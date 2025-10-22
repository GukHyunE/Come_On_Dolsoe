#include "client.h"
#include "client_protocol.h"
#include "client_handlers.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <signal.h>
#include <unistd.h>

#include <atomic>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using namespace std;

static atomic<bool> g_running(true);

// ----- 수신 스레드: 서버 메시지 읽어 출력 -----
// 서버로부터 오는 데이터를 누적 버퍼(acc)에 쌓고
// '\n' 기준으로 줄 단위로 잘라서 출력.
static void rx_thread_func(int sock) {
    string acc; acc.reserve(4096);
    char buf[4096];

    while (g_running.load()) {
        ssize_t n = recv(sock, buf, sizeof(buf), 0);
        if (n > 0) {
            acc.append(buf, buf + n);
            // '\n' 기준으로 출력
            for (;;) {
                size_t pos = acc.find('\n');
                if (pos == string::npos) break;
                string line = acc.substr(0, pos);
                acc.erase(0, pos + 1);

                // ---- (변경) 라인 처리 호출 ----
                client_handle_incoming_line(line);
            }
        } else if (n == 0) {
            cerr << "[INFO] server closed connection\n";
            g_running.store(false);
            break;
        } else {
            if (errno == EINTR) continue;
            perror("recv");
            g_running.store(false);
            break;
        }
    }
}

int start_client(const char* server_ip, int port) {
    signal(SIGPIPE, SIG_IGN); // 끊긴 소켓에 send 시 프로세스 종료 방지

    // 소켓 생성
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) { perror("socket"); return 1; }

    // 서버 주소 설정
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port   = htons((uint16_t)port);
    if (inet_pton(AF_INET, server_ip, &addr.sin_addr) != 1) {
        cerr << "Invalid IP: " << server_ip << "\n";
        close(sock);
        return 1;
    }

    // 연결
    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect");
        close(sock);
        return 1;
    }
    cout << "[INFO] connected to " << server_ip << ":" << port
         << " (type 'q' + Enter to quit)\n";

    // 수신 스레드 시작
    thread rx(rx_thread_func, sock);

    // 표준입력 → 서버로 전송
    // 한 줄 입력하면 그대로 서버에 전송(자동 '\n')
    string line;
    while (g_running.load() && getline(cin, line)) {
        if (line == "q" || line == "Q") {
            g_running.store(false);
            break;
        }
        if (!send_all_line(sock, line)) {
            cerr << "[ERROR] send failed\n";
            g_running.store(false);
            break;
        }
    }

    // 종료 처리
    shutdown(sock, SHUT_RDWR); // 수신 스레드 recv()를 0으로 떨어뜨려 종료 유도
    rx.join();
    close(sock);
    cout << "[INFO] client exit\n";
    return 0;
}
