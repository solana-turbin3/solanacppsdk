#pragma once
#include <string>
#include <vector>
#include <stdexcept>

namespace solana {

class Base58 {
public:
    // Encode from vector of bytes
    static std::string encode(const std::vector<unsigned char>& input);

    // Decode to vector of bytes
    static std::vector<unsigned char> decode(const std::string& input);

    // String-friendly helpers
    static std::string encodeString(const std::string& input);
    static std::string decodeString(const std::string& input);

private:
    static const char* const ALPHABET;
    static const signed char ALPHABET_MAP[128];
};

}
