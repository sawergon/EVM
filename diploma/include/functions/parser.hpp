//
// Created by Alex on 24.05.2025.
//

#ifndef PARSER_HPP
#define PARSER_HPP
#include <sstream>
#include <stdexcept>
#include <string>

enum class KeyType {
  Uni,
  PP
};

struct recvEnc {
  long from;
  long to;
  std::string msg;
  bool success = false;
};

static KeyType keyTypeFromChar(const std::string &c) {
  if (c == "U")
    return KeyType::Uni;
  if (c == "PP")
    return KeyType::PP;

  throw std::invalid_argument("Unknown key type");
}

static std::string charFromKeyType(KeyType type) {
  switch (type) {
    case KeyType::Uni:
      return "U";
    case KeyType::PP:
      return "PP";
    default:
      throw std::invalid_argument("Unknown key type");
  }
}

recvEnc parseMsgEnc(const std::string &msg);

#endif //PARSER_HPP
