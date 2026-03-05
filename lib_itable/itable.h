// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2
#ifndef LIB_ITABLE_ITABLE_H_
#define LIB_ITABLE_ITABLE_H_

#include <optional>

template <class TKey, class TValue>
class ITable {
 public:
  virtual ~ITable() = default;

  virtual void insert(const TKey&, const TValue&) = 0;
  virtual void erase(const TKey&) = 0;
  virtual TValue* find(const TKey&) noexcept = 0;
  virtual bool isEmpty() const noexcept = 0;

  virtual void print(std::ostream& out) const = 0;

  virtual bool contains(const TKey&) const noexcept = 0;

  friend std::ostream& operator<<(std::ostream& out, const ITable& table) {
    table.print(out);
    return out;
  }
};

#endif  // LIB_ITABLE_ITABLE_H_