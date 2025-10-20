cmake_minimum_required(VERSION 3.16)

project(dolsoe LANGUAGES CXX)

# 공통 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 기본 빌드 타입 (미지정 시 Release)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# 공통 경고 플래그
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 하위 디렉터리 추가
add_subdirectory(server)
add_subdirectory(client)
