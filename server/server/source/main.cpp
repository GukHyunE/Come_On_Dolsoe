#include "server.h"
#include "main.h"
#include <iostream>

#define DEFAULT_PORT    5000

using namespace std;

int main(int argc, char* argv[]) {
    int port = DEFAULT_PORT;
    if (argc == 2)
        port = stoi(argv[1]);

    // 서버를 시작하고(차단형), 에러 시 코드 반환
    return start_server(port);
}
