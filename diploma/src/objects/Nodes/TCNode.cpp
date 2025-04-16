#include "TCNode.hpp"

namespace node::tc {
  TCNode::TCNode(u_short port) {
    network = std::make_unique<network::UdpNetworkService>(port);
    network->onMessageReceived([this](const std::vector<uint8_t> &data, const network::Endpoint &from) {
      this->onRecv(data, from);
    });
  }
  void TCNode::setConfig( const Config &config ) {
    server.address = config["server"]["ip"];
    server.port = config["server"]["port"];
  }
  void TCNode::initialize() {
    auto header = network::MsgHeader(KEY_HELLO, 0, 0);
    network->send(header, server );
  }
  bool    TCNode::send( const Message &message ) {
    if (message.size() >= DATAGRAM_SIZE) {
      return false;
    }
    return true;
  }
  void TCNode::onRecv( const std::vector<uint8_t> &data,
                       const network::Endpoint    &from ) {
    if ()
  }
}

