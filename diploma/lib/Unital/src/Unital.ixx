module;
#include <cmath>
#include <vector>
#include <NTL/ZZ_pEX.h>
export module Unital;
import PGpl2;
import Fpld;

export class UnitalBlock;

bool hermitFilter( const BlockId &block ) {
  auto field = block.getField();
  long q     = static_cast<long>( std::sqrt( field->size() ) ) + 1;
  auto xq    = field->power( block.x(), q );
  auto yq    = field->power( block.y(), q );
  auto zq    = field->power( block.z(), q );
  auto s     = field->add( field->add( xq, yq ), zq );
  return IsZero( s );
}

bool hermitFilter( const DualBlockId &block ) {
  auto field = block.getField();
  long q     = static_cast<long>( std::sqrt( field->size() ) ) + 1;
  auto xq    = field->power( block.x(), q );
  auto yq    = field->power( block.y(), q );
  auto zq    = field->power( block.z(), q );
  auto s     = field->add( field->add( xq, yq ), zq );
  return IsZero( s );
}

export class UnitalBlock : public PGBlock {
  public:
  UnitalBlock() = default;
  [[nodiscard]] bool isEmpty() const { return values.empty(); }
  /// может быть пустой результат так как не все BlockId являются частью
  /// Юнитального дизайна
  explicit UnitalBlock( const BlockId &id )
      : id_( id ) {
    UnitalBlock::internalConstructor();
  }

  explicit UnitalBlock( long i, Fpld *field ) {
    /// Поиск первого подходящего идентификатора
    auto id = BlockId( i, field );
    while ( hermitFilter( id ) ) {
      id = BlockId( ++i, field );
    }
    id_ = id;
    UnitalBlock::internalConstructor();
  }

  DualBlockId intersection( const BlockId &other ) {
    DualBlockId result = id_ * other;
    return hermitFilter( result ) ? result : DualBlockId();
  }

  DualBlockId operator*( const BlockId &other ) {
    return intersection( other );
  }

  ~UnitalBlock() = default;

  private:
  void internalConstructor() {
    if ( !hermitFilter( id_ ) ) {
      PGBlock a( id_ );
      for ( long i = 0; i < a.size(); i++ ) {
        if ( hermitFilter( a( i ) ) ) {
          values.push_back( a( i ) );
          indexes.push_back( a[i] );
        }
      }
    }
  }
  std::vector<DualBlockId> values;
  std::vector<long>        indexes;
  BlockId                  id_;
};

export class UnitalDualBlock : public PGDualBlock {
  public:
  UnitalDualBlock() = default;
  [[nodiscard]] bool isEmpty() const { return values.empty(); }

  explicit UnitalDualBlock( const DualBlockId &id )
      : id_( id ) {
    internalConstructor();
  }

  UnitalDualBlock( long i, Fpld *field ) {
    auto id = DualBlockId( i, field );
    while (!hermitFilter(id)) {
      id = DualBlockId(++i, field);
    }
    id_ = id;
    internalConstructor();
  }

  BlockId intersection( const DualBlockId &other ) {
    BlockId result = id_ * other;
    return hermitFilter( result ) ? result : BlockId();
  }

  BlockId operator*( const DualBlockId &other ) {
    return intersection( other );
  }

  private:
  void internalConstructor() {
    if ( hermitFilter( id_ ) ) {
      PGDualBlock a( id_ );
      for ( long i = 0; i < a.size(); i++ ) {
        if ( !hermitFilter( a( i ) ) ) {
          values.push_back( a( i ) );
          indexes.push_back( a[i] );
        }
      }
    }
  }
  std::vector<BlockId> values;
  std::vector<long>    indexes;
  DualBlockId          id_;
};


struct block_cache_page {
  UnitalBlock value{};              /// Значение
  bool        isPublished = false;  /// Записано ли значение в кэш
};

struct dual_block_cache_page {
  UnitalDualBlock value{};              /// Значение
  bool            isPublished = false;  /// Записано ли значение в кэш
};

export class Unital {
  public:
  explicit Unital( Fpld f, bool isCached = false,
                   NTL::ZZ_pEX general = NTL::ZZ_pEX( 0 ) )
      : field( std::move( f ) )
      , isCached( isCached )
      , gen( std::move( general ) ) {
    field.setGen( gen );
    setParams();
  }
  explicit Unital( long p, long l, bool isCached = false,
                   NTL::ZZ_pEX general = NTL::ZZ_pEX( 0 ) )
      : isCached( isCached )
      , gen( std::move( general ) ) {
    field = Fpld( p, l, d );
    field.setGen( gen );
    setParams();
    if ( isCached ) {
      block_cache.reserve( field.size() );
    }
  }
  UnitalBlock operator[]( long i ) {

    if ( isCached ) {
      if ( block_cache[i % block_cache.size()].isPublished ) {
        return block_cache[i % block_cache.size()].value;
      }
    }

    UnitalBlock result( i, &field );

    if ( isCached ) {
      block_cache[i % block_cache.size()].value       = result;
      block_cache[i % block_cache.size()].isPublished = true;
    }
    return result;
  }

  UnitalDualBlock operator()( long i ) {
    if ( isCached ) {
      if ( dual_block_cache[i % dual_block_cache.size()].isPublished ) {
        return dual_block_cache[i % dual_block_cache.size()].value;
      }
    }

    UnitalDualBlock result( i, &field );

    if ( isCached ) {
      dual_block_cache[i % dual_block_cache.size()].value       = result;
      dual_block_cache[i % dual_block_cache.size()].isPublished = true;
    }
    return result;
  }

  BlockId getBlockId(long i) {
    auto id = BlockId(i, &field);
    while ( hermitFilter(id)) {
      id = BlockId(i, &field);
    }
    return id;
  }

  DualBlockId getDualBlockId(long i) {
    auto id = DualBlockId(i, &field);
    while (!hermitFilter(id)) {
      id = DualBlockId(++i, &field);
    }
    return id;
  }

  long size() const { return b; }
  long getN() const { return n; }
  /// размер параллельного класса Юнитала
  long getS() const { return s; }
  Fpld getField() const { return field; }

  bool operator==( const Unital &other ) {
    return b == other.n && db == other.db && s == other.s && n == other.n &&
           d == other.d && gen == other.gen && field == other.field;
  }

  bool operator!=( const Unital &other ) { return !( *this == other ); }

  Unital &operator=( const Unital &other ) {
    if ( *this == other )
      return *this;
    b        = other.b;
    db       = other.db;
    s        = other.s;
    n        = other.n;
    d        = other.d;
    gen      = other.gen;
    field    = other.field;
    isCached = other.isCached;
    if ( isCached ) {
      block_cache.reserve( b );
      dual_block_cache.reserve( db );
    }
    return *this;
  }

  ~Unital() = default;

  private:
  void setParams() {
    n = field.size() / d;  /// Поскольку юнитал над квадратичным расширенией
    b = NTL::power_long( n, 4 ) - NTL::power_long( n, 3 ) +
        NTL::power_long( n, 2 );
    s  = b / n;
    db = NTL::power_long( n, 3 ) + 1;
  }
  long        b;      /// колво блоков
  long        db;     /// колво дуальных блоков
  long        s;      /// размер параллельного класса
  long        n;      /// p^l
  long        d = 2;  /// расширение в данном случае всегда квадратичное
  NTL::ZZ_pEX gen;    /// Образующий
  Fpld        field;  /// Поле
  bool        isCached = false;                         /// Кэшировать значения
  std::vector<block_cache_page>      block_cache;       /// Кэш
  std::vector<dual_block_cache_page> dual_block_cache;  /// Кэш
};
