#pragma once
#include <string>
#include <vector>
#include <sys/socket.h>
#include <cerrno>

using namespace std;

// ----- 유틸: 안전 송신 (부분 전송 처리) -----
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

// 문자열 한 줄 전송(자동 개행). 끝에 '\n'이 없으면 붙여서 보냄.
static inline bool send_all_line(int fd, string s) {
    if (s.empty() || s.back() != '\n') s.push_back('\n');
    return send_all(fd, s.data(), s.size());
}

// ----- 구분자 분할: "A@B@C" -> ["A","B","C"] -----
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