#include "CommonNode.hpp"

namespace node::common {
  CommonNode::CommonNode( u_short port ) {
    network = std::make_unique<network::UdpNetworkService>( port );
    network->onMessageReceived(
        [this]( const std::vector<uint8_t> &data,
                const network::Endpoint    &from ) { onRecv( data, from ); } );
  }
  void CommonNode::initialize() {
    auto header =
        network::MsgHeader( KEY_HELLO, sizeof( network::Endpoint ), 0 );
    network->send( header, server );
    network->send( network->getLocalEndpoint(), server );
  }
  void CommonNode::onRecv( const std::vector<uint8_t> &data,
                           const network::Endpoint    &from ) {
    switch ( recvMode ) {
    case WaitHeader:
      onWaitHeader( data );
      break;
    case WaitDataHello:
      onWaitDataHello( data );
      break;
    }
  }
  void CommonNode::onWaitHeader( const std::vector<uint8_t> &data ) {
    if ( data.size() != sizeof( network::MsgHeader ) )
      return;
    auto header = network::MsgHeader( data );
    switch ( header.keyWord ) {
    case KEY_HELLO:
      recvMode = WaitDataHello;
      break;
    }
    nowHeader = header;
  }
  void CommonNode::onWaitDataHello( const std::vector<uint8_t> &data ) {
    if ( nowHeader.size == data.size() ) {
      server = network::Endpoint::fromVector(
          { data.begin(), data.begin() + sizeof( network::Endpoint ) } );
      recvMode      = WaitHeader;
      nodeInfo.tnId = convert::from_bytes<uint64_t>(
          { data.begin() + sizeof( network::Endpoint ),
            data.begin() + sizeof( network::Endpoint ) + sizeof( uint64_t ) } );
    }
  }
  void CommonNode::setConfig( const Config &config ) {
    server.address = config["server"]["address"];
    server.port    = config["server"]["port"];
  }
  bool CommonNode::send( const Message &message ) { return false; }

}  // namespace node::common
