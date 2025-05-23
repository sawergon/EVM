#include "Kuznechik.hpp"

namespace kuznechik {
  t_Key generate_random_key() {
    std::random_device rd;  // Источник энтропии
    std::mt19937 gen(rd()); // Генератор псевдослучайных чисел
    std::uniform_int_distribution<> dis(0, 255);

    t_Key key(32);
    for (auto &byte : key) {
      byte = static_cast<uint8_t>(dis(gen));
    }

    return key;
  }
}