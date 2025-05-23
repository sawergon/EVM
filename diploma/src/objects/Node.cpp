#include "Node.hpp"

namespace model::node {

  Node::Node( size_t routerId, t_NodeId nodeId, const t_PublishFnc &fun,
              const t_Logger &logger, bool isEncrypt, const t_KeyInfo &key ) {
    linkedRouter = routerId;
    publish      = fun;
    id           = nodeId;
    m_logger     = logger;
    encrypt      = isEncrypt;
    m_key        = key.key;
    m_keyId      = key.id;
    if ( encrypt ) {
      cipher = std::make_unique<kuznechik::KuznechikCipher>( key.key );
      initBlomeScheme();
    }
  }
  void Node::recvMessage( const std::string &message ) {
    m_logger( "[Node " + std::to_string( id ) + "] with router " +
              std::to_string( linkedRouter ) +
              " received message: " + message );
  }
  void Node::sendTo( t_NodeId endpoint, const std::string &message ) {
    m_logger( "[Node " + std::to_string( id ) + "] " + "send " + message +
              " to " + std::to_string( endpoint ) );
    if ( !encrypt ) {
      publish( std::to_string( endpoint ) + ",{" + message + "}" );
    } else {
      auto        msg  = cipher->encrypt( message );
      std::string pMsg = std::to_string( id ) + "," +
                         std::to_string( endpoint ) + "," +
                         std::to_string( m_keyId ) + ",{" +
                         std::string( msg.begin(), msg.end() ) + "}";

      m_logger( "[Node " + std::to_string( id ) + "] publish transaction " +
                pMsg );
      publish( pMsg );
    }
  }
  void Node::initBlomeScheme() {}
}  // namespace model::node