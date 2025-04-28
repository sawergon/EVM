//
// Created by Alex on 28.04.2025.
//

#ifndef DIPLOMA_INCLUDE_OBJECTS_COORDINATOR_HPP_
#define DIPLOMA_INCLUDE_OBJECTS_COORDINATOR_HPP_

#include "ConfigParser.hpp"
#include "Router.hpp"

import Unital;
import PPdn;

namespace model::coordinator {

  struct uniParams{
    size_t p;
    size_t l;
    size_t d;
  };

class Coordinator {
  public:
      Coordinator( const uniParams &params, const t_TablePtr& table, const node::t_Logger & logger);
      void setRoutes( router::t_RouterTable & routers, node::t_NodeTable& nodes);
      long needRouters();
  private:
      std::unordered_map<long, long> fiilUni2PPtable(unital::Unital& uni);
      std::shared_ptr<unital::Unital> uni{};
    uniParams params_;
    node::t_Logger logger_;
      t_TablePtr table_;
};

using t_CoordinatorPtr = std::shared_ptr<Coordinator>;
}

#endif  // DIPLOMA_INCLUDE_OBJECTS_COORDINATOR_HPP_
