//
// Created by Alex on 28.04.2025.
//
#include "Router.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace model::router {
  Router::Router( t_RouterId routerId, const std::list<size_t> &nodes,
                  const t_RetNodesCallback &callback,
                  const node::t_Logger     &logger ) {
    m_id     = routerId;
    m_logger = logger;
    for ( const auto &node : nodes ) {
      m_nodes.insert(
          { node, std::make_shared<node::Node>(
                      m_id, node,
                      [this]( const std::string &msg ) { recvMessage( msg ); },
                      m_logger ) } );
    }
    callback( m_nodes );
  }

  std::pair<long, std::string> parseMsg(const std::string& msg) {
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

  void Router::recvMessage( const std::string &msg ) const {
    m_logger( "[Router " + std::to_string( m_id ) +
              "] received message: " + msg );
    auto [to, message] = parseMsg(msg);
    if (!m_hopTable->contains(to)) {
      m_logger("[Router " + std::to_string( m_id ) +
                "]" + std::to_string(to) + " is not realized in network");
    } else {
      m_hopTable->at( to )( std::to_string( to ) + ",{" + message + '}' );
    }
  }

}  // namespace model::router