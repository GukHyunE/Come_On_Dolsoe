#pragma once
#include <string>
#include <vector>

using namespace std;

// 한 줄 수신본을 파싱하고 동작 수행
void client_handle_incoming_line(const string& raw);

// 필요하면 이후에 더 쪼갤 수 있음.
// ex) void client_handle_msg(...), client_handle_echo(...);
