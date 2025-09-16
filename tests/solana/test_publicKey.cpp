#include <iostream>
#include <solana/publicKey.h>
#include <sodium.h>

int main()
{
    // Initialize libsodium
    if (sodium_init() < 0)
    {
        std::cerr << "Failed to initialize libsodium" << std::endl;
        return 1;
    }

    std::cout << "Libsodium initialized successfully" << std::endl;

    try
    {
        // Test PublicKey creation
        solana::PublicKey pk(42);
        std::cout << "PublicKey created successfully from uint64" << std::endl;

        // Test default PublicKey
        solana::PublicKey defaultPk = solana::PublicKey::Default;
        std::cout << "Default PublicKey accessed successfully" << std::endl;

        std::cout << "All tests passed!" << std::endl;
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}
