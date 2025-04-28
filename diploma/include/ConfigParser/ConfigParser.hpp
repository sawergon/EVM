//
// Created by Alex on 28.04.2025.
//

#ifndef DIPLOMA_INCLUDE_CONFIGPARSER_CONFIGPARSER_HPP_
#define DIPLOMA_INCLUDE_CONFIGPARSER_CONFIGPARSER_HPP_

#include "../json.hpp"
#include <unordered_map>
#include <list>
#include <memory>

using t_Table = std::unordered_map<size_t, std::list<size_t>>;
using t_TablePtr = std::shared_ptr<t_Table>;

namespace parser {
  t_TablePtr parse(const nlohmann::json& json);

}

#endif  // DIPLOMA_INCLUDE_CONFIGPARSER_CONFIGPARSER_HPP_
