
#ifndef DIPLOMA_INCLUDE_OBJECTS_NODES_COMMONNODE_HPP_
#define DIPLOMA_INCLUDE_OBJECTS_NODES_COMMONNODE_HPP_

#include "Node.hpp"
#include "Udp.hpp"
#include "msg_headers.hpp"
#include "convertors.hpp"
#include <memory>

namespace node::common {
  struct NodeInfo {
    uint64_t id; /// идентификатор блока
    uint64_t tnId; /// идентификатор роутера
  };

  enum RecvMode {
    WaitHeader = 0,
    WaitDataHello = 1
  };

  class CommonNode final : public Node {
public:
    CommonNode(u_short port);
    void    setConfig( const node::Config &config ) override;
    void    initialize() override;
    bool    send( const Message &message ) override;
    ~CommonNode() override = default;
private:
    void onWaitDataHello(const std::vector<uint8_t>& data);
    void onWaitHeader(const std::vector<uint8_t>& data);
    void onRecv(const std::vector<uint8_t>& data, const network::Endpoint& from);
    std::unique_ptr<network::UdpNetworkService> network;
    network::Endpoint server;
    NodeInfo nodeInfo;
    RecvMode recvMode = RecvMode::WaitHeader;
    network::MsgHeader nowHeader{};
  };
}  // namespace node::common

#endif  // DIPLOMA_INCLUDE_OBJECTS_NODES_COMMONNODE_HPP_
