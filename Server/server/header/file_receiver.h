#pragma once

#include <cstdint>
#include <string>

// Start background TCP listener that receives a single NPY file per connection.
// The sender must send an 8-byte big-endian file size header followed by raw data.
// Returns 0 on success, or a negative value on failure.
int start_file_receiver(uint16_t port, const std::string& save_path);

// Stop the listener and wait for the worker thread to exit.
void stop_file_receiver();

// Path where the receiver stores incoming files (empty if receiver not started).
const std::string& get_file_save_path();

// Connect to (ip, port) and send the specified file using the NPY transfer format.
int send_file_to_target(const std::string& file_path,
                        const std::string& ip,
                        uint16_t port);
