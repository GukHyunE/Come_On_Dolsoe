#include "server_handlers.h"
#include "server_protocol.h"   // send_all_line, split_at 등

#include <algorithm>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <thread>
#include <iostream> // for cout

using namespace std;

// 사용자 정보를 저장할 전역 변수
static string g_name;
static string g_country_code;
static string g_password;

// 로봇 클라이언트를 저장할 전역 포인터
static ClientInfo* g_robot_client = nullptr;

// 로봇의 현재 상태를 저장할 전역 변수
static string g_robot_current_status = "IDLE"; // IDLE, IN_USE, RETURNING, AVAILABLE

// 키오스크 클라이언트를 저장할 전역 포인터
static ClientInfo* g_kiosk_client = nullptr;


static vector<int> snapshot_client_fds(ServerContext& ctx) {
    vector<int> fds;
    lock_guard<mutex> lk(ctx.mtx);
    fds.reserve(ctx.clients.size());
    for (auto* c : ctx.clients) fds.push_back(c->fd);
    return fds;
}

static ClientInfo* find_by_id(ServerContext& ctx, const string& id) {
    lock_guard<mutex> lk(ctx.mtx);
    auto it = ctx.id2cli.find(id);
    return (it == ctx.id2cli.end()) ? nullptr : it->second;
}

void handle_echo(ServerContext& ctx, ClientInfo* self,
                 const vector<string>& tok,
                 const string& fullLine)
{
    if (tok.size() < 2) { (void)send_all_line(self->fd, "ERR@FORMAT"); return; }
    const string& who = tok[1];

    if (who == "ALL") {
        auto fds = snapshot_client_fds(ctx);
        for (int fd : fds) (void)send_all_line(fd, fullLine);
    } else if (who == "ME") {
        (void)send_all_line(self->fd, fullLine);
    } else {
        (void)send_all_line(self->fd, "ERR@UNKNOWN@ECHO_TARGET");
    }
}

// 키오스크에서 보낸 사용자 정보(이름, 국가코드, 비밀번호)를 저장
// 요청 형식: STORE@<name>@<country_code>@<password>
void handle_store_info(ServerContext& ctx, ClientInfo* self, const vector<string>& tok) {
    if (tok.size() < 4) {
        send_all_line(self->fd, "ERR@STORE@FORMAT");
        return;
    }
    {
        lock_guard<mutex> lk(ctx.mtx);
        g_name = tok[1];
        g_country_code = tok[2];
        g_password = tok[3];
        g_kiosk_client = self; // Register this client as the kiosk
        cout << "[STORE] Stored password: " << g_password << endl;
    }
    send_all_line(self->fd, "ACK@STORE");
}

// 로봇 클라이언트를 등록
// 요청 형식: ROBOT_READY@<robot_id>
void handle_robot_ready(ServerContext& ctx, ClientInfo* self, const vector<string>& tok) {
    if (tok.size() < 2) {
        send_all_line(self->fd, "ERR@ROBOT_READY@FORMAT");
        return;
    }
    {
        lock_guard<mutex> lk(ctx.mtx);
        g_robot_client = self;
        // ID도 등록해줌 (선택사항)
        const string& robot_id = tok[1];
        self->id = robot_id;
        ctx.id2cli[robot_id] = self;
        g_robot_current_status = "IDLE"; // Robot is ready, so status is IDLE
        cout << "[ROBOT] Robot client registered: " << robot_id << " fd=" << self->fd << endl;
    }
    send_all_line(self->fd, "ACK@ROBOT_READY");
}

// 키오스크의 요청에 따라 로봇에게 비밀번호를 전송
// 요청 형식: SEND_TO_ROBOT
void handle_send_password_to_robot(ServerContext& ctx, ClientInfo* self, const vector<string>& tok) {
    ClientInfo* robot = nullptr;
    string password_to_send;
    {
        lock_guard<mutex> lk(ctx.mtx);
        robot = g_robot_client;
        password_to_send = g_password;
    }

    if (robot == nullptr) {
        cout << "[SEND_TO_ROBOT] Error: Robot is not connected." << endl;
        send_all_line(self->fd, "ERR@SEND_TO_ROBOT@NO_ROBOT");
        return;
    }
    if (password_to_send.empty()) {
        cout << "[SEND_TO_ROBOT] Error: Password is not set." << endl;
        send_all_line(self->fd, "ERR@SEND_TO_ROBOT@NO_PASSWORD");
        return;
    }

    // 로봇에게 ASSIGN_TASK@<password> 형식으로 전송
    string response = "ASSIGN_TASK@" + password_to_send;
    send_all_line(robot->fd, response);
    cout << "[SEND_TO_ROBOT] Sent password to robot fd=" << robot->fd << endl;

    // 키오스크에게 성공 응답
    send_all_line(self->fd, "ACK@SEND_TO_ROBOT");
}

// 로봇 상태를 업데이트하고, 필요시 키오스크에 알림
// 요청 형식: ROBOT_STATUS@<status> (예: IN_USE, RETURNING, AVAILABLE)
void handle_robot_status(ServerContext& ctx, ClientInfo* self, const vector<string>& tok) {
    if (tok.size() < 2) {
        send_all_line(self->fd, "ERR@ROBOT_STATUS@FORMAT");
        return;
    }
    const string& status = tok[1];
    {
        lock_guard<mutex> lk(ctx.mtx);
        g_robot_current_status = status;
        cout << "[ROBOT_STATUS] Robot status updated to: " << status << endl;

        if (status == "AVAILABLE" && g_kiosk_client != nullptr) {
            send_all_line(g_kiosk_client->fd, "ROBOT_AVAILABLE");
            cout << "[ROBOT_STATUS] Sent ROBOT_AVAILABLE to kiosk fd=" << g_kiosk_client->fd << endl;
        }
    }
    send_all_line(self->fd, "ACK@ROBOT_STATUS");
}

// 로봇의 현재 상태를 클라이언트에 응답
// 요청 형식: QUERY_ROBOT_STATUS
void handle_query_robot_status(ServerContext& ctx, ClientInfo* self, const vector<string>& tok) {
    (void)tok; // Unused parameter
    string current_status;
    {
        lock_guard<mutex> lk(ctx.mtx);
        current_status = g_robot_current_status;
    }
    string response = "ROBOT_STATUS@" + current_status;
    send_all_line(self->fd, response);
    cout << "[QUERY_ROBOT_STATUS] Responded with: " << response << " to fd=" << self->fd << endl;
}

// 클라이언트 연결 종료 처리. g_mtx 뮤텍스가 잠겨있는 동안 호출되어야 함.
void handle_client_disconnection(ServerContext& ctx, ClientInfo* self) {
    if (self == g_kiosk_client) {
        cout << "[DISCONNECT] Kiosk client has disconnected. Clearing pointer." << endl;
        g_kiosk_client = nullptr;
    }
    if (self == g_robot_client) {
        cout << "[DISCONNECT] Robot client has disconnected. Clearing pointer." << endl;
        g_robot_client = nullptr;
    }
}
