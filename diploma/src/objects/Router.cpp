//
// Created by Alex on 28.04.2025.
//
#include "Router.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace model::router {
Router::Router(t_RouterId routerId,
               const std::list<size_t> &nodes,
               const t_RetNodesCallback &callback,
               const node::t_Logger &logger,
               const std::shared_ptr<unital::Unital> &uni,
               bool isEncrypt) {
  m_uni = uni;
  m_id = routerId;
  m_logger = logger;
  encrypt = isEncrypt;
  for (const auto &node : nodes) {
    std::shared_ptr<node::Node> nodePtr;
    if (encrypt) {
      nodePtr = createEncryptNode(node);
    } else {
      nodePtr = std::make_shared<node::Node>(
        m_id,
        node,
        [this](const std::string &msg) { recvMessage(msg); },
        m_logger);
    }
    m_nodes.insert({node, nodePtr});
  }
  callback(m_nodes);
}

std::pair<long, std::string> parseMsg(const std::string &msg) {
  long number;
  std::string message;

  // Создаем поток для разбора строки
  std::istringstream iss(msg);

  // Извлекаем число до запятой
  char delimiter; // Для хранения символа-разделителя
  if (iss >> number >> delimiter) {
    // Проверяем, что следующий символ - это запятая
    if (delimiter == ',') {
      // Извлекаем оставшуюся часть строки
      std::string temp;
      std::getline(iss, temp); // Читаем до конца строки

      // Удаляем фигурные скобки
      if (!temp.empty() && temp.front() == '{') {
        temp.erase(0, 1); // Удаляем открывающую фигурную скобку
      }
      if (!temp.empty() && temp.back() == '}') {
        temp.erase(temp.size() - 1); // Удаляем закрывающую фигурную скобку
      }
      message = temp; // Присваиваем результат переменной msg
    }
  }
  return {number, message};
}

void Router::recvMessage(const std::string &msg) {
  m_logger("[Router " + std::to_string(m_id) +
    "] received message: " + msg);

  if (!encrypt) {
    auto [to, message] = parseMsg(msg);
    if (!m_hopTable->contains(to)) {
      m_logger("[Router " + std::to_string(m_id) + "]" +
        std::to_string(to) + " is not realized in network");
      return;
    }
    m_hopTable->at(to).publish(std::to_string(to) + ",{" + message + '}');
  } else {
    auto [from, to, message, success] = parseMsgEnc(msg);
    if (!success) {
      m_logger("[Router " + std::to_string(m_id) + "]" +
        "recv incorrect msg");
      return;
    }
    if (!m_hopTable->contains(to)) {
      m_logger("[Router " + std::to_string(m_id) + "]" +
        std::to_string(to) + " is not realized in network");
      return;
    }
    std::pair poolKey = {m_hopTable->at(from).encKeyId, m_hopTable->at(from).keyType};

    std::string recvMsg{};

    if (m_key_pool.contains(poolKey)) {
      std::cout << "[Router " + std::to_string(m_id) + "]" << " Decrypt. Use key id: " << poolKey.first <<
          charFromKeyType(poolKey.second) << std::endl;
      std::vector<uint8_t> text(reinterpret_cast<uint8_t *>(message.data()), reinterpret_cast<uint8_t *>(message.data()) + message.size());
      recvMsg = m_key_pool[poolKey]->decrypt(text);
    } else {
      m_logger("[Router " + std::to_string(m_id) + "]" +
        "recv incorrect msg");
      return;
    }

    m_logger("[Router " + std::to_string(m_id) +
      "] received message: " + recvMsg);

    std::pair endPointKey = {m_hopTable->at(to).encKeyId, m_hopTable->at(to).keyType};
    std::vector<uint8_t> a;
    if (m_key_pool.contains(endPointKey)) {
      std::cout << "[Router " + std::to_string(m_id) + "]" << " Encrypt. Use key id: " << endPointKey.first <<
          charFromKeyType(endPointKey.second) << std::endl;
      a = m_key_pool[endPointKey]->encrypt(recvMsg);
    } else {
      m_logger("[Router " + std::to_string(m_id) + "]" +
        "recv incorrect msg. Unknown destination");
      return;
    }

    std::string encMsg{a.begin(), a.end()};

    std::string pMsg =
        std::to_string(m_id) + "," + std::to_string(to) +
        ",{";
    m_hopTable->at(to).publish(pMsg + encMsg + '}');
  }
}
node::t_NodePtr Router::createEncryptNode(node::t_NodeId node) {
  auto routerBlock = m_uni->getBlockId(m_id);
  auto nodeBlock = m_uni->getBlockId(node);

  kuznechik::t_KeyId keyId = routerBlock.intersection(nodeBlock).to_int();

  kuznechik::t_Key key;

  std::pair poolKey = {keyId, KeyType::Uni};
  if (m_key_pool.contains(poolKey)) {
    key = m_key_pool[poolKey]->getKey();
  } else {
    key = kuznechik::generate_random_key();
    m_key_pool[poolKey] = std::make_shared<kuznechik::KuznechikCipher>(key);
  }

  node::t_KeyInfo info = {keyId, key};

  return std::make_shared<node::Node>(
    m_id,
    node,
    [this](const std::string &msg) { recvMessage(msg); },
    m_logger,
    true,
    info);
}
void Router::addPpPreKey(const node::t_KeyInfo &keyInfo) {
  m_key_pool[{keyInfo.id, KeyType::PP}] =
      std::make_shared<kuznechik::KuznechikCipher>(keyInfo.key);
}
} // namespace model::router
