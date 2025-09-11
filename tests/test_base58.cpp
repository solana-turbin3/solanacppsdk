#include "solana/base58.hpp"
#include <iostream>
#include <vector>
#include <cassert>

using namespace solana;

int main() {
    std::cout << "=== Base58 Encode/Decode Tests ===\n\n";

    // Helper lambda for testing string encoding/decoding
    auto testString = [](const std::string& input) {
        std::string encoded = base58encode_str(input);
        std::string decoded = base58decode_str(encoded);
        std::cout << "Original: [" << input << "]\n"
                  << "Encoded : [" << encoded << "]\n"
                  << "Decoded : [" << decoded << "]\n\n";
        assert(decoded == input);
    };

    // 1. Normal string
    testString("Hello Solana!");

    // 2. Empty string
    testString("");

    // 3. String with spaces
    testString("   ");

    // 4. String with special characters
    testString("!@#$%^&*()_+-={}[];:,.<>/?");

    // 5. String with null byte inside
    std::string null_byte_str = std::string("abc\0def", 7); // include null byte
    std::vector<unsigned char> vec(null_byte_str.begin(), null_byte_str.end());
    std::string encoded_null = base58encode(vec);
    std::vector<unsigned char> decoded_null_vec = base58decode(encoded_null);
    std::string decoded_null(decoded_null_vec.begin(), decoded_null_vec.end());
    assert(decoded_null == null_byte_str);
    std::cout << "Null byte string encoded/decoded correctly.\n\n";

    // 6. Leading zeros in byte array
    std::vector<unsigned char> leading_zeros = {0,0,0,1,2,3};
    std::string encoded_zeros = base58encode(leading_zeros);
    std::vector<unsigned char> decoded_zeros = base58decode(encoded_zeros);
    assert(decoded_zeros == leading_zeros);
    std::cout << "Leading zeros encoded/decoded correctly.\n\n";

    // 7. All possible byte values
    std::vector<unsigned char> all_bytes(256);
    for (int i = 0; i < 256; i++) all_bytes[i] = i;
    std::string encoded_all = base58encode(all_bytes);
    std::vector<unsigned char> decoded_all = base58decode(encoded_all);
    assert(decoded_all == all_bytes);
    std::cout << "All 256 byte values encoded/decoded correctly.\n\n";

    // 8. Invalid Base58 input (should throw)
    try {
        base58decode("0OIl"); // invalid chars
        assert(false); // should not reach
    } catch (const std::invalid_argument&) {
        std::cout << "Invalid input correctly threw exception.\n\n";
    }

    std::cout << "=== All Tests Passed ===\n";
    return 0;
}
