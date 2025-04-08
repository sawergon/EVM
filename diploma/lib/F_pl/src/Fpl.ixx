module;
#include <sstream>
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pE.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_pXFactoring.h>
export module Fpl;

export class Fpl {
  public:
  explicit Fpl(long p_val = 2, long l_val = 1)
      : p(p_val), l(l_val) {
    if (p <= 1 || l <= 0)
      throw std::invalid_argument("Invalid field parameters");

    NTL::ZZ_p::init(NTL::ZZ(p));

    // Фиксированный базовый полином
    base_poly = get_fixed_base_poly(p, l);
    NTL::ZZ_pE::init(base_poly);
    base_ctx.save();

    n = NTL::power_long(p, l);
  }

  [[nodiscard]] NTL::ZZ_pE from_long(long num) const {
    base_ctx.restore();
        
    NTL::ZZ_pX poly_rep;
    NTL::ZZ nn(num);
        
    for (long j = 0; j < l && nn != 0; ++j) {
      NTL::ZZ digit;
      NTL::DivRem(nn, digit, nn, NTL::ZZ(p));
      SetCoeff(poly_rep, j, NTL::conv<NTL::ZZ_p>(digit));
    }
        
    NTL::ZZ_pE val;
    conv(val, poly_rep);
    return val;
  }

  [[nodiscard]] long to_long(const NTL::ZZ_pE& val) const {
    base_ctx.restore();
    NTL::ZZ_pX poly = rep(val);
    NTL::ZZ result(0);
        
    for (long j = deg(poly); j >= 0; --j) {
      result *= NTL::ZZ(p);
      result += rep(coeff(poly, j));
    }
        
    return conv<long>(result);
  }

  [[nodiscard]] std::string to_string(const NTL::ZZ_pE& val) const {
    std::ostringstream out;
    base_ctx.restore();
    NTL::ZZ_pX poly_rep = rep(val);
        
    out << "[";
    for (long j = 0; j <= deg(poly_rep); ++j) {
      out << rep(coeff(poly_rep, j));
      if (j < deg(poly_rep))
        out << " ";
    }
    out << "]";
    return out.str();
  }

  // Арифметические операции
  [[nodiscard]] NTL::ZZ_pE add(const NTL::ZZ_pE& a, const NTL::ZZ_pE& b) const {
    base_ctx.restore();
    return a + b;
  }

  [[nodiscard]] NTL::ZZ_pE sub(const NTL::ZZ_pE& a, const NTL::ZZ_pE& b) const {
    base_ctx.restore();
    return a - b;
  }

  [[nodiscard]] NTL::ZZ_pE mul(const NTL::ZZ_pE& a, const NTL::ZZ_pE& b) const {
    base_ctx.restore();
    return a * b;
  }

  [[nodiscard]] NTL::ZZ_pE div(const NTL::ZZ_pE& a, const NTL::ZZ_pE& b) const {
    base_ctx.restore();
    return a / b;
  }

  [[nodiscard]] NTL::ZZ_pE neg(const NTL::ZZ_pE& a) const {
    base_ctx.restore();
    return -a;
  }

  [[nodiscard]] NTL::ZZ_pE inv(const NTL::ZZ_pE& a) const {
    base_ctx.restore();
    return 1/a;
  }

  [[nodiscard]] NTL::ZZ_pE power(const NTL::ZZ_pE& a, long k) const {
    base_ctx.restore();
    return NTL::power(a, k);
  }

  [[nodiscard]] NTL::ZZ_pE int2Fpl(long num) {
    if (num == 0)
      return NTL::ZZ_pE(0);
    if (NTL::IsZero(gen)) {
      gen = from_long(2);
    }
    return power(gen, num - 1);
  }

  void setGen(const NTL::ZZ_pE& generator) { gen = generator; }

  [[nodiscard]] NTL::ZZ_pE getGen() const { return gen; }

  [[nodiscard]] long fpl2int(const NTL::ZZ_pE& el) {
    if (NTL::IsZero(el))
      return 0;
    if (el == NTL::ZZ_pE(1)) return 1;
    NTL::ZZ_pE current(1);
//    std::cout << to_string(current) << std::endl;
//    std::cout << to_string(gen) << std::endl;
    for (long i = 2; i < n; ++i) {
      current *= gen;
      if (current == el)
        return i;
    }
    throw std::invalid_argument("Element not found");
  }

  long size() const { return n; }

  static void setPythonFlag(bool flag) { is_like_python = flag; }

  private:
  static NTL::ZZ_pX get_fixed_base_poly(long p, long l) {
    NTL::ZZ_pX poly;
    if (is_like_python) {
      if (p == 2) {
        if (l == 1) {
          SetCoeff(poly, 1, 1);
          SetCoeff(poly, 0, 1);
        }
        else if (l == 2) {
          SetCoeff(poly, 2, 1);
          SetCoeff(poly, 1, 1);
          SetCoeff(poly, 0, 1);
        }
        else if (l == 3) {
          SetCoeff(poly, 4, 1);
          SetCoeff(poly, 3, 1);
          SetCoeff(poly, 1, 0);
          SetCoeff(poly, 0, 1);
        }
      }
      else if (p == 3) {
        if (l == 1) {
          SetCoeff(poly, 1, 1);
          SetCoeff(poly, 0, 1);
        }
        else if (l == 2) {
          SetCoeff(poly, 2, 1);
          SetCoeff(poly, 1, 1);
          SetCoeff(poly, 0, 2);
        }
        else if (l == 3) {
          SetCoeff(poly, 4, 1);
          SetCoeff(poly, 3, 2);
          SetCoeff(poly, 1, 0);
          SetCoeff(poly, 0, 1);
        }
      }
      else {
        throw std::invalid_argument("Unknown (p, l) pair");
      }
    }
    else {
      NTL::BuildIrred(poly, l);
    }
    return poly;
  }

  static bool is_like_python;
  long p = 2, l = 1, n = 0;
  NTL::ZZ_pX base_poly;
  NTL::ZZ_pEContext base_ctx;
  NTL::ZZ_pE gen = NTL::ZZ_pE(0);
};

bool Fpl::is_like_python = true;