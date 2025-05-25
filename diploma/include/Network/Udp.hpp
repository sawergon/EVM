//
// Created by Alex on 16.04.2025.
//

#ifndef DIPLOMA_INCLUDE_NETWORK_UDP_HPP_
#define DIPLOMA_INCLUDE_NETWORK_UDP_HPP_

#include "INetworkSevice.hpp"
#include "msg_headers.hpp"
#include <boost/asio.hpp>
#include <functional>
#include <iostream>
#include <thread>

namespace network {

  class UdpNetworkService final : public INetworkService {
public:
    explicit UdpNetworkService( unsigned short port )
        : m_ioContext()
        , m_socket( m_ioContext, boost::asio::ip::udp::endpoint(
                                     boost::asio::ip::udp::v4(), port ) )
        , m_receiveBuffer( DATAGRAM_SIZE ) {
      startReceive();
      m_ioThread = std::thread( [this]() { m_ioContext.run(); } );
    }

    ~UdpNetworkService() override {
      m_ioContext.stop();
      if ( m_ioThread.joinable() )
        m_ioThread.join();
    }

    void send( const std::vector<uint8_t> &data, const Endpoint &to ) override {
      try {
        auto endpoint = boost::asio::ip::udp::endpoint(
            boost::asio::ip::make_address( to.address ), to.port );

        m_socket.async_send_to(
            boost::asio::buffer( data ), endpoint,
            []( const boost::system::error_code &, size_t ) {} );
      } catch ( const std::exception &e ) {
        handleError( e.what() );
      }
    }

    Endpoint getLocalEndpoint() const {
      return Endpoint{ m_socket.local_endpoint().address().to_string(),
                       m_socket.local_endpoint().port() };
    }

    void onMessageReceived( MessageCallback callback ) override {
      m_callback = std::move( callback );
    }

private:
    boost::asio::io_context        m_ioContext;
    boost::asio::ip::udp::socket   m_socket;
    std::thread                    m_ioThread;
    std::vector<uint8_t>           m_receiveBuffer;
    boost::asio::ip::udp::endpoint m_remoteEndpoint;
    MessageCallback                m_callback;

    void startReceive() {
      m_socket.async_receive_from(
          boost::asio::buffer( m_receiveBuffer ), m_remoteEndpoint,
          [this]( boost::system::error_code ec, std::size_t bytes ) {
            if ( !ec && bytes > 0 ) {
              std::vector<uint8_t> data( m_receiveBuffer.begin(),
                                         m_receiveBuffer.begin() + bytes );

              Endpoint endpoint{ m_remoteEndpoint.address().to_string(),
                                 m_remoteEndpoint.port() };

              if ( m_callback ) {
                m_callback( data, endpoint );
              }
            }
            startReceive();
          } );
    }

    static void handleError( const std::string &message ) {
      // Реализация обработки ошибок
      std::cerr << "Network error: " << message << std::endl;
    }
  };

}  // namespace network

#endif  // DIPLOMA_INCLUDE_NETWORK_UDP_HPP_
