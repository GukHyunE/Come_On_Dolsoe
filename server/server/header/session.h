#pragma once
#include <string>
#include <thread>
#include <netinet/in.h>

using namespace std;

// 클라이언트 세션 정보
struct ClientInfo {
    int fd;                 // 소켓 FD
    sockaddr_in addr;       // 피어 주소
    thread th;              // 핸들 스레드
    string id;              // REGISTER 후 설정되는 사용자 ID (미등록이면 빈 문자열)
};