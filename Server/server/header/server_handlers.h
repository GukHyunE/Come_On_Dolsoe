#pragma once
#include "session.h"

#include <string>
#include <vector>
#include <mutex>
#include <unordered_map>
#include <netinet/in.h>

using namespace std;

// 서버 전역 상태를 한 데 모은 컨텍스트(전역 참조를 직접 쓰지 않도록)
struct ServerContext {
    mutex& mtx;
    vector<ClientInfo*>& clients;
    unordered_map<string, ClientInfo*>& id2cli;
};

void handle_echo(ServerContext& ctx, ClientInfo* self,
                 const vector<string>& tok,
                 const string& fullLine);

// 키오스크 -> 서버
void handle_store_info(ServerContext& ctx, ClientInfo* self, const vector<string>& tok);
void handle_send_password_to_robot(ServerContext& ctx, ClientInfo* self, const vector<string>& tok);
void handle_robot_status(ServerContext& ctx, ClientInfo* self, const vector<string>& tok);
void handle_query_robot_status(ServerContext& ctx, ClientInfo* self, const vector<string>& tok); // New handler for querying robot status // New handler for robot status

// 공통
void handle_client_disconnection(ServerContext& ctx, ClientInfo* self);

// 로봇 -> 서버
void handle_robot_ready(ServerContext& ctx, ClientInfo* self, const vector<string>& tok);

// void handle_register(ServerContext& ctx, ClientInfo* self, const vector<string>& tok);
// void handle_sensor(ServerContext& ctx, ClientInfo* self, const vector<string>& tok);
// void handle_msg(ServerContext& ctx, ClientInfo* self, const vector<string>& tok);
// void handle_disconnect(ServerContext& ctx, ClientInfo* self);
