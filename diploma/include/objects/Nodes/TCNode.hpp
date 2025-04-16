//
// Created by Alex on 16.04.2025.
//

#ifndef DIPLOMA_INCLUDE_OBJECTS_NODES_TCNODE_HPP_
#define DIPLOMA_INCLUDE_OBJECTS_NODES_TCNODE_HPP_

#include "Node.hpp"
#include "Udp.hpp"
#include <memory>
#include "msg_headers.hpp"

namespace node::tc {
  struct NodeInfo {
    uint64_t id;
  };
  class TCNode final : public Node {
public:
    TCNode(u_short port);
    void setConfig(const node::Config &config) override;
    void initialize() override;
    bool    send( const Message &message) override;
    ~TCNode() override = default;
private:
    void onRecv(const std::vector<uint8_t>& data, const network::Endpoint& from);
    std::unique_ptr<network::UdpNetworkService> network;
    network::Endpoint                           server{};
  };
}

#endif  // DIPLOMA_INCLUDE_OBJECTS_NODES_TCNODE_HPP_
