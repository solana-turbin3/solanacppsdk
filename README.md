# Solana C++ SDK (WIP)

## Build & Test

```bash
mkdir -p build && clang++ -std=c++17 -Iinclude -Wall -Wextra src/base58.cpp tests/test_base58.cpp -o build/test_base58 && ./build/test_base58
```