#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <iostream>

int start_server(int port);
int server_send(int client_fd, const std::string& line);

#endif // TCP_SERVER_H
