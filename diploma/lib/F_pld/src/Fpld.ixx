module;
#include <sstream>
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pE.h>
#include <NTL/ZZ_pEX.h>
#include <NTL/ZZ_pEXFactoring.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_pXFactoring.h>
export module Fpld;

export class Fpld {
  public:
  explicit Fpld( long p_val = 2, long l_val = 1, long d_val = 1 )
      : p( p_val )
      , l( l_val )
      , d( d_val ) {
    if ( p <= 1 || l <= 0 || d <= 0 )
      throw std::invalid_argument( "Invalid field parameters" );

    NTL::ZZ_p::init( NTL::ZZ( p ) );

    // Фиксированный base полином
    base_poly = get_fixed_base_poly( p, l );
    NTL::ZZ_pE::init( base_poly );
    base_ctx.save();

    // Фиксированный ext полином
    ext_poly = get_fixed_ext_poly( p, d );

    mod_ext = NTL::ZZ_pEXModulus( ext_poly );

    n = NTL::power_long( p, NTL::power_long( l, d ) );
  }

  [[nodiscard]] NTL::ZZ_pEX from_long( long num ) const {
    NTL::ZZ_p::init( NTL::ZZ( p ) );
    NTL::ZZ_pE::init( base_poly );
    base_ctx.restore();

    NTL::ZZ_pEX val = NTL::ZZ_pEX();
    NTL::ZZ     q   = NTL::power( NTL::ZZ( p ), l );
    NTL::ZZ     nn( num );

    for ( long i = 0; i < d && nn != 0; ++i ) {
      NTL::ZZ rem;
      NTL::DivRem( nn, rem, nn, q );

      NTL::ZZ_pX poly_rep;
      for ( long j = 0; j < l; ++j ) {
        NTL::ZZ digit;
        NTL::DivRem( rem, digit, rem, NTL::ZZ( p ) );
        SetCoeff( poly_rep, j, NTL::conv<NTL::ZZ_p>( digit ) );
      }

      NTL::ZZ_pE coeff;
      conv( coeff, poly_rep );
      SetCoeff( val, i, coeff );
    }

    NTL::rem( val, val, ext_poly );
    return val;
  }

  [[nodiscard]] long to_long( const NTL::ZZ_pEX &val ) const {
    base_ctx.restore();
    NTL::ZZ result( 0 );
    NTL::ZZ q = NTL::power( NTL::ZZ( p ), l );

    for ( long i = deg( val ); i >= 0; --i ) {
      result *= q;
      NTL::ZZ_pX poly = rep( coeff( val, i ) );
      NTL::ZZ    coeff_sum( 0 );
      for ( long j = deg( poly ); j >= 0; --j ) {
        coeff_sum *= NTL::ZZ( p );
        coeff_sum += rep( coeff( poly, j ) );
      }
      result += coeff_sum;
    }

    return conv<long>( result );
  }

  [[nodiscard]] std::string to_string( const NTL::ZZ_pEX &val ) const {
    std::ostringstream out;
    base_ctx.restore();
    out << "[";
    for ( long i = 0; i <= deg( val ); ++i ) {
      out << "[";
      NTL::ZZ_pX poly_rep = rep( coeff( val, i ) );
      for ( long j = 0; j < l; ++j ) {
        out << rep( coeff( poly_rep, j ) );
        if ( j < l - 1 )
          out << " ";
      }
      out << "]";
      if ( i < deg( val ) )
        out << " ";
    }
    out << "]";
    return out.str();
  }

  // Арифметика
  [[nodiscard]] NTL::ZZ_pEX add( const NTL::ZZ_pEX &a,
                                 const NTL::ZZ_pEX &b ) const {
    base_ctx.restore();
    auto res = a + b;
    NTL::rem( res, res, mod_ext );
    return res;
  }

  [[nodiscard]] NTL::ZZ_pEX sub( const NTL::ZZ_pEX &a,
                                 const NTL::ZZ_pEX &b ) const {
    base_ctx.restore();
    auto res = a - b;
    NTL::rem( res, res, mod_ext );
    return res;
  }

  // Вспомогательные методы
  void check_compatibility( const Fpld &other ) const {
    if ( p != other.p || l != other.l || d != other.d )
      throw std::invalid_argument( "Field mismatch" );
  }

  [[nodiscard]] NTL::ZZ_pEX mul( const NTL::ZZ_pEX &a,
                                 const NTL::ZZ_pEX &b ) const {
    base_ctx.restore();
    NTL::ZZ_pEX res;
    NTL::MulMod( res, a, b, mod_ext );
    return res;
  }

  [[nodiscard]] NTL::ZZ_pEX div( const NTL::ZZ_pEX &a,
                                 const NTL::ZZ_pEX &b ) const {
    base_ctx.restore();
    NTL::ZZ_pEX res;
    NTL::MulMod( res, a, inv( b ), mod_ext );
    return res;
  }

  [[nodiscard]] NTL::ZZ_pEX neg( const NTL::ZZ_pEX &a ) const {
    base_ctx.restore();
    return -a;
  }

  [[nodiscard]] NTL::ZZ_pEX inv( const NTL::ZZ_pEX &a ) const {
    base_ctx.restore();
    NTL::ZZ_pEX res;
    NTL::InvMod( res, a, mod_ext );
    return res;
  }

  [[nodiscard]] NTL::ZZ_pEX power( const NTL::ZZ_pEX &a, long k ) const {
    base_ctx.restore();
    NTL::ZZ_pEX res;
    NTL::PowerMod( res, a, k, mod_ext );
    return res;
  }

  [[nodiscard]] NTL::ZZ_pEX int2Fpld( long num ) {
    if ( num == 0 )
      return NTL::ZZ_pEX( 0 );
    if ( NTL::IsZero( gen ) ) {
      gen = from_long( 10 );
    }
    return power( gen, num );
  }

  void setGen( const NTL::ZZ_pEX &generator ) { gen = generator; }

  [[nodiscard]] NTL::ZZ_pEX getGen() const { return gen; }

  [[nodiscard]] long fpld2int( const NTL::ZZ_pEX &el ) const {
    if ( NTL::IsZero( el ) )
      return 0;
    NTL::ZZ_pEX ell = NTL::ZZ_pEX( 1 );
    for ( long i = 0; i < n; ++i ) {
      ell = mul( ell, gen );
      if ( ell == el )
        return i + 1;
    }
    std::cout << "el = " << to_string( el ) << std::endl;
    std::cout << "gen = " << to_string( gen ) << std::endl;
    throw std::invalid_argument( "Element not found" );
  }

  // Пример использования для всех известных случаев:

  static void calculate_all_ext_polynomials() {
    // Для p = 2
    for ( long l = 1; l <= 3; ++l ) {
      NTL::ZZ_pX base_poly = get_fixed_base_poly( 2, l );
      for ( long d = 1; d <= 3; ++d ) {  // Используем d от 1 до 3 для примера
        NTL::ZZ_pEX ext_poly = get_fixed_ext_poly( 2, d );
        std::cout << "p = 2, l = " << l << ", d = " << d << ": " << ext_poly
                  << std::endl;
      }
    }

    // Для p = 3
    for ( long l = 1; l <= 3; ++l ) {
      NTL::ZZ_pX base_poly = get_fixed_base_poly( 3, l );
      for ( long d = 1; d <= 3; ++d ) {  // Используем d от 1 до 3 для примера
        NTL::ZZ_pEX ext_poly = get_fixed_ext_poly( 3, d );
        std::cout << "p = 3, l = " << l << ", d = " << d << ": " << ext_poly
                  << std::endl;
      }
    }
  }

  long size() const { return n; }

  static void setPythonFlag( bool flag ) { is_like_python = flag; }

  [[nodiscard]] long getP() const { return p; }
  [[nodiscard]] long getL() const { return l; }
  [[nodiscard]] long getD() const { return d; }

  bool operator==( const Fpld &other ) const {
    return p == other.p && l == other.l && d == other.d && n == other.n &&
           base_poly == other.base_poly && ext_poly == other.ext_poly &&
           mod_ext == other.mod_ext && gen == other.gen;
  }

  bool operator!=(const Fpld& other) const {
    return !(*this == other);
  }

  private:
  static NTL::ZZ_pX get_fixed_base_poly( long p, long l ) {
    NTL::ZZ_pX poly;
    if ( is_like_python ) {
      if ( p == 2 ) {
        if ( l == 1 ) {
          SetCoeff( poly, 1, 1 );
          SetCoeff( poly, 0, 1 );
        } else if ( l == 2 ) {
          SetCoeff( poly, 2, 1 );
          SetCoeff( poly, 1, 1 );
          SetCoeff( poly, 0, 1 );
        } else if ( l == 3 ) {
          SetCoeff( poly, 3, 1 );
          SetCoeff( poly, 1, 1 );
          SetCoeff( poly, 0, 1 );
        }
      } else if ( p == 3 ) {
        if ( l == 1 ) {
          SetCoeff( poly, 1, 1 );
          SetCoeff( poly, 0, 1 );
        } else if ( l == 2 ) {
          SetCoeff( poly, 2, 1 );
          SetCoeff( poly, 1, 1 );
          SetCoeff( poly, 0, 2 );
        } else if ( l == 3 ) {
          SetCoeff( poly, 3, 1 );
          SetCoeff( poly, 1, 2 );
          SetCoeff( poly, 0, 2 );
        }
      } else {
        throw std::invalid_argument( "Unknown (p, l) pair" );
      }
    } else {
      NTL::BuildIrred( poly, l );
    }
    return poly;
  }

  static NTL::ZZ_pEX get_fixed_ext_poly( long p, long d ) {
    NTL::ZZ_pEX poly;
    /// Если нужко как в модели на Python
    if ( is_like_python ) {
      if ( p == 2 ) {
        // Первый коэффициент [0 1]
        {
          NTL::ZZ_pX px;
          SetCoeff( px, 1, 1 );  // 0*x^0 + 1*x^1
          NTL::ZZ_pE e;
          conv( e, px );
          SetCoeff( poly, 0, e );
        }

        // Второй коэффициент [0 1]
        {
          NTL::ZZ_pX px;
          SetCoeff( px, 1, 1 );
          NTL::ZZ_pE e;
          conv( e, px );
          SetCoeff( poly, 1, e );
        }

        // Третий коэффициент [1]
        {
          NTL::ZZ_pX px;
          SetCoeff( px, 0, 1 );
          NTL::ZZ_pE e;
          conv( e, px );
          SetCoeff( poly, 2, e );
        }
      } else {
        // Коэффициент при x^0: [2]
        {
          NTL::ZZ_pX px;
          SetCoeff( px, 0, 2 );  // 2
          NTL::ZZ_pE e;
          conv( e, px );
          SetCoeff( poly, 0, e );
        }

        // Коэффициент при x^1: [0, 2]
        {
          NTL::ZZ_pX px;
          SetCoeff( px, 1, 2 );  // 0*x^0 + 2*x^1
          NTL::ZZ_pE e;
          conv( e, px );
          SetCoeff( poly, 1, e );
        }

        // Коэффициент при x^2: [1]
        {
          NTL::ZZ_pX px;
          SetCoeff( px, 0, 1 );  // 1
          NTL::ZZ_pE e;
          conv( e, px );
          SetCoeff( poly, 2, e );
        }
      }
    } else {
      /// Создаем случайный неприводимый полином
      NTL::BuildIrred( poly, d );  // Если полином приводимый, создаём
                                   // неприводимый полином степени d
    }
    return poly;
  }
  static bool        is_like_python;
  long               p = 2, l = 1, d = 1, n = 0;
  NTL::ZZ_pX         base_poly;
  NTL::ZZ_pEContext  base_ctx;
  NTL::ZZ_pEX        ext_poly;
  NTL::ZZ_pEXModulus mod_ext;
  NTL::ZZ_pEX        gen = NTL::ZZ_pEX( 0 );
};

bool Fpld::is_like_python = true;

/*
export class Fpld {
  public:
      explicit Fpld(long p_val = 2, long l_val = 1, long d_val = 1 ) {
        // Проверка входных параметров
        if ( p_val <= 1 )
          throw std::invalid_argument( "pzz must be > 1" );
        if ( l_val <= 0 )
          throw std::invalid_argument( "l must be > 0" );
        if ( d_val <= 0 )
          throw std::invalid_argument( "d must be > 0" );
        d = d_val;
        p = p_val;
        l = l_val;

      }
//  explicit Fpld( long num = 0, long p_val = 2, long l_val = 1,
//                 long d_val = 1 ) {
//    // Проверка входных параметров
//    if ( p_val <= 1 )
//      throw std::invalid_argument( "pzz must be > 1" );
//    if ( l_val <= 0 )
//      throw std::invalid_argument( "l must be > 0" );
//    if ( d_val <= 0 )
//      throw std::invalid_argument( "d must be > 0" );
//    d = d_val;
//    p = p_val;
//    // 1. Инициализация базового поля F_p
//    auto pzz = NTL::ZZ( p_val );
//    NTL::ZZ_p::init( pzz );
//
//    l = l_val;  // Просто сохраняем l_val как long
//    n = std::pow( p, std::pow( l, d ) );
//    // 2. Построение F_{pzz^l}
//    NTL::BuildIrred( base_poly, l_val );
//    NTL::ZZ_pE::init( base_poly );
//    base_ctx.save();
//
//    // 3. Построение F_{(pzz^l)^d} (неприводимый многочлен степени d над
//    // F_{pzz^l})
//    NTL::BuildIrred( ext_poly, d_val );
//    mod_ext = NTL::ZZ_pEXModulus( ext_poly );
//
//    // 4. Преобразование num в элемент F_{(pzz^l)^d}
//    val = NTL::ZZ_pEX();
//    NTL::ZZ nn( num );
//    NTL::ZZ q = NTL::power( pzz, l_val );  // q = pzz^l (размерность F_{pzz^l})
//
//    for ( long i = 0; i < d_val && nn != 0; ++i ) {
//      NTL::ZZ rem;
//      NTL::DivRem( nn, rem, nn, q );  // rem = nn % q, nn = nn / q
//
//      // Преобразуем rem в элемент F_{pzz^l}:
//      base_ctx.restore();
//      NTL::ZZ_pX poly_rep;
//
//      // Правильное преобразование rem в полином степени < l над F_p
//      for ( long j = 0; j < l_val; ++j ) {
//        NTL::ZZ bit;
//        NTL::DivRem( rem, bit, rem, pzz );  // Извлекаем цифры по основани pzz
//        SetCoeff( poly_rep, j, NTL::conv<NTL::ZZ_p>( bit ) );
//      }
//
//      NTL::ZZ_pE coeff;
//      NTL::conv( coeff, poly_rep );  // Полином → элемент F_{pzz^l}
//      SetCoeff( val, i, coeff );     // Записываем коэффициент при Y^i
//    }
//
//    // Приведение по модулю ext_poly (если степень val >= d)
//    NTL::rem( val, val, ext_poly );
//    std::cout << "All params" << std::endl;
//    std::cout << "d = " << d << std::endl;
//    std::cout << "p = " << p << std::endl;
//    std::cout << "l = " << l << std::endl;
//    std::cout << "n = " << n << std::endl;
//    std::cout << "base_poly = " << base_poly << std::endl;
//    std::cout << "ext_poly = " << ext_poly << std::endl;
//    //    std::cout << "base_ctx = " << base_ctx << std::endl;
//    std::cout << "mod_ext = " << mod_ext << std::endl;
//    std::cout << "val = " << val << std::endl;
//  }

  Fpld( const Fpld &other ) {
    d         = other.d;
    p         = other.p;
    l         = other.l;
    n         = other.n;
    base_poly = other.base_poly;
    ext_poly  = other.ext_poly;
    base_ctx  = other.base_ctx;
    mod_ext   = other.mod_ext;
    val       = other.val;
  }

  void print() const {
    std::cout << "val = [";
    for ( long i = 0; i <= deg( val ); ++i ) {
      NTL::ZZ_pX poly_rep =
          rep( coeff( val, i ) );  // Элемент F_{p^l} → полином
      std::cout << "[";
      for ( long j = 0; j < l; ++j ) {  // Всегда выводим l коэффициентов
        std::cout << coeff( poly_rep, j );
        if ( j < l - 1 )
          std::cout << " ";
      }
      std::cout << "]";
      if ( i < deg( val ) )
        std::cout << " ";
    }
    std::cout << "]" << std::endl;

    //    std::cout << "debug = " << val << std::endl;
  }

  Fpld &operator=( const Fpld &other ) {
    if ( this == &other )
      return *this;
    d         = other.d;
    p         = other.p;
    l         = other.l;
    n         = other.n;
    base_poly = other.base_poly;
    ext_poly  = other.ext_poly;
    base_ctx  = other.base_ctx;
    mod_ext   = other.mod_ext;
    val       = other.val;
    return *this;
  }

  // Сложение в F_{p^{l^d}}
  Fpld operator+( const Fpld &other ) const {
    Fpld result( *this );
    result.val = val + other.val;
    NTL::rem( result.val, result.val, mod_ext );  // приведение по модулю
    return result;
  }


  Fpld operator*( const Fpld &other ) const {
    Fpld result = *this;
    NTL::MulMod( result.val, val, other.val, mod_ext );
    return result;
  }

  [[nodiscard]] Fpld power( long k ) const {
    Fpld result = *this;
    NTL::PowerMod( result.val, val, k, mod_ext );
    return result;
  }

  [[nodiscard]] Fpld inverse() const {
    Fpld result = *this;
    NTL::InvMod( result.val, val, mod_ext );
    return result;
  }


  // В Fpld.h
  [[nodiscard]] NTL::ZZ_pEX get_value() const { return val; }

  [[nodiscard]] long get_p() const { return NTL::conv<long>( p ); }

  [[nodiscard]] long get_l() const { return l; }

  [[nodiscard]] long get_d() const { return d; }

  [[nodiscard]] bool isZero() const { return IsZero( val ); }

  bool operator==( const Fpld &other ) const { return val == other.val; }

  bool operator!=( const Fpld &other ) const { return val != other.val; }

  bool operator==( const NTL::ZZ_pEX &other ) const { return val == other; }

  bool operator!=( const NTL::ZZ_pEX &other ) const { return val != other; }

  [[nodiscard]] Fpld int2Fpld( long num ) const {
    if ( num == 0 )
      return Fpld( 0, this->get_p(), this->get_l(), this->get_d() );
    return this->power( num );
  }

  // Основная функция преобразования
  long fpld2int( const NTL::ZZ_pEX &generator ) {
    // Проверка нулевого элемента
    if ( this->isZero() )
      return 0;

    // Создаем единичный элемент
    NTL::ZZ_pEX one;
    SetCoeff( one, 0, 1 );
    // Проверка единичного элемента
    if ( val == one )
      return 1;

    NTL::ZZ_pEX current = generator;  // Начинаем с образующего элемента

    // Ищем совпадение, перебирая степени
    for ( long i = 1; i < n; ++i ) {
      if ( val == current ) {
        return i + 1;
      }
      current *= generator;  // Умножаем на образующий элемент
    }

    throw std::runtime_error( "Element not found in first n powers" );
  }

  private:
  long               p;          // основание поля
  long               l;          // степень поля
  long               d;          // степень расширения
  long               n;          // размер поля
  NTL::ZZ_pX         base_poly;  // неприводимый полином степени l над F_p
  NTL::ZZ_pEX        ext_poly;   // неприводимый полином степени d над F_{p^l}
  NTL::ZZ_pEContext  base_ctx;   // контекст поля F_{p^l}
  NTL::ZZ_pEXModulus mod_ext;    // модуль по которому работает расширение

  NTL::ZZ_pEX val;  // сам элемент поля F_{p^{l^d}} — представляется как полином
                    // по модулю
};
 */