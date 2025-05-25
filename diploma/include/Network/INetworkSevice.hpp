//
// Created by Alex on 16.04.2025.
//

#ifndef DIPLOMA_INCLUDE_INTERFACES_INETWORKSEVICE_HPP_
#define DIPLOMA_INCLUDE_INTERFACES_INETWORKSEVICE_HPP_

#include <cstdint>
#include <functional>
#include <string>
#include <vector>
namespace network {
  struct Endpoint {
    std::string address;
    uint16_t    port;
    bool        operator==( const Endpoint &other ) const {
             return address == other.address && port == other.port;
    }

    bool operator!=( const Endpoint &other ) const {
      return !( *this == other );
    }

    operator std::vector<uint8_t>() const {
      std::vector<uint8_t> result;
      result.push_back( port & 0xFF );
      result.push_back( port >> 8 );
      result.insert( result.end(), address.begin(), address.end() );
      return result;
    }

    static Endpoint fromVector( const std::vector<uint8_t> &vec ) {
      Endpoint result;
      result.port = vec[0] + ( vec[1] << 8 );
      result.address.assign( vec.begin() + 2, vec.end() );
      return result;
    }
  };

  // Тип коллбэка, вызываемого при получении сообщения
  using MessageCallback =
      std::function<void( const std::vector<uint8_t> &, const Endpoint & )>;

  class INetworkService {
public:
    virtual ~INetworkService()                                 = default;
    virtual void send( const std::vector<uint8_t> &data,
                       const Endpoint             &to )                    = 0;
    virtual void onMessageReceived( MessageCallback callback ) = 0;
  };
}  // namespace network
#endif  // DIPLOMA_INCLUDE_INTERFACES_INETWORKSEVICE_HPP_
