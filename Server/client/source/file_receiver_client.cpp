#include "file_receiver_client.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <atomic>
#include <cerrno>
#include <cstring>
#include <filesystem>
#include <future>
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>

using namespace std;

namespace {
    thread g_listener;
    atomic<bool> g_running{false};
    atomic<int> g_listen_fd{-1};
    string g_save_path;

    bool recv_exact(int fd, char* buf, size_t len) {
        size_t off = 0;
        while (off < len) {
            ssize_t k = recv(fd, buf + off, len - off, 0);
            if (k > 0) {
                off += static_cast<size_t>(k);
            } else if (k == 0) {
                return false;
            } else if (errno == EINTR) {
                continue;
            } else {
                perror("[FILE-CLI] recv");
                return false;
            }
        }
        return true;
    }

    bool save_file_data(int fd, uint64_t size, const filesystem::path& save_path) {
        namespace fs = std::filesystem;
        error_code ec;
        auto parent = save_path.parent_path();
        if (!parent.empty()) {
            fs::create_directories(parent, ec);
            if (ec) {
                cerr << "[FILE-CLI] Failed to create directory '" << parent
                     << "': " << ec.message() << "\n";
                return false;
            }
        }

        ofstream ofs(save_path, ios::binary | ios::trunc);
        if (!ofs) {
            cerr << "[FILE-CLI] Failed to open '" << save_path << "' for writing\n";
            return false;
        }

        vector<char> buffer(64 * 1024);
        uint64_t remaining = size;
        while (remaining > 0) {
            size_t chunk = static_cast<size_t>(min<uint64_t>(buffer.size(), remaining));
            ssize_t n = recv(fd, buffer.data(), chunk, 0);
            if (n > 0) {
                ofs.write(buffer.data(), n);
                if (!ofs) {
                    cerr << "[FILE-CLI] Error while writing to '" << save_path << "'\n";
                    ofs.close();
                    fs::remove(save_path);
                    return false;
                }
                remaining -= static_cast<uint64_t>(n);
            } else if (n == 0) {
                cerr << "[FILE-CLI] Connection closed prematurely\n";
                ofs.close();
                fs::remove(save_path);
                return false;
            } else if (errno == EINTR) {
                continue;
            } else {
                perror("[FILE-CLI] recv");
                ofs.close();
                fs::remove(save_path);
                return false;
            }
        }

        ofs.close();
        return true;
    }

    uint64_t parse_be64(const unsigned char header[8]) {
        uint64_t value = 0;
        for (int i = 0; i < 8; ++i) {
            value = (value << 8) | static_cast<uint64_t>(header[i]);
        }
        return value;
    }

    void listener_thread(uint16_t port, string save_path, promise<int> ready) {
        int srv = socket(AF_INET, SOCK_STREAM, 0);
        if (srv < 0) {
            perror("[FILE-CLI] socket");
            ready.set_value(-1);
            g_running.store(false);
            return;
        }

        int yes = 1;
        setsockopt(srv, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(port);

        if (bind(srv, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
            perror("[FILE-CLI] bind");
            ready.set_value(-2);
            close(srv);
            g_running.store(false);
            return;
        }

        if (listen(srv, 4) < 0) {
            perror("[FILE-CLI] listen");
            ready.set_value(-3);
            close(srv);
            g_running.store(false);
            return;
        }

        g_listen_fd.store(srv);
        ready.set_value(0);
        cout << "[FILE-CLI] Listening on port " << port << " for NPY files...\n";

        filesystem::path output_path(save_path);

        while (g_running.load()) {
            sockaddr_in peer{};
            socklen_t peer_len = sizeof(peer);
            int cs = accept(srv, reinterpret_cast<sockaddr*>(&peer), &peer_len);
            if (cs < 0) {
                if (!g_running.load()) break;
                if (errno == EINTR) continue;
                perror("[FILE-CLI] accept");
                continue;
            }

            char addr_buf[INET_ADDRSTRLEN] = {0};
            inet_ntop(AF_INET, &peer.sin_addr, addr_buf, sizeof(addr_buf));
            cout << "[FILE-CLI] Connection from " << addr_buf
                 << ":" << ntohs(peer.sin_port) << "\n";

            unsigned char header[8];
            if (!recv_exact(cs, reinterpret_cast<char*>(header), sizeof(header))) {
                cerr << "[FILE-CLI] Failed to read header\n";
                close(cs);
                continue;
            }

            uint64_t expected_size = parse_be64(header);
            if (expected_size == 0) {
                cerr << "[FILE-CLI] Received empty file. Ignoring.\n";
                close(cs);
                continue;
            }

            if (save_file_data(cs, expected_size, output_path)) {
                cout << "[FILE-CLI] Saved file to '" << output_path
                     << "' (" << expected_size << " bytes)\n";
            } else {
                cerr << "[FILE-CLI] Failed to store incoming file\n";
            }

            close(cs);
        }

        close(srv);
        g_listen_fd.store(-1);
        cout << "[FILE-CLI] Listener stopped\n";
        g_running.store(false);
    }
}

int start_client_file_receiver(uint16_t port, const std::string& save_path) {
    bool expected = false;
    if (!g_running.compare_exchange_strong(expected, true)) {
        return -10;
    }

    g_save_path = save_path;
    promise<int> ready;
    auto fut = ready.get_future();
    g_listener = thread(listener_thread, port, save_path, move(ready));
    int rc = fut.get();
    if (rc != 0) {
        g_running.store(false);
        if (g_listener.joinable()) g_listener.join();
    }
    return rc;
}

void stop_client_file_receiver() {
    if (!g_running.exchange(false)) return;

    int fd = g_listen_fd.load();
    if (fd >= 0) {
        shutdown(fd, SHUT_RDWR);
    }

    if (g_listener.joinable()) g_listener.join();
    g_listen_fd.store(-1);
}
