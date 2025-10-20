#pragma once

#include <cstdint>
#include <string>

// Start a background listener that receives NPY files using the 8-byte length
// header protocol. Returns 0 on success, negative value on failure.
int start_client_file_receiver(uint16_t port, const std::string& save_path);

// Stop the listener and wait for the thread to finish.
void stop_client_file_receiver();
