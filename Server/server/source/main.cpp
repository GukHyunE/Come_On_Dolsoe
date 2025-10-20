#include "server.h"
#include "main.h"
#include "file_receiver.h"

#include <iostream>

using namespace std;

namespace {
    constexpr int DEFAULT_PORT = 5000;
    constexpr uint16_t FILE_RECEIVER_PORT = 12345;
    const char* FILE_SAVE_PATH = "received/customer_feature.npy";
}

int main(int argc, char* argv[]) {
    int port = DEFAULT_PORT;
    if (argc == 2)
        port = stoi(argv[1]);

    int file_rc = start_file_receiver(FILE_RECEIVER_PORT, FILE_SAVE_PATH);
    if (file_rc != 0) {
        cerr << "[FILE] Receiver failed to start (code " << file_rc << "). NPY uploads will be unavailable.\n";
    }

    int server_rc = start_server(port);

    stop_file_receiver();
    return server_rc;
}
