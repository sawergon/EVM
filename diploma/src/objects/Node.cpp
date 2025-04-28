#include "Node.hpp"

namespace model::node {

  Node::Node( size_t routerId, t_NodeId nodeId, const t_PublishFnc &fun,
              const t_Logger &logger ) {
    linkedRouter = routerId;
    publish      = fun;
    id           = nodeId;
    m_logger     = logger;
  }
  void Node::recvMessage( const std::string &message ) {
    m_logger( "[Node " + std::to_string( id ) + "] with router " +
              std::to_string( linkedRouter ) +
              " received message: " + message );
  }
  void Node::sendTo( t_NodeId endpoint, const std::string &message ) {
    m_logger( "[Node " + std::to_string( id ) + "] " + "send " + message +
              " to " + std::to_string( endpoint ) );
    publish( std::to_string( endpoint ) + ",{" + message + "}" );
  }
}  // namespace model::node