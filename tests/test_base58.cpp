#include "solana/base58.h"
#include <cassert>
#include <iostream>

int main()
{
  std::vector<unsigned char> data = {0, 1, 2, 3, 4};
  std::string encoded = solana::base58encode(data);
  std::vector<unsigned char> decoded = solana::base58decode(encoded);

  assert(decoded == data);

  std::cout << "Base58 encode/decode test passed: " << encoded << std::endl;
  return 0;
}
