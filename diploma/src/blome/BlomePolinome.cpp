//
// Created by Alex on 25.05.2025.
//
#include "BlomePolinome.hpp"
#include <NTL/ZZ.h>
#include <vector>
#include <cstdint>

namespace blome {
BlomPolynomial::BlomPolynomial(long degree, const NTL::ZZ &modulus) : m(degree), p(modulus) {
  NTL::ZZ_p::init(p); // Инициализация поля

  coeffs.SetDims(m + 1, m + 1);
  for (long i = 0; i <= m; ++i) {
    for (long j = i; j <= m; ++j) {
      // Генерируем только верхний треугольник
      NTL::ZZ_p r = NTL::random_ZZ_p(); // Случайный элемент поля
      coeffs[i][j] = r;
      if (i != j) {
        coeffs[j][i] = r; // Зеркалирование для симметрии
      }
    }
  }
}

NTL::ZZ_p BlomPolynomial::evaluate(const NTL::ZZ_p &x, const NTL::ZZ_p &y) {
  NTL::ZZ_p result = NTL::ZZ_p::zero();
  NTL::ZZ_p xi = NTL::ZZ_p(1); // x^0

  for (long i = 0; i <= m; ++i) {
    NTL::ZZ_p yj = NTL::ZZ_p(1); // y^0
    for (long j = 0; j <= m; ++j) {
      result += coeffs[i][j] * xi * yj;
      yj *= y;
    }
    xi *= x;
  }
  return result;
}

// Получение предварительного ключа для узла с ID = x
NTL::ZZ_p BlomPolynomial::get_node_key(const NTL::ZZ_p &x) {
  return evaluate(x, NTL::ZZ_p(1));
}

// Генерация 32-байтового ключа для узла с ID = x
std::vector<uint8_t> BlomPolynomial::generate_32byte_key( const NTL::ZZ_p &x,
                                                          const NTL::ZZ_p &y ) {
  // Получаем значение полинома в точке x
  NTL::ZZ_p key_value = evaluate( x, y );

  // Конвертируем в ZZ для работы с битовым представлением
  NTL::ZZ key_zz = rep( key_value );

  // Преобразуем в массив байтов
  std::vector<uint8_t> key_bytes( 32, 0 );

  // Копируем биты в массив байтов
  NTL::BytesFromZZ( key_bytes.data(), key_zz, 32 );

  return key_bytes;
}
std::vector<uint8_t> BlomPolynomial::generate_32byte_key( const size_t &x,
                                                          const size_t &y ) {
  // Получаем значение полинома в точке x
 return generate_32byte_key( NTL::ZZ_p( x ), NTL::ZZ_p( y ) );
}

// Печать полинома (для отладки)
void BlomPolynomial::print() const {
  for (long i = 0; i <= m; ++i) {
    for (long j = 0; j <= m; ++j) {
      std::cout << coeffs[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

} // namespace blome
