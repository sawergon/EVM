//
// Created by Alex on 25.05.2025.
//

#ifndef BLOMEPOLINOME_HPP
#define BLOMEPOLINOME_HPP

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/mat_ZZ_p.h>

namespace blome {
class BlomPolynomial {
  private:
    long m; // Степень полинома
    NTL::ZZ p; // Модуль
    NTL::mat_ZZ_p coeffs; // Матрица коэффициентов (m+1)x(m+1)

  public:
    // Конструктор с генерацией случайного полинома
    BlomPolynomial(long degree, const NTL::ZZ &modulus);

    // Вычисление значения полинома в точке (x, y)
    NTL::ZZ_p evaluate(const NTL::ZZ_p &x, const NTL::ZZ_p &y);

    // Получение предварительного ключа для узла с ID = x
    NTL::ZZ_p get_node_key(const NTL::ZZ_p &x);

    void print() const;
};
}

#endif //BLOMEPOLINOME_HPP
