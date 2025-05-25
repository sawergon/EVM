//
// Created by Alex on 25.05.2025.
//

#ifndef STRIBOG512_HPP
#define STRIBOG512_HPP


#include <array>
#include <cstdint>
#include <string>
#include <vector>

class Streebog512 {
  public:
  Streebog512();
  void                    reset();
  void                    update( const std::vector<uint8_t> &data );
  std::array<uint8_t, 64> finalize();

  std::string hash( const std::string &data );

  private:
  using Block = std::array<uint8_t, 64>;

  // Состояние
  Block                h;
  Block                N;
  Block                Sigma;
  std::vector<uint8_t> buffer;
  uint64_t             processed_bytes;

  // Константы
  static const std::array<uint8_t, 256>               PI;
  static const std::array<uint8_t, 64>                TAU;
  static const std::array<std::array<uint8_t, 8>, 64> A_MATRIX;
  static const std::array<Block, 13>                  C;

  // Вспомогательные методы
  Block                  convert_size_t_to_Block( size_t value );
  void                   g_N( Block &h, const Block &m, const Block &N );
  void                   compress( const Block &m );
  void                   l_transform( std::array<uint8_t, 8> &b );
  static void            S( Block &data );
  static void            P( Block &data );
  void                   L( Block &data );
  Block                  LPS( const Block &data );
  Block                  E( const Block &K, const Block &m );
  void                   XOR( Block &a, const Block &b ) const;
  void XOR( std::array<uint8_t, 8> &a, const std::array<uint8_t, 8> &b ) const;
  void add_mod512( Block &a, const Block &b ) const;
  void padding();
  void processBlock( const Block &block );
};

#endif  // STRIBOG512_HPP
