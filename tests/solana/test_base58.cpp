#include <iostream>
#include <vector>
#include <stdexcept>
#include "solana/base58.h"

using namespace solana;

struct TestRunner {
    int passed = 0;
    int failed = 0;

    void check(bool condition, const std::string& description) {
        if (condition) {
            std::cout << "[PASS] " << description << "\n";
            passed++;
        } else {
            std::cout << "[FAIL] " << description << "\n";
            failed++;
        }
    }

    void summary() {
        std::cout << "\n=== TEST RESULTS ===\n";
        std::cout << "Passed: " << passed << "\n";
        std::cout << "Failed: " << failed << "\n";
        if (failed == 0) {
            std::cout << "🎉 All tests passed!\n";
        }
    }
};

int main() {
    TestRunner tr;

    // 1. Normal string
    {
        std::string input = "Hello Solana!";
        std::string encoded = Base58::encodeString(input);
        std::string decoded = Base58::decodeString(encoded);
        tr.check(decoded == input, "Normal string");
    }

    // 2. Empty string
    {
        std::string input = "";
        std::string encoded = Base58::encodeString(input);
        std::string decoded = Base58::decodeString(encoded);
        tr.check(decoded == input, "Empty string");
    }

    // 3. String with spaces
    {
        std::string input = "   ";
        std::string encoded = Base58::encodeString(input);
        std::string decoded = Base58::decodeString(encoded);
        tr.check(decoded == input, "String with spaces");
    }

    // 4. String with special characters
    {
        std::string input = "!@#$%^&*()_+-={}[];:,.<>/?";
        std::string encoded = Base58::encodeString(input);
        std::string decoded = Base58::decodeString(encoded);
        tr.check(decoded == input, "Special characters");
    }

    // 5. String with a null byte
    {
        std::string input("abc\0def", 7); // includes a null byte
        std::string encoded = Base58::encode({input.begin(), input.end()});
        auto decoded_vec = Base58::decode(encoded);
        std::string decoded(decoded_vec.begin(), decoded_vec.end());
        tr.check(decoded == input, "String with null byte");
    }

    // 6. Leading zeros in byte array
    {
        std::vector<unsigned char> input = {0,0,0,1,2,3};
        std::string encoded = Base58::encode(input);
        auto decoded = Base58::decode(encoded);
        tr.check(decoded == input, "Leading zeros in byte array");
    }

    // 7. All possible byte values
    {
        std::vector<unsigned char> input(256);
        for (int i = 0; i < 256; i++) {
            input[i] = i;
        }
        std::string encoded = Base58::encode(input);
        auto decoded = Base58::decode(encoded);
        tr.check(decoded == input, "All 256 byte values");
    }

    // 8. Invalid Base58 input should throw
    {
        try {
            Base58::decode("0OIl"); // invalid characters
            tr.check(false, "Invalid Base58 input throws error");
        } catch (const std::invalid_argument&) {
            tr.check(true, "Invalid Base58 input throws error");
        }
    }

    tr.summary();
    return 0;
}
