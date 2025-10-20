#pragma once
#include <string>
#include <vector>
#include <sys/socket.h>
#include <cerrno>

using namespace std;

// 안전 송신(부분 전송 처리). 에러 시 false.
// MSG_NOSIGNAL: 끊긴 소켓에 send할 때 SIGPIPE 방지(리눅스).
static inline bool send_all(int fd, const char* p, size_t n) {
    size_t off = 0;
    while (off < n) {
        ssize_t k = ::send(fd, p + off, n - off, MSG_NOSIGNAL);
        if (k > 0)      off += (size_t)k;
        else if (k < 0 && errno == EINTR) continue;
        else            return false;
    }
    return true;
}

// 문자열 한 줄 전송: 끝에 '\n'이 없으면 자동 부착.
static inline bool send_all_line(int fd, string s) {
    if (s.empty() || s.back() != '\n') s.push_back('\n');
    return send_all(fd, s.data(), s.size());
}

// 구분자 1글자로 토큰 분리: "A@B@C" -> ["A","B","C"]
static inline vector<string> split_at(const string& s, char delim) {
    vector<string> out;
    string cur;
    out.reserve(8);
    for (char ch : s) {
        if (ch == delim) { out.push_back(move(cur)); cur.clear(); }
        else cur.push_back(ch);
    }
    out.push_back(move(cur));
    return out;
}

/*
[프로토콜 메모]
- 라인 단위 메시지('\n' 종료), 필드는 '@' 구분
- ECHO@ALL@text...   -> 모든 클라이언트에게 방송
- ECHO@ME@text...    -> 나에게만 회신
- (예시) REGISTER@<id> / SENSOR@<id>@<value> / MSG@<to>@<seq>@...
- (예시) DISCONNECT -> BYE 회신
*/