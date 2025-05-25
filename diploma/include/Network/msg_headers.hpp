//
// Created by Alex on 16.04.2025.
//

#ifndef DIPLOMA_INCLUDE_NETWORK_MSG_HEADERS_HPP_
#define DIPLOMA_INCLUDE_NETWORK_MSG_HEADERS_HPP_

#include <cstdint>
#include <vector>

#define DATAGRAM_SIZE 2048

#define KEY_HELLO 0x0001

namespace network {

  struct MsgHeader {
    uint16_t keyWord{};
    uint16_t size{};
    uint16_t datagramAmount{};

    MsgHeader() = default;

    MsgHeader( uint16_t keyWord, uint16_t size, uint16_t datagramAmount )
        : keyWord( keyWord )
        , size( size )
        , datagramAmount( datagramAmount ) {}

    operator std::vector<uint8_t>() {
      std::vector<uint8_t> header;
      header.push_back( keyWord >> 8 );
      header.push_back( keyWord & 0xFF );
      header.push_back( size >> 8 );
      header.push_back( size & 0xFF );
      header.push_back( datagramAmount >> 8 );
      header.push_back( datagramAmount & 0xFF );
      return header;
    }

    MsgHeader( const std::vector<uint8_t> &vec ) {
      keyWord        = vec[0] << 8 | vec[1];
      size           = vec[2] << 8 | vec[3];
      datagramAmount = vec[4] << 8 | vec[5];
    }
  };

  struct Server2NodeHelloAnswer {
    uint64_t id;        /// идентификатор блока
    uint64_t routerId;  /// идентификатор роутера
  };
}  // namespace network

#endif  // DIPLOMA_INCLUDE_NETWORK_MSG_HEADERS_HPP_
