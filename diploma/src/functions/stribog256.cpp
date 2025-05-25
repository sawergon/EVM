#include "stribog256.hpp"

// Константы для алгоритма Стрибог

const uint8_t PI[256] = {
    252, 238, 221, 17,  207, 110, 49,  22,  251, 196, 250, 218, 35,  197, 4,
    77,  233, 119, 240, 219, 147, 46,  153, 186, 23,  54,  241, 187, 20,  205,
    95,  193, 249, 24,  101, 90,  226, 92,  239, 33,  129, 28,  60,  66,  139,
    1,   142, 79,  5,   132, 2,   174, 227, 106, 143, 160, 6,   11,  237, 152,
    127, 212, 211, 31,  235, 52,  44,  81,  234, 200, 72,  171, 242, 42,  104,
    162, 253, 58,  206, 204, 181, 112, 14,  86,  8,   12,  118, 18,  191, 114,
    19,  71,  156, 183, 93,  135, 21,  161, 150, 41,  16,  123, 154, 199, 243,
    145, 120, 111, 157, 158, 178, 177, 50,  117, 25,  61,  255, 53,  138, 126,
    109, 84,  198, 128, 195, 189, 13,  87,  223, 245, 36,  169, 62,  168, 67,
    201, 215, 121, 214, 246, 124, 34,  185, 3,   224, 15,  236, 222, 122, 148,
    176, 188, 220, 232, 40,  80,  78,  51,  10,  74,  167, 151, 96,  115, 30,
    0,   98,  68,  26,  184, 56,  130, 100, 159, 38,  65,  173, 69,  70,  146,
    39,  94,  85,  47,  140, 163, 165, 125, 105, 213, 149, 59,  7,   88,  179,
    64,  134, 172, 29,  247, 48,  55,  107, 228, 136, 217, 231, 137, 225, 27,
    131, 73,  76,  63,  248, 254, 141, 83,  170, 144, 202, 216, 133, 97,  32,
    113, 103, 164, 45,  43,  9,   91,  203, 155, 37,  208, 190, 229, 108, 82,
    89,  166, 116, 210, 230, 244, 180, 192, 209, 102, 175, 194, 57,  75,  99,
    182 };

const uint8_t TAU[64] = { 0,  8,  16, 24, 32, 40, 48, 56, 1,  9,  17, 25, 33,
                          41, 49, 57, 2,  10, 18, 26, 34, 42, 50, 58, 3,  11,
                          19, 27, 35, 43, 51, 59, 4,  12, 20, 28, 36, 44, 52,
                          60, 5,  13, 21, 29, 37, 45, 53, 61, 6,  14, 22, 30,
                          38, 46, 54, 62, 7,  15, 23, 31, 39, 47, 55, 63 };

const uint64_t A[64] = {
    0x8e20faa72ba0b470, 0x47107ddd9b505a38, 0xad08b0e0c3282d1c,
    0xd8045870ef14980e, 0x6c022c38f90a4c07, 0x3601161cf205268d,
    0x1b8e0b0e798c13c8, 0x83478b07b2468764, 0xa011d380818e8f40,
    0x5086e740ce47c920, 0x2843fd2067adea10, 0x14aff010bdd87508,
    0x0ad97808d06cb404, 0x05e23c0468365a02, 0x8c711e02341b2d01,
    0x46b60f011a83988e, 0x90dab52a387ae76f, 0x486dd4151c3dfdb9,
    0x24b86a840e90f0d2, 0x125c354207487869, 0x092e94218d243cba,
    0x8a174a9ec8121e5d, 0x4585254f64090fa0, 0xaccc9ca9328a8950,
    0x9d4df05d5f661451, 0xc0a878a0a1330aa6, 0x60543c50de970553,
    0x302a1e286fc58ca7, 0x18150f14b9ec46dd, 0x0c84890ad27623e0,
    0x0642ca05693b9f70, 0x0321658cba93c138, 0x86275df09ce8aaa8,
    0x439da0784e745554, 0xafc0503c273aa42a, 0xd960281e9d1d5215,
    0xe230140fc0802984, 0x71180a8960409a42, 0xb60c05ca30204d21,
    0x5b068c651810a89e, 0x456c34887a3805b9, 0xac361a443d1c8cd2,
    0x561b0d22900e4669, 0x2b838811480723ba, 0x9bcf4486248d9f5d,
    0xc3e9224312c8c1a0, 0xeffa11af0964ee50, 0xf97d86d98a327728,
    0xe4fa2054a80b329c, 0x727d102a548b194e, 0x39b008152acb8227,
    0x9258048415eb419d, 0x492c024284fbaec0, 0xaa16012142f35760,
    0x550b8e9e21f7a530, 0xa48b474f9ef5dc18, 0x70a6a56e2440598e,
    0x3853dc371220a247, 0x1ca76e95091051ad, 0x0edd37c48a08a6d8,
    0x07e095624504536c, 0x8d70c431ac02a736, 0xc83862965601dd1b,
    0x641c314b2b8ee083 };

const uint16_t C[12][128] = {
    { 0x3084, 0x85a2, 0xd172, 0x0224, 0xf7e5, 0xd3e2, 0x7890, 0x8366,
      0x8940, 0x4813, 0xfb6e, 0xf557, 0x588f, 0x313d, 0x6a73, 0x6584,
      0x6623, 0x9459, 0xff25, 0xb72a, 0x1a84, 0x4a63, 0x6c70, 0x6155 },
    { 0xe655, 0x25f3, 0xa2d0, 0x95b2, 0x735a, 0x9197, 0x665b, 0x85ce,
      0x1f4a, 0xb5b6, 0x647e, 0x378b, 0x82ff, 0xa39b, 0x5b52, 0xdab9,
      0x846a, 0x3488, 0xf988, 0x048e, 0x3781, 0xb9af, 0x251f, 0xe2a2 },
    { 0x6fa3, 0xb58a, 0xa99d, 0x2f1a, 0x4fe3, 0x9d46, 0x0f70, 0xb5d7, 0xf3fe,
      0xea72, 0xa232, 0xb986, 0x1d55, 0xe0f1, 0x6b50, 0x1931, 0x9ab5, 0x17d6,
      0x99e5, 0x7cb8, 0x561c, 0x2db0, 0xaa7c, 0xa55d, 0xda21, 0xbd7c },
    { 0xef1f, 0xdfb3, 0xe815, 0x66d2, 0xf948, 0xe1a0, 0x5d71, 0xe4dd, 0x488e,
      0x857e, 0x335c, 0x3c7d, 0x9d72, 0x1cad, 0x685e, 0x353f, 0xa376, 0x062d,
      0xb09c, 0x2b6f, 0x4438, 0x67ad, 0xb319, 0x91e9, 0x6f50, 0xaba0, 0xab2 },
    { 0x4bea, 0x6bac, 0xad47, 0x4799, 0xa3f4, 0x10c6, 0xca92, 0x637f,  0x151c,
      0x1f16, 0x8104, 0xa359, 0xe35d, 0x7800, 0xfffb, 0xdbf1, 0x3d27,  0x1271,
      0xa167, 0xa56a, 0x27ea, 0x9ea6, 0x3f56, 0x0175, 0x8fd7, 0xc6cfe, 0x57 },
    { 0xae4f, 0xaeae, 0x1d3a, 0xd3d9, 0x6fa4, 0xc33b, 0x7a30, 0x39c0, 0x2d66,
      0xc4f9, 0x5142, 0xa46c, 0x187f, 0x9ab4, 0x9ec6, 0xcffa, 0xa6b7, 0x1c9a,
      0xb7b8, 0x40af, 0x21f6, 0x6c2b, 0xec6b, 0x6bf7, 0x1c },
    { 0xf4c7, 0xe016, 0xeeaa, 0xc5ec, 0x51ac, 0x86fe, 0xbfb2,
      0x40c6, 0x7698, 0x3284, 0xa050, 0x4351, 0x7454, 0xca23,
      0xc4af, 0x3888, 0x6564, 0xd3a1, 0x4d49, 0x3a14, 0xd493 },
    { 0x9b1f, 0x5b42, 0x4d93, 0xc9a7, 0x03e7, 0xaa02, 0x0c6e, 0x4141,
      0xeb7f, 0x8719, 0xc36d, 0xe1e8, 0x9b44, 0x43bb, 0x4ddc, 0x49af,
      0x4892, 0xbcbb, 0x929b, 0x0690, 0x69d1, 0x8d2b, 0xd1a5, 0xc42f,
      0x36ac, 0xc235, 0x5951, 0xa8d9, 0xa47f, 0xdd4b, 0xf02e, 0x71e },
    { 0x378f, 0x5a54, 0x1631, 0x229b, 0x944c, 0x9ad8, 0xec16, 0x5fde, 0x3a7d,
      0x3a1b, 0x2589, 0x42cd, 0x955b, 0x7e00, 0xd098, 0x4800, 0xa440, 0xbdbb,
      0x2ceb, 0x17b2, 0xb8a9, 0xaa60, 0x79c5, 0x40e3, 0x8dc9, 0x2cb1, 0xf2a6,
      0x0741, 0x8451, 0x8332, 0x35ad, 0xb4c7, 0xfb98, 0x59ce, 0xd },
    { 0xabbe, 0xddea, 0x6800, 0x56f5, 0x2382, 0xae54, 0x8b2e, 0x4f3f,  0x3894,
      0x1e71, 0xcff8, 0xa78d, 0xb1ff, 0xfe18, 0xa1b3, 0x36f,  0x1039,  0xfe76,
      0x702a, 0xf693, 0x34b7, 0xa17c, 0x303b, 0x7652, 0xf436, 0x98fad, 0x1153,
      0xbb6c, 0x374b, 0x4c7f, 0xb984, 0x59ce, 0xd },
    { 0x7bcd,  0x9ed0,  0xefc8, 0x89fb, 0x3002,   0xc6cd,  0x635a, 0xfe94,
      0xd8fa,  0x6bbbe, 0xbab0, 0x76f,  0x1200,   0x1802,  0x1484, 0x6679,
      0x8a1d,  0x71e,   0xfea4, 0x8b9c, 0xae4b,   0xcaed,  0x1d7d, 0x476e,
      0x98dea, 0x2594,  0xac06, 0xfd85, 0xd6bcaa, 0x4cd81, 0xf32d, 0x1b },
};

// Вспомогательные функции
void XOR( uint8_t *a, const uint8_t *b, size_t len ) {
  for ( size_t i = 0; i < len; i++ ) {
    a[i] ^= b[i];
  }
}

void S( uint8_t *state ) {
  for ( size_t i = 0; i < 64; i++ ) {
    state[i] = PI[state[i]];
  }
}

void P( uint8_t *state ) {
  uint8_t temp[64];
  memcpy( temp, state, 64 );
  for ( size_t i = 0; i < 64; i++ ) {
    state[i] = temp[TAU[i]];
  }
}

void L( uint8_t *state ) {
  uint64_t *v = reinterpret_cast<uint64_t *>( state );
  for ( size_t i = 0; i < 8; i++ ) {
    uint64_t res = 0;
    for ( size_t j = 0; j < 64; j++ ) {
      if ( v[i] & ( 1ULL << ( 63 - j ) ) ) {
        res ^= A[j];
      }
    }
    v[i] = res;
  }
}

void E( uint8_t *K, const uint8_t *m ) {
  uint8_t state[64];
  XOR( K, m, 64 );
  memcpy( state, K, 64 );
  for ( size_t i = 0; i < 12; i++ ) {
    S( state );
    P( state );
    L( state );
    XOR( state, K, 64 );
  }
  memcpy( K, state, 64 );
}

void g_N( uint8_t *h, const uint8_t *N, const uint8_t *m ) {
  uint8_t K[64], t[64];
  XOR( K, h, 64 );
  XOR( K, N, 64 );
  S( K );
  P( K );
  L( K );
  E( K, m );
  XOR( t, K, 64 );
  XOR( t, h, 64 );
  XOR( t, m, 64 );
  memcpy( h, t, 64 );
}

// Основная функция хеширования
void stribog256( const uint8_t *message, size_t len, uint8_t *hash ) {
  uint8_t h[64]      = { 0 };
  uint8_t N[64]      = { 0 };
  uint8_t Sigma[64]  = { 0 };
  size_t  block_size = 64;
  size_t  padded_len = ( ( len + block_size ) / block_size ) * block_size;
  std::vector<uint8_t> padded( padded_len, 0 );
  memcpy( padded.data(), message, len );
  padded[len] = 0x01;

  // Добавляем длину сообщения в битах (little-endian)
  uint64_t bit_len = len * 8;
  for ( size_t i = 0; i < 8; i++ ) {
    padded[padded_len - 8 + i] = ( bit_len >> ( i * 8 ) ) & 0xFF;
  }

  // Обработка блоков
  for ( size_t i = 0; i < padded_len; i += block_size ) {
    const uint8_t *block = padded.data() + i;
    g_N( h, N, block );

    // Обновляем N и Sigma
    uint64_t carry = 0;
    for ( size_t j = 0; j < 64; j++ ) {
      carry += N[j] + block[j];
      N[j] = carry & 0xFF;
      carry >>= 8;
    }
    carry = 0;
    for ( size_t j = 0; j < 64; j++ ) {
      carry += Sigma[j] + block[j];
      Sigma[j] = carry & 0xFF;
      carry >>= 8;
    }
  }

  // Финальный шаг
  memset( N, 0, 64 );
  g_N( h, N, Sigma );
  memcpy( hash, h, 32 );  // Для Stribog-256 берем первые 32 байта
}

std::string stribog256( const std::string &message ) {
  const auto *m = reinterpret_cast<const uint8_t *>( message.data() );
  uint8_t     result[32];
  stribog256( m, message.size(), result );
  std::string msg;
  for ( unsigned char i : result ) {
    char buf[3];
    sprintf( buf, "%02x", i );
    msg += buf;
  }
  return msg;
}