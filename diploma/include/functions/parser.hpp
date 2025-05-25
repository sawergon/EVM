//
// Created by Alex on 24.05.2025.
//

#ifndef PARSER_HPP
#define PARSER_HPP
#include <cstdint>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

enum class KeyType { Uni, PP };

struct recvEnc {
  long        from;
  long        to;
  std::string msg;
  bool        success = false;
};

static KeyType keyTypeFromChar( const std::string &c ) {
  if ( c == "U" )
    return KeyType::Uni;
  if ( c == "PP" )
    return KeyType::PP;

  throw std::invalid_argument( "Unknown key type" );
}

static std::string charFromKeyType( KeyType type ) {
  switch ( type ) {
  case KeyType::Uni:
    return "U";
  case KeyType::PP:
    return "PP";
  default:
    throw std::invalid_argument( "Unknown key type" );
  }
}

inline std::string convertToString( const std::vector<uint8_t> &bytes ) {
  return std::string(
      reinterpret_cast<const char *>( bytes.data() ),
      reinterpret_cast<const char *>( bytes.data() ) + bytes.size() );
}

inline std::vector<uint8_t> convertFromString( const std::string &bytes ) {
  return std::vector(
      reinterpret_cast<const uint8_t *>( bytes.data() ),
      reinterpret_cast<const uint8_t *>( bytes.data() ) + bytes.size() );
}

recvEnc parseMsgEnc( const std::string &msg );

#endif  // PARSER_HPP
