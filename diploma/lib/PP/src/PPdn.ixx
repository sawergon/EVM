module;
#include <sstream>
#include <vector>
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pE.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_pXFactoring.h>
export module PPdn;
import Fpl;

export class PPBlockId {
  public:
  PPBlockId( Fpl *f = nullptr )
      : field( f )
      , a( 0 )
      , b( 0 )
      , c( 0 ) {}

  PPBlockId( Fpl *f, NTL::ZZ_pE a, NTL::ZZ_pE b, NTL::ZZ_pE c ) {
    field   = f;
    this->a = a;
    this->b = b;
    this->c = c;
  }

  PPBlockId( long i, Fpl *f )
      : field( f )
      , a( 0 )
      , b( 0 )
      , c( 0 ) {
    if ( i == 0 ) {
      c = NTL::ZZ_pE( 1 );
    } else if ( i - 1 < field->size() ) {
      b = NTL::ZZ_pE( 1 );
      c = field->int2Fpl( i - 1 );
    } else {
      for ( long cc = 0; cc < field->size(); ++cc ) {
        for ( long bb = 0; bb < field->size(); ++bb ) {
          if ( i == ( 1 + field->size() + cc + bb * field->size() ) ) {
            a = NTL::ZZ_pE( 1 );
            b = field->int2Fpl( bb );
            c = field->int2Fpl( cc );
            return;
          }
        }
      }
    }
  }

  PPBlockId( const PPBlockId &other ) {
    field = other.field;
    a     = other.a;
    b     = other.b;
    c     = other.c;
  }

  PPBlockId &operator=( const PPBlockId &other ) {
    if ( this == &other )
      return *this;
    field = other.field;
    a     = other.a;
    b     = other.b;
    c     = other.c;
    return *this;
  }

  long to_int() const {
    NTL::ZZ_pE zero( 0 );
    NTL::ZZ_pE one( 1 );
    if ( a == zero && b == zero && c == one )
      return 0;
    else if ( a == zero && b == one )
      return field->fpl2int( c ) + 1;
    if ( a == one ) {
      return 1 + field->size() + field->fpl2int( c ) +
             field->size() * field->fpl2int( b );
    }
    throw std::invalid_argument( "Unknown block id" );
  }

  std::string to_string() const {
    return "[" + field->to_string( a ) + ", " + field->to_string( b ) + ", " +
           field->to_string( c ) + "]";
  }

  bool operator==( const PPBlockId &other ) {
    return a == other.a && b == other.b && c == other.c;
  }

  bool operator!=( const PPBlockId &other ) { return !( *this == other ); }

  void setA( NTL::ZZ_pE aa ) { a = aa; }

  void setB( NTL::ZZ_pE bb ) { b = bb; }

  void setC( NTL::ZZ_pE cc ) { c = cc; }

  NTL::ZZ_pE getA() { return a; }
  NTL::ZZ_pE getB() { return b; }
  NTL::ZZ_pE getC() { return c; }

  Fpl *getField() { return field; }

  private:
  Fpl       *field;
  NTL::ZZ_pE a, b, c;
};

export class PPDualBlockId {
  public:
  PPDualBlockId( Fpl *f = nullptr )
      : field( f )
      , x( 0 )
      , y( 0 )
      , z( 0 ) {}

  PPDualBlockId( const PPDualBlockId &other ) {
    field = other.field;
    x     = other.x;
    y     = other.y;
    z     = other.z;
  }
  PPDualBlockId( Fpl *f, NTL::ZZ_pE x, NTL::ZZ_pE y, NTL::ZZ_pE z )
      : field( f )
      , x( x )
      , y( y )
      , z( z ) {}
  PPDualBlockId( long i, Fpl *f )
      : field( f )
      , x( 0 )
      , y( 0 )
      , z( 0 ) {
    if ( i == 0 ) {
      x = NTL::ZZ_pE( 1 );
    } else if ( i - 1 < field->size() ) {
      x = field->int2Fpl( i - 1 );
      y = NTL::ZZ_pE( 1 );
    } else {
      for ( long xx = 0; xx < field->size(); ++xx ) {
        for ( long yy = 0; yy < field->size(); ++yy ) {
          if ( i == ( 1 + field->size() + xx + yy * field->size() ) ) {
            x = field->int2Fpl( xx );
            y = field->int2Fpl( yy );
            z = NTL::ZZ_pE( 1 );
          }
        }
      }
    }
    std::invalid_argument( "Unknown dualblock id" );
  }

  long to_int() const {
    NTL::ZZ_pE zero( 0 );
    NTL::ZZ_pE one( 1 );
    if ( x == one && y == zero && z == zero ) {
      return 0;
    }
    if ( y == one && z == zero ) {
      return field->fpl2int( x ) + 1;
    }
    if ( z == one ) {
      return 1 + field->size() + field->fpl2int( x ) +
             field->fpl2int( y ) * field->size();
    }
    throw std::invalid_argument( "Unknown dueal block id" );
  }

  std::string to_string() const {
    return "[" + field->to_string( x ) + ", " + field->to_string( y ) + ", " +
           field->to_string( z ) + "]";
  }

  bool operator==( const PPDualBlockId &other ) {
    return x == other.x && y == other.y && z == other.z;
  }

  bool operator!=( const PPDualBlockId &other ) { return !( *this == other ); }

  NTL::ZZ_pE getX() { return x; }
  NTL::ZZ_pE getY() { return y; }
  NTL::ZZ_pE getZ() { return z; }

  void setX( NTL::ZZ_pE xx ) { x = xx; }
  void setY( NTL::ZZ_pE yy ) { y = yy; }
  void setZ( NTL::ZZ_pE zz ) { z = zz; }

  Fpl *getField() { return field; }

  private:
  Fpl       *field;
  NTL::ZZ_pE x, y, z;
};

export class PPBlock {
  public:
  PPBlock( const PPBlockId &id )
      : id( id ) {
    internalConstructor();
  }

  PPBlock( long i, Fpl *field )
      : id( i, field ) {
    internalConstructor();
  }

  std::string to_string() {
    std::stringstream ss;
    ss << "[";
    for ( const auto &i : values ) {
      ss << i.to_string() << ", ";
    }
    ss << "\b\b]";
    return ss.str();
  }

  std::string to_string_int() {
    std::stringstream ss;
    ss << "[";
    for ( auto i : indexes ) {
      ss << i << ", ";
    }
    ss << "\b\b]";
    return ss.str();
  }

  private:
  void internalConstructor() {
    PPBlockId  block{};
    NTL::ZZ_pE zero( 0 );
    NTL::ZZ_pE one( 1 );
    block.setC( one );
    auto field = id.getField();
    if ( id == block ) {
      for ( long i = 0; i < field->size(); ++i ) {
        values.emplace_back( field, field->int2Fpl( i ), one, zero );
      }
      values.emplace_back( field, one, zero, zero );
    }

    block.setB( one );
    block.setC( id.getC() );
    if ( block == id ) {
      for ( long i = 0; i < field->size(); ++i ) {
        values.emplace_back( field, field->int2Fpl( i ),
                             field->sub( zero, id.getC() ), one );
      }
      values.emplace_back( field, one, zero, zero );
    }

    block.setA( one );
    block.setB( id.getB() );
    if ( id == block ) {
      for ( long i = 0; i < field->size(); ++i ) {
        auto value = field->sub(
            zero, field->add( field->mul( id.getB(), field->int2Fpl( i ) ),
                              id.getC() ) );
        values.emplace_back( field, value, field->int2Fpl( i ), one );
      }
      values.emplace_back( field, field->sub( zero, id.getB() ), one, zero );
    }

    for ( const auto &el : values ) {
      indexes.emplace_back( el.to_int() );
    }
  }
  std::vector<PPDualBlockId> values;
  std::vector<long>          indexes;
  PPBlockId                  id;
};

export class PPDualBlock {
  public:
  PPDualBlock( const PPDualBlockId &id )
      : id( id ) {
    internalConstructor();
  }

  PPDualBlock( long i, Fpl *field )
      : id( i, field ) {
    internalConstructor();
  }

  std::string to_string() {
    std::stringstream ss;
    ss << "[";
    for ( const auto &i : values ) {
      ss << i.to_string() << ", ";
    }
    ss << "\b\b]";
    return ss.str();
  }

  std::string to_string_int() {
    std::stringstream ss;
    ss << "[";
    for ( auto i : indexes ) {
      ss << i << ", ";
    }
    ss << "\b\b]";
    return ss.str();
  }

  private:
  void internalConstructor() {
    PPDualBlockId block{};
    NTL::ZZ_pE    zero( 0 );
    NTL::ZZ_pE    one( 1 );
    block.setX( one );
    auto field = id.getField();
    if ( id == block ) {
      for ( long i = 0; i < field->size(); ++i ) {
        values.emplace_back( field, zero, one, field->int2Fpl( i ) );
      }
      values.emplace_back( field, zero, zero, one );
    }

    block.setY( one );
    block.setX( id.getX() );
    if ( block == id ) {
      for ( long i = 0; i < field->size(); ++i ) {
        values.emplace_back( field, one, field->sub( zero, id.getX() ),
                             field->int2Fpl( i ) );
      }
      values.emplace_back( field, zero, zero, one );
    }

    block.setZ( one );
    block.setY( id.getY() );
    if ( id == block ) {
      for ( long i = 0; i < field->size(); ++i ) {
        auto value = field->sub(
            zero, field->add( field->mul( field->int2Fpl( i ), id.getY() ),
                              id.getX() ) );
        values.emplace_back( field, one, field->int2Fpl( i ), value );
      }
      values.emplace_back( field, zero, one, field->sub( zero, id.getY() ) );
    }

    for ( const auto &el : values ) {
      indexes.emplace_back( el.to_int() );
    }
  }

  std::vector<PPBlockId> values;
  std::vector<long>      indexes;
  PPDualBlockId          id;
};

struct block_cache {
  PPBlock value;
  bool    isPublished;
};

struct dual_block_cache {
  PPDualBlock value;
  bool        isPublished;
};

export class PPdn {
  public:
  explicit PPdn( long degree = 2, long p = 2, long l = 1,
                 bool isCached = false )
      : isCached( isCached ) {
    field = Fpl( p, l );
    n     = NTL::power_long( p, l );
    if ( degree == 2 ) {
      v      = n * n + n + 1;
      k      = n + 1;
      lambda = 1;
    } else if ( degree == 3 ) {
      k      = n * n + n + 1;
      v      = n * n * n + n * n + n + 1;
      lambda = n + 1;
    }
    if ( isCached ) {
      blocks.reserve( v );
      dual_blocks.reserve( v );
    }
  }

  PPBlock operator[]( long i ) {
    if ( isCached ) {
      if ( blocks[i % blocks.size()].isPublished ) {
        return blocks[i % blocks.size()].value;
      }
    }

    PPBlock result( i, &field );

    if ( isCached ) {
      blocks[i % blocks.size()].value       = result;
      blocks[i % blocks.size()].isPublished = true;
    }
    return result;
  }

  PPBlock operator[]( const PPBlockId &id ) {
    return this->operator[]( id.to_int() );
  }

  PPDualBlock operator()( long i ) {
    if ( isCached ) {
      if ( dual_blocks[i % dual_blocks.size()].isPublished ) {
        return dual_blocks[i % dual_blocks.size()].value;
      }
    }

    PPDualBlock result( i, &field );

    if ( isCached ) {
      dual_blocks[i % dual_blocks.size()].value       = result;
      dual_blocks[i % dual_blocks.size()].isPublished = true;
    }
    return result;
  }

  PPDualBlock operator()( const PPDualBlockId &id ) {
    return this->operator()( id.to_int() );
  }
  long size() { return v; }

  private:
  long                          v, k, lambda, n;
  Fpl                           field;
  bool                          isCached = false;
  std::vector<block_cache>      blocks;
  std::vector<dual_block_cache> dual_blocks;
};
