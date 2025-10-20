#pragma once

// 클라이언트 시작 함수
//  - server_ip : "127.0.0.1" 같은 IPv4 문자열
//  - port      : 서버 포트
// 반환값: 0(정상 종료), 0 이외(에러)
int start_client(const char* server_ip, int port);
