//
// Created by Alex on 16.04.2025.
//

#ifndef DIPLOMA_INCLUDE_INTERFACES_IBLOMESCHEME_HPP_
#define DIPLOMA_INCLUDE_INTERFACES_IBLOMESCHEME_HPP_

#include <vector>
#include <cstdint>

namespace Infrastructure::Crypto {

  using PublicKey  = std::vector<uint64_t>;
  using PrivateKey = std::vector<uint64_t>;

  class IBlomScheme {
public:
    virtual ~IBlomScheme()                                     = default;
    virtual std::pair<PublicKey, PrivateKey> generateKeyPair() = 0;
    virtual std::vector<uint8_t> encrypt( const uint8_t *data, size_t size,
                                          const uint8_t *key,
                                          size_t         keySize )     = 0;
    virtual std::vector<uint8_t> decrypt( const uint8_t *data, size_t size,
                                          const uint8_t *key,
                                          size_t         keySize )     = 0;
  };
}

#endif  // DIPLOMA_INCLUDE_INTERFACES_IBLOMESCHEME_HPP_
