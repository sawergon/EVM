//
// Created by Alex on 16.04.2025.
//

#ifndef DIPLOMA_INCLUDE_OBJECTS_NODE_HPP_
#define DIPLOMA_INCLUDE_OBJECTS_NODE_HPP_

#include <string>
#include "../../json.hpp"

namespace node {
  using Config = nlohmann::json;
  using Message = std::string;
  struct ReturnMessage {
    Message message;
    bool error = false;
  };
  class Node {
public:
    virtual void setConfig(const Config& config) = 0;
    virtual void initialize() = 0;
    virtual bool send(const Message& message) = 0;
    virtual ~Node() = 0;
  };

}  // namespace node
#endif  // DIPLOMA_INCLUDE_OBJECTS_NODE_HPP_
