# Solana C++ SDK (WIP)

## Build & Test

```bash
mkdir -p build && cd build
clang++ -std=c++17 -I../include ../src/base58.cpp ../tests/test_base58.cpp -o test_base58
./test_base58
```

## Status

- [x] Base58 encode/decode
- [ ] PublicKey
- [ ] Keypair