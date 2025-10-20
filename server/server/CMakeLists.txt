# 서버 전용 CMake
# 이 디렉토리에서 server 실행파일 생성

# 스레드 라이브러리 필수 (pthread)
find_package(Threads REQUIRED)

add_executable(server
  source/main.cpp
  source/server.cpp
  source/server_handlers.cpp
)

# 서버에서 헤더 include 경로
target_include_directories(server
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/header
)

# 링크
target_link_libraries(server
  PRIVATE
    Threads::Threads
)

# (선택) 빌드 산출물 위치를 최상위 build/bin 아래로
set_target_properties(server PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
