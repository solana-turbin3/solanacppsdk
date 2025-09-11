#pragma once
#include <string>
#include <vector>

namespace solana
{
  std::string base58encode(const std::vector<unsigned char> &input);
  std::vector<unsigned char> base58decode(const std::string &input);
}
