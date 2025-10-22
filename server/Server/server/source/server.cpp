#include "server.h"
#include "server_protocol.h"
#include "server_handlers.h"
#include "session.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>
#include <unordered_map>

#include <atomic>
#include <string>
#include <cerrno>

using namespace std;

#define PACKET_SIZE 4096  // 1회 recv 임시버퍼 크기

// 전역 상태(동시 접근 보호)
static mutex g_mtx;
static vector<ClientInfo*> g_clients;                // 접속 목록
static unordered_map<string, ClientInfo*> g_id2cli;  // id -> ClientInfo*

// 전역 실행 플래그
static atomic<bool> g_running(true);
static atomic<int> g_listen_fd{-1};

// stdin을 감시하는 컨트롤 스레드
static void control_thread() {
    string line;
    while(getline(cin, line)) {
        if(line == "q" || line == "Q") {
            cerr << "[CTRL] quit requested\n";
            g_running.store(false);
            int fd = g_listen_fd.exchange(-1); // fd 읽고 즉시 -1로
            if(fd >= 0) {
                shutdown(fd, SHUT_RDWR);
                close(fd);   // accept()를 깨우는 트리거
            }
            break;
        }
    }
}

// ServerHandlers에 넘길 컨텍스트 생성 헬퍼
static ServerContext make_ctx() {
    return ServerContext{ g_mtx, g_clients, g_id2cli };
}

// 명령 처리: 한 줄(line, '\n' 제거됨) → 파싱/응답/포워딩
static void handle_line(ClientInfo* self, string line) {
    if (!line.empty() && line.back() == '\r')
        line.pop_back(); // CRLF 대응

    auto tok = split_at(line, '@');
    if (tok.empty() || tok[0].empty())
        return;

    const string& cmd = tok[0];

    // 디스패치: 각 기능은 server_handlers.*에 구현
    auto ctx = make_ctx();

    // 에코 테스트
    if(cmd == "ECHO") {
        handle_echo(ctx, self, tok, line);
        return;
    }

    // 사용자 정보 저장 (키오스크 -> 서버)
    if(cmd == "STORE") {
        handle_store_info(ctx, self, tok);
        return;
    }

    // 로봇 등록 (로봇 -> 서버)
    if(cmd == "ROBOT_READY") {
        handle_robot_ready(ctx, self, tok);
        return;
    }

    // 로봇에게 비밀번호 전송 명령 (키오스크 -> 서버)
    if(cmd == "SEND_TO_ROBOT") {
        handle_send_password_to_robot(ctx, self, tok);
        return;
    }

    // 로봇 상태 업데이트 명령 (키오스크/로봇 -> 서버)
    if(cmd == "ROBOT_STATUS") {
        handle_robot_status(ctx, self, tok);
        return;
    }

    // 로봇 상태 문의 명령 (키오스크 -> 서버)
    if(cmd == "QUERY_ROBOT_STATUS") {
        handle_query_robot_status(ctx, self, tok);
        return;
    }

    /*
    ***************************예시 명령처리들***************************
    // 1) 헬스체크
    if (cmd == "PING") {
        (void)send_all_line(self->fd, "PONG");
        return;
    }

    // 2) ID 등록: REGISTER@<id>
    if (cmd == "REGISTER") {
        if (tok.size() < 2) { (void)send_all_line(self->fd, "ERR@FORMAT"); return; }
        const string& new_id = tok[1];

        // 중복 ID가 있으면 기존 연결 제거(정책상 NACK로 바꿀 수도 있음)
        {
            lock_guard<mutex> lk(g_mtx);
            auto it_old = g_id2cli.find(new_id);
            if (it_old != g_id2cli.end() && it_old->second != self) {
                // 기존 세션 닫기
                close(it_old->second->fd);
                // 목록/맵에서 제거는 해당 스레드 종료 시점에 정리됨(레퍼런스만 삭제)
            }
            self->id = new_id;
            g_id2cli[new_id] = self;
        }
        cerr << "[REGISTER] fd=" << self->fd << " id=" << new_id << "\n";
        (void)send_all_line(self->fd, string("ACK@REGISTER@") + new_id);
        return;
    }

    // 3) 센서: SENSOR@<id>@<value>  (샘플 처리)
    if (cmd == "SENSOR") {
        if (tok.size() < 3) { (void)send_all_line(self->fd, "ERR@FORMAT"); return; }
        const string& sid   = tok[1];
        const string& value = tok[2];
        cerr << "[SENSOR] id=" << sid << " value=" << value << "\n";
        (void)send_all_line(self->fd, string("ACK@SENSOR@") + sid + "@" + value);
        return;
    }

    // 4) 메시지 포워딩: MSG@<to_id>@<seq>@<payload...>
    if (cmd == "MSG") {
        if (tok.size() < 4) { (void)send_all_line(self->fd, "ERR@FORMAT"); return; }
        const string& to_id = tok[1];
        const string& seq   = tok[2];

        // payload 재조립(토큰 3 이후 전부)
        string payload = tok[3];
        for (size_t i = 4; i < tok.size(); ++i) {
            payload.push_back('@');
            payload += tok[i];
        }

        ClientInfo* to = find_by_id(to_id);
        if (!to) {
            (void)send_all_line(self->fd, string("NACK@") + seq + "@client not found");
            return;
        }

        // 대상에게: MSG@<from_id>@<seq>@<payload...>
        const string from_id = self->id;
        (void)send_all_line(to->fd, string("MSG@") + from_id + "@" + seq + "@" + payload);

        // 보낸 쪽에 ACK
        (void)send_all_line(self->fd, string("ACK@") + seq);
        return;
    }

    // 5) 클라이언트가 종료 의사: DISCONNECT
    if (cmd == "DISCONNECT") {
        (void)send_all_line(self->fd, "BYE"); // 실제 close는 recv 루프에서 EOF 시
        return;
    }

    // 6) 정의되지 않은 명령
    (void)send_all_line(self->fd, string("ERR@UNKNOWN@") + cmd);

    */
}

// Client 스레드 - 수신 루프 (파싱) + 명령 처리 + 종료 처리
static void handle_client(ClientInfo* c) {
    cout << "[CLIENT] start fd=" << c->fd << " from "
         << inet_ntoa(c->addr.sin_addr) << ":" << ntohs(c->addr.sin_port) << endl;

    string acc;                 // TCP 누적 버퍼
    acc.reserve(4096);
    char buf[PACKET_SIZE];

    while (true) {
        memset(buf, 0, sizeof(buf));
        ssize_t n = recv(c->fd, buf, sizeof(buf), 0);
        if (n > 0) {
            acc.append(buf, buf + n);

            // '\n' 단위로 라인 분리
            for (;;) {
                size_t pos = acc.find('\n');
                if (pos == string::npos)
                    break;
                string line = acc.substr(0, pos);
                acc.erase(0, pos + 1);
                handle_line(c, move(line));
            }
        } else if (n == 0) {
            cout << "[CLIENT] closed fd=" << c->fd << endl;
            break;
        } else {
            perror("recv");
            break;
        }
    }

    // 소켓 닫고 전역 상태에서 제거
    close(c->fd);

    lock_guard<mutex> lk(g_mtx);

    // 핸들러에게 연결 종료 알림 (g_kiosk_client 등 포인터 정리 목적)
    auto ctx = make_ctx();
    handle_client_disconnection(ctx, c);

    // id 매핑 제거
    if (!c->id.empty()) {
        auto it = g_id2cli.find(c->id);
        if (it != g_id2cli.end() && it->second == c) g_id2cli.erase(it);
    }
    // 접속 목록에서 제거
    auto it2 = find(g_clients.begin(), g_clients.end(), c);
    if (it2 != g_clients.end()) g_clients.erase(it2);

    // delete c; // Main thread is now responsible for cleanup
}


// Signal handler for graceful shutdown
void handle_shutdown_signal(int signum) {
    if (g_running.load()) {
        cerr << "\n[SIGNAL] Caught signal " << signum << ". Shutting down.\n";
        g_running.store(false);
        int fd = g_listen_fd.exchange(-1);
        if(fd >= 0) {
            shutdown(fd, SHUT_RDWR);
            close(fd);
        }
    }
}

int start_server(int port) {
    // Set up signal handlers for graceful shutdown
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, handle_shutdown_signal);
    signal(SIGTERM, handle_shutdown_signal);

    // 1) Create listening socket
    int srv = socket(AF_INET, SOCK_STREAM, 0);
    if (srv < 0) { perror("socket"); return 1; }

    int yes = 1;
    setsockopt(srv, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    // 2) Bind
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons((uint16_t)port);

    if (bind(srv, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(srv);
        return 1;
    }

    // 3) Listen
    if (listen(srv, 64) < 0) {
        perror("listen");
        close(srv);
        return 1;
    }

    g_listen_fd.store(srv);
    thread ctrl(control_thread);

    cout << "[SERVER] listening on " << port
              << " (type 'q' + Enter or Ctrl-C to quit)\n";

    vector<ClientInfo*> all_sessions; // Master list for joining/cleanup

    // 4) Accept loop
    while (g_running.load()) {
        sockaddr_in cli{}; socklen_t clen = sizeof(cli);
        int cs = accept(srv, (sockaddr*)&cli, &clen);
        if (cs < 0) {
            if (!g_running.load() || errno == EBADF) break; // Intentional shutdown
            if (errno == EINTR) continue;     // Retry on signal interrupt
            perror("accept");
            continue;
        }

        // Create and register session struct
        ClientInfo* c = new ClientInfo;
        c->fd = cs;
        c->addr = cli;
        all_sessions.push_back(c); // Add to master list for cleanup

        {
            lock_guard<mutex> lk(g_mtx);
            g_clients.push_back(c);
        }

        // Start thread (joinable, not detached)
        c->th = thread(handle_client, c);

        cout << "[CONNECT] " << inet_ntoa(cli.sin_addr) << ":" << ntohs(cli.sin_port)
             << " fd=" << cs << " (alive=" << g_clients.size() << ")\n";
    }

    cout << "[SHUTDOWN] Accept loop finished. Closing client connections...\n";

    // Shutdown all client sockets to unblock recv() in their threads
    for (auto* c : all_sessions) {
        shutdown(c->fd, SHUT_RDWR);
    }

    // Join all client threads
    cout << "[SHUTDOWN] Joining all client threads...\n";
    for (auto* c : all_sessions) {
        if (c->th.joinable()) {
            c->th.join();
        }
    }
    cout << "[SHUTDOWN] All threads joined.\n";

    // Join the control thread
    ctrl.join();

    // Clean up session objects
    cout << "[SHUTDOWN] Cleaning up session objects...\n";
    for (auto* c : all_sessions) {
        delete c;
    }
    all_sessions.clear();
    cout << "[SHUTDOWN] Cleanup complete.\n";

    int fd = g_listen_fd.exchange(-1);
    if (fd >= 0) close(fd);
    return 0;
}
