//
// Created by Alex on 28.04.2025.
//

#ifndef DIPLOMA_INCLUDE_OBJECTS_NODE_HPP_
#define DIPLOMA_INCLUDE_OBJECTS_NODE_HPP_

#include "Kuznechik.hpp"
#include "parser.hpp"
// #include "stribog256.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include <utility>

namespace model::node {

  using t_NodeId = size_t;

  using t_PublishFnc = std::function<void( const std::string & )>;

  using t_Logger = std::function<void( const std::string & )>;

  struct t_KeyInfo {
    kuznechik::t_KeyId id;
    kuznechik::t_Key   key;
  };


  class Node {
public:
    Node( size_t routerId, t_NodeId nodeId, const t_PublishFnc &fun,
          const t_Logger &logger, bool isEncrypt = false,
          const t_KeyInfo &key = {} );

    void setPublishFnc( const t_PublishFnc &fun ) { publish = fun; }

    void recvMessage( const std::string &message );

    void sendTo( t_NodeId endpoint, const std::string &message );

    [[nodiscard]] t_NodeId getRouter() const { return linkedRouter; }

private:
    void     initBlomeScheme();
    t_Logger m_logger{};
    t_NodeId id{};
    size_t   linkedRouter{};

    bool encrypt = false;

    t_PublishFnc publish{ nullptr };

    kuznechik::t_Key                            m_key{};
    kuznechik::t_KeyId                          m_keyId{};
    std::shared_ptr<kuznechik::KuznechikCipher> cipher{ nullptr };
  };

  using t_NodePtr   = std::shared_ptr<Node>;
  using t_NodeTable = std::unordered_map<node::t_NodeId, node::t_NodePtr>;
}  // namespace model::node

#endif  // DIPLOMA_INCLUDE_OBJECTS_NODE_HPP_
