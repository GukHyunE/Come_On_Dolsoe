#include "client_handlers.h"
#include "client_protocol.h"

#include <atomic>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 한 줄 수신본을 파싱하고 동작 수행
void client_handle_incoming_line(const string& raw) {
    auto line = raw;
    if (!line.empty() && line.back() == '\r') line.pop_back(); // CRLF
    auto tok = split_at(line, '@');
    if (tok.empty() || tok[0].empty()) {
        cout << "[RECV] " << raw << "\n";
        return;
    }

    const string& cmd = tok[0];

    // ECHO@ME@..., ECHO@ALL@...
    if (cmd == "ECHO") {
        if (tok.size() >= 3) {
            string payload = tok[2];
            for (size_t i = 3; i < tok.size(); ++i) {
                payload.push_back('@');
                payload += tok[i];
            }
            cout << "[ECHO] " << tok[1] << " | " << payload << "\n";
        } else {
            cout << "[ECHO] " << line << "\n";
        }
        return;
    }

    // --------------------------------------------
    // 아래에 Command에 따른 처리 명령 작성하면 됨
    // --------------------------------------------

    // MSG@from@seq@payload...
    if (cmd == "MSG") {
        if (tok.size() >= 4) {
            const string& from = tok[1];
            const string& seq  = tok[2];
            string payload = tok[3];
            for (size_t i = 4; i < tok.size(); ++i) {
                payload.push_back('@');
                payload += tok[i];
            }
            cout << "[MSG] from=" << from << " seq=" << seq << " | " << payload << "\n";
        } else {
            cout << "[MSG] " << line << "\n";
        }
        return;
    }

    // ACK@seq
    if (cmd == "ACK") {
        if (tok.size() >= 2) cout << "[ACK] seq=" << tok[1] << "\n";
        else                 cout << "[ACK] " << line << "\n";
        return;
    }

    // NACK@seq@reason
    if (cmd == "NACK") {
        string reason;
        if (tok.size() >= 3) {
            reason = tok[2];
            for (size_t i = 3; i < tok.size(); ++i) {
                reason.push_back('@'); reason += tok[i];
            }
        }
        cout << "[NACK] seq=" << (tok.size()>=2 ? tok[1] : "?")
                  << " reason=" << (reason.empty()? "-" : reason) << "\n";
        return;
    }
}
