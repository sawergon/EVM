//
// Created by Alex on 28.04.2025.
//

#ifndef DIPLOMA_INCLUDE_MODEL_HPP_
#define DIPLOMA_INCLUDE_MODEL_HPP_

#include "BlomePolinome.hpp"
#include "ConfigParser.hpp"
#include "Coordinator.hpp"
#include "Router.hpp"

import Unital;

namespace model {


  class Model {
public:
    Model( const coordinator::uniParams &params, const t_TablePtr &table,
           const node::t_Logger &logger, bool isEncrypt = false, const blome::SchemeParams& blomeParams = {} );
    void setStartTable( const t_TablePtr &table );

    void send( size_t from, size_t to, const std::string &msg );

    void printNetwork();

    ~Model() = default;

private:
    void mergeNodeTable(
        const std::unordered_map<node::t_NodeId, node::t_NodePtr> &table );

    node::t_Logger m_logger;

    node::t_NodeTable             m_nodes;
    router::t_RouterTable         m_routers;
    coordinator::t_CoordinatorPtr m_coordinator{ nullptr };

    std::shared_ptr<unital::Unital> m_uni{ nullptr };

    bool encrypted = false;
  };
}  // namespace model

#endif  // DIPLOMA_INCLUDE_MODEL_HPP_
