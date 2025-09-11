#include "solana/base58.h"
#include <stdexcept>

namespace solana
{
  const char *const ALPHABET =
      "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

  const signed char ALPHABET_MAP[128] = {
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, -1, -1, -1, -1, -1, -1,
      -1, 9, 10, 11, 12, 13, 14, 15, 16, -1, 17, 18, 19, 20, 21, -1,
      22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, -1, -1, -1, -1, -1,
      -1, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, -1, 44, 45, 46,
      47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, -1, -1, -1, -1, -1};

  std::string base58encode(const std::vector<unsigned char> &input)
  {
    if (input.empty())
      return "";

    std::vector<unsigned char> digits(input.size() * 137 / 100 + 1);
    int digitslen = 1;

    for (size_t i = 0; i < input.size(); i++)
    {
      unsigned int carry = input[i];
      for (int j = 0; j < digitslen; j++)
      {
        carry += (unsigned int)(digits[j]) << 8;
        digits[j] = (unsigned char)(carry % 58);
        carry /= 58;
      }
      while (carry > 0)
      {
        digits[digitslen++] = (unsigned char)(carry % 58);
        carry /= 58;
      }
    }

    std::string result;
    // leading zeros
    for (size_t i = 0; i < input.size() && input[i] == 0; i++)
    {
      result.push_back('1');
    }
    // reverse
    for (int i = digitslen - 1; i >= 0; i--)
    {
      result.push_back(ALPHABET[digits[i]]);
    }
    return result;
  }

  std::vector<unsigned char> base58decode(const std::string &input)
  {
    if (input.empty())
      return {};

    std::vector<unsigned char> result(1, 0);

    for (char c : input)
    {
      if (c & 0x80 || ALPHABET_MAP[(int)c] == -1)
      {
        throw std::invalid_argument("Invalid Base58 character");
      }
      unsigned int carry = ALPHABET_MAP[(int)c];
      for (size_t j = 0; j < result.size(); j++)
      {
        carry += (unsigned int)(result[j]) * 58;
        result[j] = (unsigned char)(carry & 0xff);
        carry >>= 8;
      }
      while (carry > 0)
      {
        result.push_back((unsigned char)(carry & 0xff));
        carry >>= 8;
      }
    }

    // handle leading zeros
    int leadingZeros = 0;
    for (char c : input)
    {
      if (c == '1')
        leadingZeros++;
      else
        break;
    }
    std::vector<unsigned char> decoded(leadingZeros, 0);
    for (int i = result.size() - 1; i >= 0; i--)
    {
      decoded.push_back(result[i]);
    }
    return decoded;
  }
}
