#include "Coordinator.hpp"

namespace model::coordinator {

  Coordinator::Coordinator( const uniParams &params, const t_TablePtr &table,
                            const node::t_Logger &logger ) {
    table_  = table;
    logger_ = logger;
    params_ = params;
    uni     = std::make_shared<unital::Unital>( params_.p, params_.l );
  }

  std::pair<long, long> gotPL( long n ) {
    for ( long p = 1; p < n - 1; ++p ) {
      for ( long l = 1; l < n - 1; ++l ) {
        if ( p + l == n )
          return { p, l };
      }
    }
    return { n - 1, 1 };
  }

  void Coordinator::setRoutes( router::t_RouterTable &routers,
                               node::t_NodeTable     &nodes ) {
    /// для каждого блока параллельнгого класса составляем таблицу маршрутов
    for ( auto &[id_i, router] : routers ) {
      router::t_RoutesTable routes = std::make_shared<
          std::unordered_map<size_t, router::t_PublishMessage>>();
      auto tcBlockId = uni->getBlockId( id_i );
      /// Проективная геометрия для роутеров
      for ( auto &[id_j, router_j] : routers ) {
        routes->insert( { id_j, [&]( const std::string &msg ) {
                           router_j->recvMessage( msg );
                         } } );
      }

      /// для каждого реализованного узла в сети
      for ( auto &[id, ptr] : nodes ) {
        auto targetBlockId = uni->getBlockId( id );
        /// если узел соеденен с текущим выбранным блоком параллельнгого класса
        if ( router->isAchived( id ) &&
             tcBlockId.intersection( targetBlockId ).isValid() ) {
          /// добавляем маршрут в таблицу
          routes->insert( { id, [&]( const std::string &msg ) {
                             ptr->recvMessage( msg );
                           } } );
        } else {

          auto elseTcBlockId = uni->getBlockId( ptr->getRouter() );
          /// если нашли пересечение, то добавляем путь до блока
          /// параллеьльного класса
          if ( routers[ptr->getRouter()]->isAchived( id ) &&
               elseTcBlockId.intersection( targetBlockId ).isValid() ) {
            routes->insert( { id, [&]( const std::string &msg ) {
                               routers[ptr->getRouter()]->recvMessage( msg );
                             } } );
          }
        }
      }

      routers[id_i]->setHopTable( routes );
    }
  }

  std::unordered_map<long, long> Coordinator::fiilUni2PPtable(
      unital::Unital &uni ) {
    std::unordered_map<long, long> res{};

    auto tcSize = uni.getS();
    for ( auto i = 0; i < tcSize; ++i ) {
      res[uni.getBlockId( i ).to_int()] = i;
    }
    return res;
  }
  long Coordinator::needRouters() { return uni->getS(); }

}  // namespace model::coordinator