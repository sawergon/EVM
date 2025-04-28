#include "Model.hpp"

namespace model {

  Model::Model( const coordinator::uniParams &params, const t_TablePtr &table,
                const node::t_Logger &logger, bool isEncrypt ) {
    m_logger = logger;
    m_coordinator =
        std::make_shared<coordinator::Coordinator>( params, table, logger );
    for ( const auto &[routerId, nodeList] : *table ) {
      m_routers.insert(
          { routerId,
            std::make_shared<router::Router>(
                routerId, nodeList,
                [this]( const std::unordered_map<node::t_NodeId, node::t_NodePtr>
                            &table ) { mergeNodeTable( table ); },
                m_logger ) } );
    }

    std::list<size_t> nodes;
    m_logger( "[Model] Network params: p = " + std::to_string( params.p ) +
              ", l = " + std::to_string( params.l ) +
              ", d = " + std::to_string( params.d ) );
    m_logger( "[Model] Total routers count: " +
              std::to_string( m_coordinator->needRouters() ) );
    if ( m_coordinator->needRouters() != m_routers.size() ) {
      for ( auto i = 0; i < m_coordinator->needRouters(); ++i ) {
        if ( m_routers.find( i ) == m_routers.end() ) {
          m_routers.insert(
              { i,
                std::make_shared<router::Router>(
                    i, nodes,
                    [this]( const std::unordered_map<node::t_NodeId,
                                                     node::t_NodePtr> &table ) {
                      mergeNodeTable( table );
                    },
                    m_logger ) } );
        }
      }
    }

    m_coordinator->setRoutes( m_routers, m_nodes );

    encrypted = isEncrypt;
  }

  void Model::mergeNodeTable(
      const std::unordered_map<node::t_NodeId, node::t_NodePtr> &table ) {
    for ( const auto &pair : table ) {
      m_nodes[pair.first] = pair.second;
    }
  }
  void Model::send( size_t from, size_t to, const std::string &msg ) {
    if (!m_nodes.contains(from) || !m_nodes.contains(to)) {
      m_logger("[Model] No such nodes");
      return;
    }
    m_nodes[from]->sendTo( to, msg );
    m_logger( "[Model] send" + std::to_string( from ) + " -> " +
              std::to_string( to ) + ": " + msg );
  }
  void Model::printNetwork() {
    m_logger( "[Model] realized Network" );
    m_logger( "[Model] Routers count: " + std::to_string( m_routers.size() ) );
    std::string str;
    for ( const auto &pair : m_routers ) {
      str += std::to_string( pair.first ) + ' ';
    }
    m_logger( "[Model] Routers: " + str );
    m_logger( "[Model] Nodes count: " + std::to_string( m_nodes.size() ) );
    str.clear();
    for ( const auto &pair : m_nodes ) {
      str += std::to_string( pair.first ) + ' ';
    }
    m_logger( "[Model] Nodes: " + str );

    for ( const auto &[id, router] : m_routers ) {
    std::string msg{};
      for ( const auto &[node_id, node] : router->getNodes() ) {
        msg += std::to_string( node_id ) + ' ';
      }
      m_logger( "[Model] Router " + std::to_string(id) + " " + msg );
    }
  }

}  // namespace model