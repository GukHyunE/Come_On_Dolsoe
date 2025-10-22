#!/usr/bin/env bash
# build — one-shot CMake build runner
# 사용법:
#   ./build            # 기본(Debug) 빌드
#   ./build r          # Release 빌드
#   ./build clean      # 클린 후 빌드
#   ./build target X   # 특정 타겟만 빌드(X 자리에 타겟명)

set -euo pipefail

BUILD_DIR="build"
BUILD_TYPE="Debug"
TARGET=""
DO_CLEAN=0

# 간단 인자 파싱
case "${1-}" in
  r|release|Release) BUILD_TYPE="Release";;
  clean) DO_CLEAN=1;;
  target) TARGET="${2-}";;
  "" ) ;;
  *) echo "Unknown arg: $1"; echo "Usage: ./build [r|clean|target <name>]"; exit 1;;
esac

# clean 옵션이면 빌드 폴더 비우기
if [[ $DO_CLEAN -eq 1 ]]; then
  echo "[clean] removing $BUILD_DIR"
  rm -rf "$BUILD_DIR"
fi

# configure 필요 여부 판단(CMakeCache 유무)
if [[ ! -f "$BUILD_DIR/CMakeCache.txt" ]]; then
  echo "[configure] CMAKE_BUILD_TYPE=$BUILD_TYPE -> $BUILD_DIR"
  cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
else
  echo "[configure] skipped (already configured)."
fi

# 빌드 실행(병렬)
if [[ -n "$TARGET" ]]; then
  echo "[build] target: $TARGET"
  cmake --build "$BUILD_DIR" --target "$TARGET" --parallel
else
  echo "[build] all"
  cmake --build "$BUILD_DIR" --parallel
fi

echo "[done] artifacts in ./$BUILD_DIR/"
