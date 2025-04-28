//
// Created by Alex on 28.04.2025.
//

#ifndef DIPLOMA_INCLUDE_OBJECTS_ROUTER_HPP_
#define DIPLOMA_INCLUDE_OBJECTS_ROUTER_HPP_

#include "Node.hpp"
#include <list>
#include <memory>

namespace model::router {

  using t_RouterId       = size_t;
  using t_PublishMessage = std::function<void( const std::string & )>;
  using t_RoutesTable =
      std::shared_ptr<std::unordered_map<size_t, t_PublishMessage>>;

  using t_RetNodesCallback = std::function<void(
      const std::unordered_map<node::t_NodeId, node::t_NodePtr> & )>;
  class Router {
public:
    Router( t_RouterId routerId, const std::list<size_t> &nodes,
            const t_RetNodesCallback &callback, const node::t_Logger &logger );
    void recvMessage( const std::string &msg ) const;

    void setHopTable( const t_RoutesTable &hopTable ) { m_hopTable = hopTable; }

    std::unordered_map<node::t_NodeId, node::t_NodePtr> getNodes() {
      return m_nodes;
    }

    bool isAchived(node::t_NodeId id) {
      return m_nodes.find(id) != m_nodes.end();
    }

private:
    node::t_Logger                                      m_logger;
    t_RoutesTable                                       m_hopTable{};
    t_RouterId                                          m_id;
    std::unordered_map<node::t_NodeId, node::t_NodePtr> m_nodes;
  };

  using t_RouterPtr = std::shared_ptr<Router>;
  using t_RouterTable =
      std::unordered_map<router::t_RouterId, router::t_RouterPtr>;
}  // namespace model::router

#endif  // DIPLOMA_INCLUDE_OBJECTS_ROUTER_HPP_
