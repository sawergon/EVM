//
// Created by Alex on 28.04.2025.
//

#ifndef DIPLOMA_INCLUDE_OBJECTS_NODE_HPP_
#define DIPLOMA_INCLUDE_OBJECTS_NODE_HPP_

#include <functional>
#include <iostream>
#include <memory>
#include <utility>

namespace model::node {

  using t_NodeId = size_t;

  using t_PublishFnc = std::function<void( const std::string & )>;

  using t_Logger = std::function<void( const std::string & )>;


  class Node {
public:
    Node( size_t routerId, t_NodeId nodeId, const t_PublishFnc &fun,
          const t_Logger &logger );

    void setPublishFnc( const t_PublishFnc &fun ) { publish = fun; }

    void recvMessage( const std::string &message );

    void sendTo( t_NodeId endpoint, const std::string &message );

    t_NodeId getRouter() { return linkedRouter; }

private:
    t_Logger m_logger{};
    t_NodeId id{};
    size_t   linkedRouter{};

    t_PublishFnc publish{ nullptr };
  };

  using t_NodePtr   = std::shared_ptr<Node>;
  using t_NodeTable = std::unordered_map<node::t_NodeId, node::t_NodePtr>;
}  // namespace model::node

#endif  // DIPLOMA_INCLUDE_OBJECTS_NODE_HPP_
