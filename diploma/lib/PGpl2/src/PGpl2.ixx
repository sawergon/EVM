module;
#include "NTL/ZZ_pEX.h"
#include <memory>
#include <sstream>
#include <utility>
#include <vector>
export module PGpl2;
import Fpld;

namespace pgpl2 {
export class DualBlockId;

export class BlockId {
  public:
    explicit BlockId(Fpld *f = nullptr)
      : field(f)
        , x_(0)
        , y_(0)
        , z_(0) {
    }
    bool isValid() const { return field != nullptr; }
    explicit BlockId(long i, Fpld *f)
      : x_(0), y_(0)
        , z_(0)
        , field(f) {
      if (i == 0) {
        z_ = NTL::ZZ_pEX(1);
      } else {
        if (i <= field->size()) {
          y_ = NTL::ZZ_pEX(1);
          z_ = field->int2Fpld(i - 1);
        } else {
          long r = (i - 1) % field->size();
          long q = (i - 1 - r) / field->size();
          if (q == 1) {
            x_ = NTL::ZZ_pEX(1);
            z_ = field->int2Fpld(r);
          } else {
            x_ = NTL::ZZ_pEX(1);
            y_ = field->int2Fpld(q - 1);
            z_ = field->int2Fpld(r);
          }
        }
      }
    }

    explicit BlockId(Fpld *f, NTL::ZZ_pEX x, NTL::ZZ_pEX y, NTL::ZZ_pEX z)
      : field(f)
        , x_(std::move(x))
        , y_(std::move(y))
        , z_(std::move(z)) {
    }

    [[nodiscard]] NTL::ZZ_pEX x() const { return x_; }
    [[nodiscard]] NTL::ZZ_pEX y() const { return y_; }
    [[nodiscard]] NTL::ZZ_pEX z() const { return z_; }

    void setX(const NTL::ZZ_pEX &x) { x_ = x; }
    void setY(const NTL::ZZ_pEX &y) { y_ = y; }
    void setZ(const NTL::ZZ_pEX &z) { z_ = z; }

    void setField(Fpld *f) { field = f; }
    [[nodiscard]] Fpld *getField() const { return field; }
    [[nodiscard]] long to_int() const {
      BlockId block{*this};
      BlockId tmp{field};
      auto one = NTL::ZZ_pEX(1);
      tmp.setZ(one);
      if (tmp == block) {
        return 0;
      }
      if (NTL::IsZero(block.x()) && block.y() == one) {
        return 1 + field->fpld2int(block.z());
      }
      long n1 = field->fpld2int(block.y());
      long n2 = field->fpld2int(block.z());
      return 1 + field->size() + field->size() * n1 + n2;
    }

    bool operator==(const BlockId &other) const {
      return x_ == other.x_ && y_ == other.y_ && z_ == other.z_;
    }
    bool operator!=(const BlockId &other) const {
      return x_ != other.x_ || y_ != other.y_ || z_ != other.z_;
    }
    [[nodiscard]] std::string to_string() const {
      return "[" + field->to_string(x_) + ", " + field->to_string(y_) +
          ", " + field->to_string(z_) + "]";
    }

    DualBlockId intersection(const BlockId &other) const;

    DualBlockId operator*(const BlockId &other) const;
    ~BlockId() = default;

  private:
    NTL::ZZ_pEX x_ = NTL::ZZ_pEX(0);
    NTL::ZZ_pEX y_ = NTL::ZZ_pEX(0);
    NTL::ZZ_pEX z_ = NTL::ZZ_pEX(0);
    Fpld *field = nullptr;
};

export class BlockId;

export class DualBlockId {
  public:
    explicit DualBlockId(Fpld *f = nullptr)
      : field(f)
        , x_(0)
        , y_(0)
        , z_(0) {
    }
    bool isValid() { return field != nullptr; }
    explicit DualBlockId(long i, Fpld *f)
      : field(f)
        , x_(0)
        , y_(0)
        , z_(0) {
      if (i == 0) {
        x_ = NTL::ZZ_pEX(1);
      } else {
        if (i <= field->size()) {
          y_ = NTL::ZZ_pEX(1);
          x_ = field->int2Fpld(i - 1);
        } else {
          long r = (i - 1) % field->size();
          long q = (i - 1 - r) / field->size();
          if (q == 1) {
            z_ = NTL::ZZ_pEX(1);
            x_ = field->int2Fpld(r);
          } else {
            z_ = NTL::ZZ_pEX(1);
            y_ = field->int2Fpld(q - 1);
            x_ = field->int2Fpld(r);
          }
        }
      }
    }
    explicit DualBlockId(Fpld *f, NTL::ZZ_pEX x, NTL::ZZ_pEX y, NTL::ZZ_pEX z)
      : field(f)
        , x_(std::move(x))
        , y_(std::move(y))
        , z_(std::move(z)) {
    }
    [[nodiscard]] NTL::ZZ_pEX x() const { return x_; }
    [[nodiscard]] NTL::ZZ_pEX y() const { return y_; }
    [[nodiscard]] NTL::ZZ_pEX z() const { return z_; }

    void setX(const NTL::ZZ_pEX &x) { x_ = x; }
    void setY(const NTL::ZZ_pEX &y) { y_ = y; }
    void setZ(const NTL::ZZ_pEX &z) { z_ = z; }

    void setField(Fpld *f) { field = f; }
    [[nodiscard]] Fpld *getField() const { return field; }
    [[nodiscard]] long to_int() const {
      DualBlockId block{field, x_, y_, z_};
      DualBlockId tmp{field};
      auto one = NTL::ZZ_pEX(1);
      tmp.setX(one);
      if (tmp == block) {
        return 0;
      }
      if (NTL::IsZero(block.z()) && block.y() == one) {
        return 1 + field->fpld2int(block.x());
      }
      long n1 = field->fpld2int(block.y());
      long n2 = field->fpld2int(block.x());
      return 1 + field->size() + field->size() * n1 + n2;
    }

    [[nodiscard]] std::string to_string() const {
      return "[" + field->to_string(x_) + ", " + field->to_string(y_) +
          ", " + field->to_string(z_) + "]";
    }

    BlockId intersection(const DualBlockId &other) const;

    BlockId operator*(const DualBlockId &other) const;

    bool operator==(const DualBlockId &other) const {
      return x_ == other.x_ && y_ == other.y_ && z_ == other.z_;
    }
    bool operator!=(const DualBlockId &other) const {
      return x_ != other.x_ || y_ != other.y_ || z_ != other.z_;
    }
    ~DualBlockId() = default;

  private:
    NTL::ZZ_pEX x_ = NTL::ZZ_pEX(0);
    NTL::ZZ_pEX y_ = NTL::ZZ_pEX(0);
    NTL::ZZ_pEX z_ = NTL::ZZ_pEX(0);
    Fpld *field = nullptr;
};

DualBlockId BlockId::intersection(const BlockId &other) const {
  auto zero = NTL::ZZ_pEX(0);
  auto one = NTL::ZZ_pEX(1);

  if (x_ == zero && other.x_ == zero && (other.y_ == one || y_ == one))
    return DualBlockId(field, one, zero, zero);

  if (other.x_ == one && y_ == zero && x_ == zero) {
    auto val = field->sub(zero, other.y_);
    return DualBlockId{field, val, one, zero};
  }

  if (other.y_ == zero && other.x_ == zero && x_ == one) {
    auto val = field->sub(zero, y_);
    return DualBlockId{field, val, one, zero};
  }

  if (x_ == zero && other.x_ == zero && y_ == one && other.y_ == one)
    return DualBlockId{field, one, zero, zero};

  if (x_ == one && other.y_ == one && other.x_ == zero) {
    auto num = field->sub(field->mul(other.z_, y_), z_);
    auto y = field->sub(zero, other.z_);
    return DualBlockId{field, num, y, one};
  }

  if (y_ == one && other.x_ == one && x_ == zero) {
    auto num = field->sub(field->mul(z_, other.y_), other.z_);
    auto y = field->sub(zero, z_);
    return DualBlockId{field, num, y, one};
  }

  if (x_ == one && other.x_ == one && y_ == other.y_) {
    auto val = field->sub(zero, y_);
    return DualBlockId{field, val, one, zero};
  }

  auto numerator = field->sub(z_, other.z_);
  auto denominator = field->sub(other.y_, y_);
  auto y = field->mul(numerator, field->inv(denominator));
  auto x = field->sub(zero, field->add(z_, field->mul(y, y_)));

  return DualBlockId{field, x, y, one};
}

DualBlockId BlockId::operator*(const BlockId &other) const {
  return intersection(other);
}

BlockId DualBlockId::intersection(const DualBlockId &other) const {
  auto zero = NTL::ZZ_pEX(0);
  auto one = NTL::ZZ_pEX(1);

  if (z_ == zero && other.z_ == zero && (y_ == one || other.y_ == one))
    return BlockId(field, zero, zero, one);

  if (y_ == zero && z_ == zero && other.z_ == one)
    return BlockId(field, zero, one, field->sub(zero, other.y_));

  if (other.y_ == zero && other.z_ == zero && z_ == one)
    return BlockId(field, one, field->sub(zero, y_), zero);

  if (y_ == one && other.y_ == one && other.z_ == zero && z_ == zero)
    return BlockId(field, zero, zero, one);

  if (z_ == one && other.y_ == one && other.z_ == zero)
    return BlockId(field,
                   one,
                   field->sub(zero, other.x_),
                   field->sub(field->mul(other.x_, y_), x_));

  if (other.z_ == one && y_ == one && z_ == zero)
    return BlockId(field,
                   one,
                   field->sub(zero, x_),
                   field->sub(field->mul(x_, other.y_), other.x_));

  if (z_ == one && other.z_ == one && y_ == other.y_)
    return BlockId(field, zero, one, field->sub(zero, y_));
  auto y = field->mul(field->sub(x_, other.x_),
                      field->inv(field->sub(other.y_, y_)));
  return BlockId(field,
                 one,
                 y,
                 field->sub(zero, field->add(x_, field->mul(y, y_))));
}

BlockId DualBlockId::operator*(const DualBlockId &other) const {
  return intersection(other);
}

/// Блок состоит из дуальных блоков
export class PGBlock {
  public:
    PGBlock() = default;
    explicit PGBlock(const BlockId &id) {
      id_ = id;
      internalConstructor();
    }

    explicit PGBlock(long i, Fpld *f) {
      id_ = BlockId(i, f);
      internalConstructor();
    }

    long size() { return static_cast<long>(values.size()); }

    long getIntId() { return id_.to_int(); }
    BlockId getId() { return id_; }

    long operator[](long i) { return indexes[i]; }
    DualBlockId operator()(long i) { return values[i]; }

    [[nodiscard]] std::string to_string_int() const {
      std::stringstream ss;
      ss << "[";
      for (auto i : indexes) {
        ss << i << ", ";
      }
      ss << "\b\b]";
      return ss.str();
    }

    [[nodiscard]] std::string to_string() const {
      std::stringstream ss;
      ss << "[";
      for (const auto &i : values) {
        ss << i.to_string() << ", ";
      }
      ss << "\b\b]";
      return ss.str();
    }

  private:
    void internalConstructor() {
      BlockId block;
      auto one = NTL::ZZ_pEX(1);
      auto zero = NTL::ZZ_pEX(0);

      block.setZ(one);
      auto field = id_.getField();
      if (id_ == block) {
        for (int i = 0; i < field->size(); i++) {
          values.emplace_back(field, field->int2Fpld(i), one, zero);
        }
        values.emplace_back(field, one, zero, zero);
      }

      block.setZ(id_.z());
      block.setY(one);
      if (id_ == block) {
        auto subc = field->sub(zero, block.z());
        for (int i = 0; i < field->size(); i++) {
          values.emplace_back(field, field->int2Fpld(i), subc, one);
        }
        values.emplace_back(field, one, zero, zero);
      }

      block.setX(one);
      block.setY(id_.y());
      if (id_ == block) {
        for (int i = 0; i < field->size(); i++) {
          auto y = field->int2Fpld(i);
          auto value = field->sub(
            zero,
            field->add(block.z(), field->mul(block.y(), y)));
          values.emplace_back(field, value, y, one);
        }
        values.emplace_back(field, field->sub(zero, block.y()), one, zero);
      }

      for (const auto &el : values) {
        indexes.push_back(el.to_int());
      }
    }

    std::vector<DualBlockId> values;
    std::vector<long> indexes;
    BlockId id_;
};

/// Дуальный блок состоит из блоков
export class PGDualBlock {
  public:
    PGDualBlock() = default;
    PGDualBlock(const PGDualBlock &other) {
      values = other.values;
      indexes = other.indexes;
      id_ = other.id_;
    }

    explicit PGDualBlock(const DualBlockId &id) {
      id_ = id;
      internalConstructor();
    }

    PGDualBlock(long i, Fpld *field) {
      id_ = DualBlockId(i, field);
      internalConstructor();
    }

    [[nodiscard]] long getIntId() const { return id_.to_int(); }
    [[nodiscard]] DualBlockId getId() const { return id_; }

    long operator[](long i) { return indexes[i]; }
    BlockId operator()(long i) { return values[i]; }

    [[nodiscard]] std::string to_string_int() const {
      std::stringstream ss;
      ss << "[";
      for (auto i : indexes) {
        ss << i << ", ";
      }
      ss << "\b\b]";
      return ss.str();
    }

    [[nodiscard]] std::string to_string() const {
      std::stringstream ss;
      ss << "[";
      for (const auto &i : values) {
        ss << i.to_string() << ", ";
      }
      ss << "\b\b]";
      return ss.str();
    }

    long size() { return static_cast<long>(values.size()); }

    ~PGDualBlock() = default;

  private:
    void internalConstructor() {
      DualBlockId block{id_.getField()};
      auto one = NTL::ZZ_pEX(1);
      auto zero = NTL::ZZ_pEX(0);

      block.setX(one);
      auto field = id_.getField();
      if (id_ == block) {
        for (int i = 0; i < field->size(); i++) {
          values.emplace_back(field, zero, one, field->int2Fpld(i));
        }
        values.emplace_back(field, zero, zero, one);
      }

      block.setX(id_.x());
      block.setY(one);
      if (id_ == block) {
        auto subc = field->sub(zero, block.x());
        for (int i = 0; i < field->size(); i++) {
          auto gh = BlockId(field, one, subc, field->int2Fpld(i));
          values.push_back(gh);
        }
        values.emplace_back(field, zero, zero, one);
      }

      block.setZ(one);
      block.setY(id_.y());
      if (id_ == block) {
        for (int i = 0; i < field->size(); i++) {
          auto y = field->int2Fpld(i);
          auto value = field->sub(
            zero,
            field->add(block.x(), field->mul(block.y(), y)));
          values.emplace_back(field, one, y, value);
        }
        values.emplace_back(field, zero, one, field->sub(zero, block.y()));
      }

      for (const auto &el : values) {
        indexes.push_back(el.to_int());
      }
    }
    std::vector<BlockId> values;
    std::vector<long> indexes;
    DualBlockId id_;
};

struct block_cache_page {
  PGBlock value{}; /// Значение
  bool isPublished = false; /// Записано ли значение в кэш
};

struct dual_block_cache_page {
  PGDualBlock value{}; /// Значение
  bool isPublished = false; /// Записано ли значение в кэш
};

export class PGpl2 {
  public:
    explicit PGpl2(Fpld f,
                   bool isCached = false,
                   NTL::ZZ_pEX general = NTL::ZZ_pEX(0))
      : field(std::move(f))
        , isCached(isCached)
        , gen(std::move(general)) {
      field.setGen(gen);
      setPgParams();
      if (isCached) {
        block_cache.reserve(v);
        dual_block_cache.reserve(v);
      }
    }
    explicit PGpl2(long p,
                   long l,
                   bool isCached = false,
                   NTL::ZZ_pEX general = NTL::ZZ_pEX(0))
      : isCached(isCached)
        , gen(std::move(general)) {
      field = Fpld(p, l, 2);
      field.setGen(gen);
      setPgParams();
      if (isCached) {
        block_cache.reserve(v);
        dual_block_cache.reserve(v);
      }
    }

    PGBlock operator[](const BlockId &id) {
      return this->operator[](id.to_int());
    }

    PGBlock operator[](long i) {
      if (isCached) {
        if (block_cache[i % block_cache.size()].isPublished) {
          return block_cache[i % block_cache.size()].value;
        }
      }

      PGBlock result(i, &field);

      if (isCached) {
        block_cache[i % block_cache.size()].value = result;
        block_cache[i % block_cache.size()].isPublished = true;
      }
      return result;
    }

    PGDualBlock operator()(const DualBlockId &id) {
      return this->operator()(id.to_int());
    }

    PGDualBlock operator()(long i) {
      if (isCached) {
        if (dual_block_cache[i % dual_block_cache.size()].isPublished) {
          return dual_block_cache[i % dual_block_cache.size()].value;
        }
      }

      PGDualBlock result(i, &field);

      if (isCached) {
        dual_block_cache[i % dual_block_cache.size()].value = result;
        dual_block_cache[i % dual_block_cache.size()].isPublished = true;
      }
      return result;
    }

    long size() { return v; }
    ~PGpl2() = default;

  private:
    void setPgParams() {
      long n = field.size();
      v = n * n + n + 1;
      r = n + 1;
      k = n + 1;
      lambda = 1;
    }
    long v, r, k, lambda;
    NTL::ZZ_pEX gen; /// Образующий
    Fpld field; /// Поле
    bool isCached = false; /// Кэшировать значения
    std::vector<block_cache_page> block_cache; /// Кэш
    std::vector<dual_block_cache_page> dual_block_cache; /// Кэш
};
} // namespace pgpl2
