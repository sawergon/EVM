module;
#include <cmath>
#include <NTL/ZZ_pE.h>

export module Unital;

/// Поле Fpld при d = 2
export class Unital {
  public:
  Unital( const long p, const long l )
      : p( p )
      , l( l )
      , n( static_cast<long>( std::pow( std::pow( p, l ), 2 ) ) ) {};

  ~Unital() = default;

  private:
  long       p, l, n;
  const long d = 2;
};
