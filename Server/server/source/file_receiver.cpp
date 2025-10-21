#include "file_receiver.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <algorithm>
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
    // constexpr const char* FORWARD_TARGET_IP = "192.168.0.22";
    // constexpr const char* FORWARD_TARGET_IP = "192.168.0.21";
    constexpr const char* FORWARD_TARGET_IP = "192.168.0.13";
    // constexpr const char* FORWARD_TARGET_IP = "127.0.0.1";
    constexpr uint16_t FORWARD_TARGET_PORT = 5001;

    thread g_worker;
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
                perror("[FILE] recv");
                return false;
            }
        }
        return true;
    }

    bool send_all_data(int fd, const char* buf, size_t len) {
        size_t off = 0;
        while (off < len) {
            ssize_t k = send(fd, buf + off, len - off, MSG_NOSIGNAL);
            if (k > 0) {
                off += static_cast<size_t>(k);
            } else if (k < 0 && errno == EINTR) {
                continue;
            } else {
                perror("[FILE] send");
                return false;
            }
        }
        return true;
    }

    uint64_t parse_be64(const unsigned char header[8]) {
        uint64_t value = 0;
        for (int i = 0; i < 8; ++i) {
            value = (value << 8) | static_cast<uint64_t>(header[i]);
        }
        return value;
    }

    bool receive_file_data(int fd, uint64_t size, const filesystem::path& save_path) {
        error_code ec;
        const auto parent = save_path.parent_path();
        if (!parent.empty()) {
            filesystem::create_directories(parent, ec);
            if (ec) {
                cerr << "[FILE] Failed to create directory '" << parent << "': " << ec.message() << "\n";
                return false;
            }
        }

        ofstream ofs(save_path, ios::binary | ios::trunc);
        if (!ofs) {
            cerr << "[FILE] Failed to open '" << save_path << "' for writing\n";
            return false;
        }

        vector<char> buffer(64 * 1024);
        uint64_t remaining = size;
        while (remaining > 0) {
            size_t chunk_size = static_cast<size_t>(min<uint64_t>(buffer.size(), remaining));
            ssize_t n = recv(fd, buffer.data(), chunk_size, 0);
            if (n > 0) {
                ofs.write(buffer.data(), n);
                if (!ofs) {
                    cerr << "[FILE] Failed while writing to '" << save_path << "'\n";
                    ofs.close();
                    filesystem::remove(save_path);
                    return false;
                }
                remaining -= static_cast<uint64_t>(n);
            } else if (n == 0) {
                cerr << "[FILE] Peer closed connection prematurely\n";
                ofs.close();
                filesystem::remove(save_path);
                return false;
            } else if (errno == EINTR) {
                continue;
            } else {
                perror("[FILE] recv");
                ofs.close();
                filesystem::remove(save_path);
                return false;
            }
        }

        ofs.close();
        return true;
    }

    void file_receiver_thread(uint16_t port, string save_path, promise<int> ready) {
        int srv = socket(AF_INET, SOCK_STREAM, 0);
        if (srv < 0) {
            perror("[FILE] socket");
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
            perror("[FILE] bind");
            ready.set_value(-2);
            close(srv);
            g_running.store(false);
            return;
        }

        if (listen(srv, 4) < 0) {
            perror("[FILE] listen");
            ready.set_value(-3);
            close(srv);
            g_running.store(false);
            return;
        }

        g_listen_fd.store(srv);
        ready.set_value(0);
        cout << "[FILE] Listening on port " << port << " for NPY uploads\n";

        filesystem::path output_path(save_path);

        while (g_running.load()) {
            sockaddr_in peer{};
            socklen_t peer_len = sizeof(peer);
            int cs = accept(srv, reinterpret_cast<sockaddr*>(&peer), &peer_len);
            if (cs < 0) {
                if (!g_running.load()) break;
                if (errno == EINTR) continue;
                perror("[FILE] accept");
                continue;
            }

            char addr_buf[INET_ADDRSTRLEN] = {0};
            inet_ntop(AF_INET, &peer.sin_addr, addr_buf, sizeof(addr_buf));
            cout << "[FILE] Connection from " << addr_buf << ":" << ntohs(peer.sin_port) << "\n";

            unsigned char header[8];
            if (!recv_exact(cs, reinterpret_cast<char*>(header), sizeof(header))) {
                cerr << "[FILE] Failed to read header from client\n";
                close(cs);
                continue;
            }

            uint64_t expected_size = parse_be64(header);
            if (expected_size == 0) {
                cerr << "[FILE] Received zero-length file. Ignoring.\n";
                close(cs);
                continue;
            }

            if (receive_file_data(cs, expected_size, output_path)) {
                cout << "[FILE] Stored file at '" << output_path << "' (" << expected_size << " bytes)\n";
                int rc = send_file_to_target(output_path.string(),
                                             FORWARD_TARGET_IP,
                                             FORWARD_TARGET_PORT);
                if (rc == 0) {
                    cout << "[FILE] Forwarded file to "
                         << FORWARD_TARGET_IP << ":" << FORWARD_TARGET_PORT << "\n";
                } else {
                    cerr << "[FILE] Forward failed (code " << rc << ")\n";
                }
            } else {
                cerr << "[FILE] Failed to store file at '" << output_path << "'\n";
            }

            close(cs);
        }

        close(srv);
        g_listen_fd.store(-1);
        cout << "[FILE] Receiver stopped\n";
        g_running.store(false);
    }
}

int start_file_receiver(uint16_t port, const string& save_path) {
    bool expected = false;
    if (!g_running.compare_exchange_strong(expected, true)) {
        return -10;
    }

    g_save_path = save_path;
    promise<int> ready;
    auto fut = ready.get_future();
    g_worker = thread(file_receiver_thread, port, save_path, move(ready));
    int rc = fut.get();
    if (rc != 0) {
        g_running.store(false);
        if (g_worker.joinable()) g_worker.join();
    }
    return rc;
}

void stop_file_receiver() {
    if (!g_running.exchange(false)) return;

    int fd = g_listen_fd.load();
    if (fd >= 0) {
        shutdown(fd, SHUT_RDWR);
    }

    if (g_worker.joinable()) g_worker.join();
    g_listen_fd.store(-1);
}

const std::string& get_file_save_path() {
    return g_save_path;
}

int send_file_to_target(const std::string& file_path,
                        const std::string& ip,
                        uint16_t port) {
    namespace fs = std::filesystem;

    fs::path path(file_path);
    std::error_code ec;
    if (!fs::exists(path, ec) || !fs::is_regular_file(path, ec)) {
        std::cerr << "[FILE] File not found: " << file_path << "\n";
        return -1;
    }

    uint64_t file_size = fs::file_size(path, ec);
    if (ec) {
        std::cerr << "[FILE] Failed to get size of " << file_path << ": " << ec.message() << "\n";
        return -2;
    }
    ifstream ifs(path, ios::binary);
    if (!ifs) {
        std::cerr << "[FILE] Failed to open " << file_path << " for reading\n";
        return -3;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("[FILE] socket");
        return -4;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) != 1) {
        std::cerr << "[FILE] Invalid IP address: " << ip << "\n";
        close(sock);
        return -5;
    }

    if (connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        perror("[FILE] connect");
        close(sock);
        return -6;
    }

    cout << "[FILE] Sending '" << path << "' (" << file_size
         << " bytes) to " << ip << ":" << port << "\n";

    unsigned char header[8];
    uint64_t size_copy = file_size;
    for (int i = 7; i >= 0; --i) {
        header[i] = static_cast<unsigned char>(size_copy & 0xFF);
        size_copy >>= 8;
    }

    if (!send_all_data(sock, reinterpret_cast<const char*>(header), sizeof(header))) {
        std::cerr << "[FILE] Failed to send file header\n";
        close(sock);
        return -7;
    }

    std::vector<char> buffer(64 * 1024);
    uint64_t remaining = file_size;
    while (remaining > 0) {
        size_t to_read = static_cast<size_t>(std::min<uint64_t>(buffer.size(), remaining));
        ifs.read(buffer.data(), static_cast<std::streamsize>(to_read));
        std::streamsize got = ifs.gcount();
        if (got <= 0) {
            std::cerr << "[FILE] Failed while reading file data\n";
            close(sock);
            return -8;
        }
        if (!send_all_data(sock, buffer.data(), static_cast<size_t>(got))) {
            std::cerr << "[FILE] Failed while sending file data\n";
            close(sock);
            return -9;
        }
        remaining -= static_cast<uint64_t>(got);
    }

    close(sock);
    cout << "[FILE] Transfer complete\n";
    return 0;
}
