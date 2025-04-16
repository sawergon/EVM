//
// Created by Alex on 16.04.2025.
//

#ifndef DIPLOMA_INCLUDE_NETWORK_CONVERTORS_HPP_
#define DIPLOMA_INCLUDE_NETWORK_CONVERTORS_HPP_

#include <string>
#include <vector>
#include <cstdint>

namespace convert {
  inline std::vector<uint8_t> uint16_t_to_vec(uint16_t v) {
    std::vector<uint8_t> res;
    res.push_back(static_cast<uint8_t>(v >> 8));
    res.push_back(static_cast<uint8_t>(v));
    return res;
  }

  inline std::vector<uint8_t> uint32_t_to_vec(uint32_t v) {
    std::vector<uint8_t> res;
    res.push_back(static_cast<uint8_t>(v >> 24));
    res.push_back(static_cast<uint8_t>(v >> 16));
    res.push_back(static_cast<uint8_t>(v >> 8));
    res.push_back(static_cast<uint8_t>(v));
    return res;
  }

  inline std::vector<uint8_t> uint64_t_to_vec(uint64_t v) {
    std::vector<uint8_t> res;
    res.push_back(static_cast<uint8_t>(v >> 56));
    res.push_back(static_cast<uint8_t>(v >> 48));
    res.push_back(static_cast<uint8_t>(v >> 40));
    res.push_back(static_cast<uint8_t>(v >> 32));
    res.push_back(static_cast<uint8_t>(v >> 24));
    res.push_back(static_cast<uint8_t>(v >> 16));
    res.push_back(static_cast<uint8_t>(v >> 8));
    res.push_back(static_cast<uint8_t>(v));
    return res;
  }
}

#endif  // DIPLOMA_INCLUDE_NETWORK_CONVERTORS_HPP_
