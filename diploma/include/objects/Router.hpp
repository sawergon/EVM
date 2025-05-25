//
// Created by Alex on 28.04.2025.
//

#ifndef DIPLOMA_INCLUDE_OBJECTS_ROUTER_HPP_
#define DIPLOMA_INCLUDE_OBJECTS_ROUTER_HPP_

#include "BlomePolinome.hpp"
#include "Node.hpp"
#include "parser.hpp"
#include <list>
#include <map>
#include <memory>

import Unital;

namespace model::router {
  using t_RouterId       = size_t;
  using t_PublishMessage = std::function<void( const std::string & )>;

  struct routeStruct {
    size_t           encKeyId;
    KeyType          keyType;
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
            const std::shared_ptr<unital::Unital> &uni, bool isEncrypt = false,
            const blome::SchemeParams &blomeParams = {} );
    void recvMessage( const std::string &msg );

    void setHopTable( const t_RoutesTable &hopTable ) {
      m_hopTable = hopTable;
      std::cout << "[Router " << m_id << "] Set hop table" << std::endl;
      for ( const auto &item : *m_hopTable ) {
        kuznechik::t_Key key =
            m_key_pool[{ item.second.encKeyId, item.second.keyType }]->getKey();

        std::string keyStr =
            std::string( reinterpret_cast<char *>( key.data() ),
                         reinterpret_cast<char *>( key.data() ) + key.size() );
        std::cout << "[Router " << m_id << "] " << item.first << " -> "
                  << item.second.encKeyId
                  << charFromKeyType( item.second.keyType )
                  << " Key: " << keyStr << std::endl;
      }
    }

    std::unordered_map<node::t_NodeId, node::t_NodePtr> getNodes() {
      return m_nodes;
    }

    bool isAchived( node::t_NodeId id ) {
      return m_nodes.find( id ) != m_nodes.end();
    }

    void addPpPreKey( const node::t_KeyInfo &keyInfo );

    bool connected( node::t_NodeId id ) {
      return m_hopTable != nullptr &&
             m_hopTable->find( id ) != m_hopTable->end();
    }

private:
    bool checkTransitRequest( bool success, long to );

    bool checkKeyRequest( node::t_NodeId to );
    void makeKeys( node::t_NodeId from, node::t_NodeId to,
                   const std::string &msg );

    bool decryptRecvMsg( const std::pair<node::t_NodeId, KeyType> &fromTo,
                         const std::string &msg, std::string &recvMsg );
    bool encryptSendMsg( const std::pair<node::t_NodeId, KeyType> &fromTo,
                         const std::string &msg, std::string &encMsg );

    node::t_NodePtr createEncryptNode( node::t_NodeId node );

    node::t_Logger                                      m_logger{};
    t_RoutesTable                                       m_hopTable{};
    t_RouterId                                          m_id{};
    std::unordered_map<node::t_NodeId, node::t_NodePtr> m_nodes{};
    bool                                                encrypt = false;

    std::map<std::pair<kuznechik::t_KeyId, KeyType>,
             std::shared_ptr<kuznechik::KuznechikCipher>>
        m_key_pool{};

    std::map<std::pair<t_RouterId, t_RouterId>,
             std::pair<kuznechik::t_KeyId, KeyType>>
        m_key_use{};

    std::shared_ptr<unital::Unital> m_uni{ nullptr };

    blome::SchemeParams blomeParams{};
  };

  using t_RouterPtr = std::shared_ptr<Router>;
  using t_RouterTable =
      std::unordered_map<router::t_RouterId, router::t_RouterPtr>;
}  // namespace model::router

#endif  // DIPLOMA_INCLUDE_OBJECTS_ROUTER_HPP_
