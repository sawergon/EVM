//
// Created by Alex on 28.04.2025.
//

#ifndef DIPLOMA_INCLUDE_OBJECTS_ROUTER_HPP_
#define DIPLOMA_INCLUDE_OBJECTS_ROUTER_HPP_

#include "Node.hpp"
#include <list>
#include <memory>
import Unital;

namespace model::router {

  using t_RouterId       = size_t;
  using t_PublishMessage = std::function<void( const std::string & )>;
  struct routeStruct {
    size_t encKeyId;
    t_PublishMessage publish;
  };
  using t_RoutesTable =
      std::shared_ptr<std::unordered_map<size_t, routeStruct>>;

  using t_RetNodesCallback = std::function<void(
      const std::unordered_map<node::t_NodeId, node::t_NodePtr> & )>;
  class Router {
public:
    Router( t_RouterId routerId, const std::list<size_t> &nodes,
            const t_RetNodesCallback &callback, const node::t_Logger &logger,
            const std::shared_ptr<unital::Unital> &uni,
            bool                                   isEncrypt = false );
    void recvMessage( const std::string &msg );

    void setHopTable( const t_RoutesTable &hopTable ) { m_hopTable = hopTable; }

    std::unordered_map<node::t_NodeId, node::t_NodePtr> getNodes() {
      return m_nodes;
    }

    bool isAchived( node::t_NodeId id ) {
      return m_nodes.find( id ) != m_nodes.end();
    }

    void addPreKey( const node::t_KeyInfo &keyInfo );

private:
    node::t_NodePtr createEncryptNode( node::t_NodeId node );

    node::t_Logger                                      m_logger{};
    t_RoutesTable                                       m_hopTable{};
    t_RouterId                                          m_id{};
    std::unordered_map<node::t_NodeId, node::t_NodePtr> m_nodes{};
    bool                                                encrypt = false;

    std::unordered_map<kuznechik::t_KeyId,
                       std::shared_ptr<kuznechik::KuznechikCipher>>
        m_key_pool{};
    std::unordered_map<kuznechik::t_KeyId,
                       std::shared_ptr<kuznechik::KuznechikCipher>>
                                    m_pp_key_pool{};
    std::shared_ptr<unital::Unital> m_uni{ nullptr };
  };

  using t_RouterPtr = std::shared_ptr<Router>;
  using t_RouterTable =
      std::unordered_map<router::t_RouterId, router::t_RouterPtr>;
}  // namespace model::router

#endif  // DIPLOMA_INCLUDE_OBJECTS_ROUTER_HPP_
