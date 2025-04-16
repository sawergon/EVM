//
// Created by Alex on 16.04.2025.
//

#ifndef DIPLOMA_INCLUDE_NETWORK_CONVERTORS_HPP_
#define DIPLOMA_INCLUDE_NETWORK_CONVERTORS_HPP_

#include <string>
#include <vector>
#include <cstdint>
#include <cereal/archives/binary.hpp>

namespace convert {
  template<typename T>
  std::vector<uint8_t> to_bytes(const T& value) {
    std::vector<uint8_t> buffer;
    // Используем специализацию для разных типов
    if constexpr (std::is_trivially_copyable_v<T>) {
      // Оптимизированный путь для тривиальных типов
      buffer.resize(sizeof(T));
      memcpy(buffer.data(), &value, sizeof(T));
    } else {
      // Общий путь через сериализацию
      std::ostringstream oss;
      {
        cereal::BinaryOutputArchive archive(oss);
        archive(value);
      }
      const auto& str = oss.str();
      buffer.assign(str.begin(), str.end());
    }
    return buffer;
  }

  template<typename T>
  T from_bytes(const std::vector<uint8_t>& buffer) {
    if constexpr (std::is_trivially_copyable_v<T>) {
      // Для тривиально копируемых типов
      if (buffer.size() != sizeof(T)) {
        throw std::runtime_error("Buffer size mismatch for trivial type");
      }
      T value;
      memcpy(&value, buffer.data(), sizeof(T));
      return value;
    } else {
      // Для сложных типов через cereal
      std::string str(buffer.begin(), buffer.end());
      std::istringstream iss(str);
      T value;
      {
        cereal::BinaryInputArchive archive(iss);
        archive(value);
      }
      return value;
    }
  }
}

#endif  // DIPLOMA_INCLUDE_NETWORK_CONVERTORS_HPP_
