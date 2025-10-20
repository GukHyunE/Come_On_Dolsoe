#include "../header/client.h"
#include <iostream>
#include <string>

#define DEFAULT_PORT    5000

using namespace std;

int main(int argc, char* argv[]) {
    string server_ip = "127.0.0.1";  // 문자열 리터럴은 string으로 보관
    int port = DEFAULT_PORT;

    // 인자 파싱 (유연하게)
    if (argc >= 2)
        server_ip = argv[1];
    if (argc >= 3)
        port = stoi(argv[2]);

    // start_client는 const char*를 받으니 c_str()로 전달
    return start_client(server_ip.c_str(), port);
}