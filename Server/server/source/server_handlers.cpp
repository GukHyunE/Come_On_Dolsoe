#include "server_handlers.h"
#include "server_protocol.h"   // send_all_line, split_at 등
#include "file_receiver.h"

#include <algorithm>
#include <filesystem>
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

// 저장된 NPY 파일을 지정한 IP/포트로 전송
// 요청 형식: SEND_NPY@<ip>@<port>
void handle_send_npy(ServerContext& ctx, ClientInfo* self, const vector<string>& tok) {
    (void)ctx;
    if (tok.size() < 3) {
        send_all_line(self->fd, "ERR@SEND_NPY@FORMAT");
        return;
    }

    const string& ip = tok[1];
    const string& port_str = tok[2];
    int port = 0;
    try {
        port = stoi(port_str);
    } catch (...) {
        send_all_line(self->fd, "ERR@SEND_NPY@PORT");
        return;
    }

    if (port <= 0 || port > 65535) {
        send_all_line(self->fd, "ERR@SEND_NPY@PORT_RANGE");
        return;
    }

    const string& path = get_file_save_path();
    if (path.empty()) {
        send_all_line(self->fd, "ERR@SEND_NPY@NO_PATH");
        return;
    }

    namespace fs = std::filesystem;
    if (!fs::exists(path)) {
        send_all_line(self->fd, "ERR@SEND_NPY@NO_FILE");
        return;
    }

    int rc = send_file_to_target(path, ip, static_cast<uint16_t>(port));
    if (rc == 0) {
        send_all_line(self->fd, "ACK@SEND_NPY");
    } else {
        send_all_line(self->fd, string("ERR@SEND_NPY@FAIL@") + to_string(rc));
    }
}
