#include "Coordinator.hpp"

namespace model::coordinator {

  Coordinator::Coordinator( const uniParams &params, const t_TablePtr &table,
                            const node::t_Logger                  &logger,
                            const std::shared_ptr<unital::Unital> &unital,
                            bool                                   isEncrypt ) {
    table_  = table;
    logger_ = logger;
    params_ = params;
    uni     = unital;
    encrypt = isEncrypt;
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
    auto [p, l] = gotPL( uni->getN() );
    if (p == 1 && l == 1) {
      p++;
    }
    ppdn::PPdn pp( static_cast<long>(params_.d), p, l );

    auto pp_uni = fiilUni2PPtable();
    /// для каждого блока параллельнгого класса составляем таблицу маршрутов
    for ( auto &[id_i, router] : routers ) {
      router::t_RoutesTable routes = std::make_shared<
          std::unordered_map<size_t, router::routeStruct>>();
      auto tcBlockId = uni->getBlockId( id_i );
      /// Проективная геометрия для роутеров
      auto tc_pp_id = pp.getBlockId( id_i );
      for ( auto &[id_j, router_j] : routers ) {
        size_t key_id = 0;

        if ( encrypt ) {
          auto               other_pp_id = pp.getBlockId( id_j );
          key_id =
              tc_pp_id.intersect( other_pp_id ).to_int();
          kuznechik::t_Key key  = kuznechik::generate_random_key();
          node::t_KeyInfo  info = { key_id, key };
          router->addPreKey( info );
          router_j->addPreKey( info );
        }
        routes->insert( { id_j, {key_id, [&]( const std::string &msg ) {
                                   router_j->recvMessage( msg );
                                 } } } );
      }

      /// для каждого реализованного узла в сети
      for ( auto &[id, ptr] : nodes ) {
        auto targetBlockId = uni->getBlockId( id );
        /// если узел соеденен с текущим выбранным блоком параллельнгого класса
        if ( router->isAchived( id ) &&
             tcBlockId.intersection( targetBlockId ).isValid() ) {
          /// добавляем маршрут в таблицу
          routes->insert( { id, {0, [&]( const std::string &msg ) {
                              ptr->recvMessage( msg );
                            } } } );
        } else {

          auto elseTcBlockId = uni->getBlockId( ptr->getRouter() );
          /// если нашли пересечение, то добавляем путь до блока
          /// параллеьльного класса
          if ( routers[ptr->getRouter()]->isAchived( id ) &&
               elseTcBlockId.intersection( targetBlockId ).isValid() ) {
            routes->insert( { id, {0, [&]( const std::string &msg ) {
                                routers[ptr->getRouter()]->recvMessage( msg );
                              } } } );
          }
        }
      }

      routers[id_i]->setHopTable( routes );
    }
  }

  std::unordered_map<long, long> Coordinator::fiilUni2PPtable() {
    std::unordered_map<long, long> res{};

    auto tcSize = uni->getS();
    for ( auto i = 0; i < tcSize; ++i ) {
      auto uni_id = uni->getBlockId( i ).to_int();
      res[uni_id] = i;
      i           = uni_id;
    }
    return res;
  }
  long Coordinator::needRouters() { return uni->getS(); }

}  // namespace model::coordinator