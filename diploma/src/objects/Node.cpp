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
      std::cout << "[Node " << id << "] is encrypt. Linked router: " << linkedRouter << " Use key id: " << m_keyId << "U" << std::endl;
      cipher = std::make_unique<kuznechik::KuznechikCipher>( key.key );
      initBlomeScheme();
    }
  }
  void Node::recvMessage( const std::string &message ) {
    m_logger( "[Node " + std::to_string( id ) + "] received message: " + message );

    if ( encrypt ) {
      auto [from, to, msg, success] = parseMsgEnc( message );
      if ( !success ) {
        m_logger( "[Node " + std::to_string( id ) + "]" + "recv incorrect msg" );
        return;
      }

      std::cout << "[Node " << id << "] Decrypt. Use key id: " << m_keyId << "U" << std::endl;
      std::string recvMsg = cipher->decrypt( std::vector<uint8_t>( msg.begin(), msg.end() ) );
      m_logger( "[Node " + std::to_string( id ) + "]" + "message data: " + recvMsg );
    }
  }
  void Node::sendTo( t_NodeId endpoint, const std::string &message ) {
    m_logger( "[Node " + std::to_string( id ) + "] " + "send " + message +
              " to " + std::to_string( endpoint ) );
    if ( !encrypt ) {
      publish( std::to_string( endpoint ) + ",{" + message + "}" );
    } else {
      std::cout  << "[Node " << id << "] Use key id: " << m_keyId << "U Key value: " << std::string(m_key.begin(), m_key.end()) << std::endl;
      auto        msg  = cipher->encrypt( message );
      std::cout << "[Node " << id << "] Check encryption: " << cipher->decrypt(msg) << std::endl;
      std::string pMsg = std::to_string( id ) + "," +
                         std::to_string( endpoint ) + ",{" +
                         std::string( msg.begin(), msg.end() ) + "}";

      m_logger( "[Node " + std::to_string( id ) + "] publish transaction " +
                pMsg );
      publish( pMsg );
    }
  }
  void Node::initBlomeScheme() {}
}  // namespace model::node