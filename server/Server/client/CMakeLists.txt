# 클라이언트 전용 CMake

find_package(Threads REQUIRED)

add_executable(client
  source/main.cpp
  source/client.cpp
  source/client_handlers.cpp
)

target_include_directories(client
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/header
)

target_link_libraries(client
  PRIVATE
    Threads::Threads
)

set_target_properties(client PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
