//
// Created by Alex on 29.04.2025.
//

#ifndef DIPLOMA_INCLUDE_KUZNECHIK_KUZNECHIK_HPP_
#define DIPLOMA_INCLUDE_KUZNECHIK_KUZNECHIK_HPP_


#include <algorithm>
#include <cstdint>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

namespace kuznechik {

  using t_Key   = std::vector<uint8_t>;
  using t_KeyId = size_t;

  class KuznechikCipher {
private:
    // S-блок (Pi) ГОСТ Р 34.12-2015
    static constexpr uint8_t PI[256] = {
        252, 238, 221, 17,  207, 110, 49,  22,  251, 196, 250, 218, 35,  197,
        4,   77,  233, 119, 240, 219, 147, 46,  153, 186, 23,  54,  241, 187,
        20,  205, 95,  193, 249, 24,  101, 90,  226, 92,  239, 33,  129, 28,
        60,  66,  139, 1,   142, 79,  5,   132, 2,   174, 227, 106, 143, 160,
        6,   11,  237, 152, 127, 212, 211, 31,  235, 52,  44,  81,  234, 200,
        72,  171, 242, 42,  104, 162, 253, 58,  206, 204, 181, 112, 14,  86,
        8,   12,  118, 18,  191, 114, 19,  71,  156, 183, 93,  135, 21,  161,
        150, 41,  16,  123, 154, 199, 243, 145, 120, 111, 157, 158, 178, 177,
        50,  117, 25,  61,  255, 53,  138, 126, 109, 84,  198, 128, 195, 189,
        13,  87,  223, 245, 36,  169, 62,  168, 67,  201, 215, 121, 214, 246,
        124, 34,  185, 3,   224, 15,  236, 222, 122, 148, 176, 188, 220, 232,
        40,  80,  78,  51,  10,  74,  167, 151, 96,  115, 30,  0,   98,  68,
        26,  184, 56,  130, 100, 159, 38,  65,  173, 69,  70,  146, 39,  94,
        85,  47,  140, 163, 165, 125, 105, 213, 149, 59,  7,   88,  179, 64,
        134, 172, 29,  247, 48,  55,  107, 228, 136, 217, 231, 137, 225, 27,
        131, 73,  76,  63,  248, 254, 141, 83,  170, 144, 202, 216, 133, 97,
        32,  113, 103, 164, 45,  43,  9,   91,  203, 155, 37,  208, 190, 229,
        108, 82,  89,  166, 116, 210, 230, 244, 180, 192, 209, 102, 175, 194,
        57,  75,  99,  182 };

    // Корректный обратный S-блок (Pi^{-1})
    static constexpr uint8_t PI_INV[256] = {
        165, 45,  50,  143, 14,  48,  56,  192, 84,  230, 158, 57,  85,  126,
        82,  145, 100, 3,   87,  90,  28,  96,  7,   24,  33,  114, 168, 209,
        41,  198, 164, 63,  224, 39,  141, 12,  130, 234, 174, 180, 154, 99,
        73,  229, 66,  228, 21,  183, 200, 6,   112, 157, 65,  117, 25,  201,
        170, 252, 77,  191, 42,  115, 132, 213, 195, 175, 43,  134, 167, 177,
        178, 91,  70,  211, 159, 253, 212, 15,  156, 47,  155, 67,  239, 217,
        121, 182, 83,  127, 193, 240, 35,  231, 37,  94,  181, 30,  162, 223,
        166, 254, 172, 34,  249, 226, 74,  188, 53,  202, 238, 120, 5,   107,
        81,  225, 89,  163, 242, 113, 86,  17,  106, 137, 148, 101, 140, 187,
        119, 60,  123, 40,  171, 210, 49,  222, 196, 95,  204, 207, 118, 44,
        184, 216, 46,  54,  219, 105, 179, 20,  149, 190, 98,  161, 59,  22,
        102, 233, 92,  108, 109, 173, 55,  97,  75,  185, 227, 186, 241, 160,
        133, 131, 218, 71,  197, 176, 51,  250, 150, 111, 110, 194, 246, 80,
        255, 93,  169, 142, 23,  27,  151, 125, 236, 88,  247, 31,  251, 124,
        9,   13,  122, 103, 69,  135, 220, 232, 79,  29,  78,  4,   235, 248,
        243, 62,  61,  189, 138, 136, 221, 205, 11,  19,  152, 2,   147, 128,
        144, 208, 36,  52,  203, 237, 244, 206, 153, 16,  68,  64,  146, 58,
        1,   38,  18,  26,  72,  104, 245, 129, 139, 199, 214, 32,  10,  8,
        0,   76,  215, 116 };

    // Константы для линейного преобразования
    static constexpr uint8_t L_VEC[16] = { 0x94, 0x20, 0x85, 0x10, 0xC2, 0xC0,
                                           0x01, 0xFB, 0x01, 0xC0, 0xC2, 0x10,
                                           0x85, 0x20, 0x94, 0x01 };
public:
    std::vector<std::vector<uint8_t>> round_keys;

    // Умножение в поле Галуа GF(2^8)
    static uint8_t gf_mul( uint8_t a, uint8_t b ) {
      uint8_t res = 0;
      for ( int i = 0; i < 8; i++ ) {
        if ( b & 1 )
          res ^= a;
        bool hi_bit = ( a & 0x80 );
        a <<= 1;
        if ( hi_bit )
          a ^= 0xC3;  // Полином x^8 + x^7 + x^6 + x + 1
        b >>= 1;
      }
      return res;
    }

    static uint8_t l_transform( const uint8_t *a ) {
      uint8_t res = 0;
      for ( int i = 0; i < 16; ++i ) {
        res ^= gf_mul( a[i], L_VEC[i] );
      }
      return res;
    }

    static uint8_t *R_transform( uint8_t *a ) {
      uint8_t a15 = l_transform( a );
      for ( int i = 15; i > 0; --i ) {
        a[i] = a[i - 1];
      }
      a[0] = a15;
      return a;
    }

    static uint8_t* R_inv_transform( uint8_t *a ) {
      uint8_t a0 = a[0];
      for (int i = 0; i < 15; ++i) {
        a[i] = a[i + 1];
      }
      a[15] = a0;
      a[15] = l_transform(a);
      return a;
    }

    // Линейное преобразование L
    static uint8_t *L_transform( uint8_t *state ) {
      for ( int i = 0; i < 16; ++i ) {
        R_transform( state );
      }
      return state;
    }

    // Обратное линейное преобразование L⁻¹
    static uint8_t* L_inv_transform( uint8_t *state ) {
      for ( int i = 0; i < 16; ++i ) {
        R_inv_transform( state );
      }
      return state;
    }

    // Нелинейное преобразование S
    static uint8_t *S_transform( uint8_t *state ) {
      for ( int i = 0; i < 16; i++ ) {
        state[i] = PI[state[i]];
      }
      return state;
    }

    // Обратное нелинейное преобразование S⁻¹
    static void S_inv_transform( uint8_t *state ) {
      for ( int i = 0; i < 16; i++ ) {
        state[i] = PI_INV[state[i]];
      }
    }

    static uint8_t *X_transform( const uint8_t *k, uint8_t *a ) {
      for ( int i = 0; i < 16; ++i ) {
        a[i] ^= k[i];
      }
      return a;
    }

    static void F_transform( const uint8_t *k, uint8_t *a1, uint8_t *a0 ) {
      uint8_t a1_[16];
      memcpy( a1_, a1, 16 );

      L_transform( S_transform( X_transform( k, a1 ) ) );

      for ( int i = 0; i < 16; ++i ) {
        a1[i] ^= a0[i];
      }

      memcpy( a0, a1_, 16 );
    }

    static void lsx_transform( const uint8_t *k, uint8_t *a ) {
      L_transform( S_transform( X_transform( k, a ) ) );
    }

    // Генерация раундовых ключей
    void key_expansion( const uint8_t *master_key ) {
      uint8_t k1[16], k2[16];
      memcpy( k1, master_key, 16 );
      memcpy( k2, master_key + 16, 16 );

      round_keys.clear();
      round_keys.emplace_back( k1, k1 + 16 );
      round_keys.emplace_back( k2, k2 + 16 );
      uint8_t c[32][16] = { 0 };
      for ( int i = 1; i <= 32; ++i ) {
        c[i - 1][15] = i;
        L_transform( c[i - 1] );
      }

      for ( int i = 1; i <= 4; ++i ) {
        uint8_t k2i1[16] = { 0 }, k2i2[16] = { 0 };
        memcpy( k2i1, round_keys[2 * i - 2].data(), 16 );
        memcpy( k2i2, round_keys[2 * i - 1].data(), 16 );
        for ( int j = 0; j < 8; ++j ) {
          F_transform( c[( 8 * ( i - 1 ) + j )], k2i1, k2i2 );
        }
        round_keys.emplace_back( k2i1, k2i1 + 16 );
        round_keys.emplace_back( k2i2, k2i2 + 16 );
      }
    }

    // Шифрование блока
    void encrypt_block( uint8_t *block ) {
      for ( int r = 0; r < 9; ++r ) {
        lsx_transform( round_keys[r].data(), block );
      }

      X_transform( round_keys[9].data(), block );
    }

    // Дешифрование блока
    void decrypt_block( uint8_t *block ) {
      for (int r = 9; r > 0; --r) {
        S_inv_transform(L_inv_transform(X_transform(round_keys[r].data(), block)));
      }
      X_transform(round_keys[0].data(), block);
    }

    // Удаление паддинга
    static std::string unpad_message( const std::vector<uint8_t> &padded ) {
      if ( padded.empty() )
        return "";
      uint8_t pad_len = padded.back();
      if ( pad_len == 0 || pad_len > 16 )
        throw std::runtime_error( "Invalid padding" );
      for ( size_t i = padded.size() - pad_len; i < padded.size(); ++i ) {
        if ( padded[i] != pad_len )
          throw std::runtime_error( "Invalid padding" );
      }
      return std::string( padded.begin(), padded.end() - pad_len );
    }

    // Добавление паддинга
    static std::vector<uint8_t> pad_message( const std::string &message ) {
      size_t               pad_len = 16 - ( message.size() % 16 );
      std::vector<uint8_t> padded( message.begin(), message.end() );
      padded.insert( padded.end(), pad_len, static_cast<uint8_t>( pad_len ) );
      return padded;
    }

    KuznechikCipher( const std::vector<uint8_t> &key ) {
      if ( key.size() != 32 )
        throw std::invalid_argument( "Key must be 32 bytes" );
      key_expansion( key.data() );
    }

    std::vector<uint8_t> encrypt( const std::string &message ) {
      std::vector<uint8_t> padded = pad_message( message );
      std::vector<uint8_t> ciphertext;

      for ( size_t i = 0; i < padded.size(); i += 16 ) {
        uint8_t block[16];
        memcpy( block, &padded[i], 16 );
        encrypt_block( block );
        ciphertext.insert( ciphertext.end(), block, block + 16 );
      }

      return ciphertext;
    }

    std::string decrypt( const std::vector<uint8_t> &ciphertext ) {
      if ( ciphertext.size() % 16 != 0 )
        throw std::invalid_argument(
            "Ciphertext length must be multiple of 16 bytes" );

      std::vector<uint8_t> padded;
      for ( size_t i = 0; i < ciphertext.size(); i += 16 ) {
        uint8_t block[16];
        memcpy( block, &ciphertext[i], 16 );
        decrypt_block( block );
        padded.insert( padded.end(), block, block + 16 );
      }

      return unpad_message( padded );
    }
  };

  t_Key generate_random_key();
}  // namespace kuznechik

#endif  // DIPLOMA_INCLUDE_KUZNECHIK_KUZNECHIK_HPP_
