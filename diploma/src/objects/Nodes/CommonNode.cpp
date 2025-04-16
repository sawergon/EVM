#include "CommonNode.hpp"

namespace node::common {
  CommonNode::CommonNode( u_short port ) {
    network = std::make_unique<network::UdpNetworkService>( port );
    network->onMessageReceived(
        [this]( const std::vector<uint8_t> &data,
                const network::Endpoint    &from ) { onRecv( data, from ); } );
  }
  void CommonNode::initialize() {
    auto header = network::MsgHeader( KEY_HELLO, 0, 0 );
    network->send( header, server );
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
    auto header = network::MsgHeader( data );
    if ( header.keyWord == KEY_HELLO ) {
      recvMode  = WaitDataHello;
      nowHeader = header;
    }
  }
  void CommonNode::onWaitDataHello( const std::vector<uint8_t> &data ) {
    if (nowHeader.size == data.size()) {

    }
  }

}  // namespace node::common
