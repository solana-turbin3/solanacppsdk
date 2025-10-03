#!/usr/bin/env bash
set -euo pipefail

# Resolve script directory and repo root
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(dirname "$SCRIPT_DIR")"

# Compiler detection
if [ -n "${CXX:-}" ]; then
  COMPILER="$CXX"
elif command -v clang++ >/dev/null 2>&1; then
  COMPILER="clang++"
elif command -v g++ >/dev/null 2>&1; then
  COMPILER="g++"
else
  echo "No C++ compiler found. Set \$CXX or install clang++/g++."
  exit 1
fi

CXXFLAGS="-std=c++17 -I$ROOT_DIR/include -Wall -Wextra"
LDFLAGS="-L$ROOT_DIR/lib -lsodium"
BUILD_DIR="$ROOT_DIR/build"

mkdir -p "$BUILD_DIR"

# Discover all test files automatically
TEST_FILES=("$ROOT_DIR"/tests/solana/test_*.cpp)

# Function to build + run a test
build_and_run() {
  local test_file=$1
  local test_name
  test_name=$(basename "$test_file" .cpp)
  
  echo "🔨 Building $test_name..."
  "$COMPILER" $CXXFLAGS $(find "$ROOT_DIR/src/solana" -name '*.cpp') "$test_file" $LDFLAGS -o "$BUILD_DIR/$test_name"

  echo "Running $test_name..."
  # On Windows, we need to ensure the DLL is available
  if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
    # Copy DLL to build directory for Windows
    cp "$ROOT_DIR/vcpkg/libsodium-win64/bin/libsodium-26.dll" "$BUILD_DIR/" 2>/dev/null || true
    "$BUILD_DIR/$test_name"
  else
    "$BUILD_DIR/$test_name"
  fi
  echo
}

if [ $# -eq 0 ]; then
  echo "Running all tests..."
  for file in "${TEST_FILES[@]}"; do
    build_and_run "$file"
  done
else
  test_name=$1
  test_file="$ROOT_DIR/tests/solana/${test_name}.cpp"
  if [ -f "$test_file" ]; then
    build_and_run "$test_file"
  else
    echo "Test '$test_name' not found."
    echo "Available tests:"
    for f in "${TEST_FILES[@]}"; do
      echo "  - $(basename "$f" .cpp)"
    done
    exit 1
  fi
fi
