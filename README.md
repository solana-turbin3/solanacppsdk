# Solana C++ SDK

[![Build Status](https://github.com/solana-turbin3/solanacppsdk/actions/workflows/cmake.yml/badge.svg)](https://github.com/solana-turbin3/solanacppsdk/actions/workflows/cmake.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A C++ SDK for interacting with the Solana blockchain. This project is currently a work in progress.

## Features

*   **Keypairs**: Generate, sign, and verify keypairs.
*   **Transactions**: Construct and serialize transactions.
*   **RPC Client**: Communicate with a Solana RPC node.
*   **Encoding**: Support for Base58.
*   **BIP39**: Mnemonic phrase generation.

## Getting Started

### Prerequisites

*   A C++17 compatible compiler
*   CMake (version 3.15 or later)
*   Git

### Building

1.  Clone the repository and its submodules:
    ```bash
    git clone --recurse-submodules https://github.com/solana-turbin3/solanacppsdk.git
    cd solanacppsdk
    ```

2.  Configure and build the project:
    ```bash
    cmake -B build
    cmake --build build
    ```

## Usage

Here is a basic example of how to generate a new keypair.

```cpp
#include "wallet.hpp"
#include <iostream>

int main() {
    Wallet wallet;
    Keypair keypair = wallet.create_keypair();

    std::cout << "Public Key: " << keypair.public_key << std::endl;

    return 0;
}
```

## Testing

To run all tests:

```bash
./scripts/run_tests.sh
```

To run a specific test file (e.g., `test_base58`):

```bash
./scripts/run_tests.sh test_base58
```

## Contributing

Contributions are welcome! Please feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.