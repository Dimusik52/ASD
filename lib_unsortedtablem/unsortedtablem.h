// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2
#ifndef LIB_UNSORTEDTABLEM_UNSORTEDTABLEM_H_
#define LIB_UNSORTEDTABLEM_UNSORTEDTABLEM_H_

#include "../lib_itable/itable.h"
#include "../lib_TVector/include/TVector.h"

template <class TKey, class TValue>
class UnsortedTableM : public ITable<TKey, TValue> {
 private:
  TVector<std::pair<TKey, TValue>> _rows;

 public:
  UnsortedTableM() = default;

  void insert(const TKey& key, const TValue& value) override {
    for (size_t i = 0; i < _rows.size(); i++) {
      if (_rows[i].first == key) {
        _rows[i].second = value;
        return;
      }
    }

    _rows.push_back({key, value});
  }

  void erase(const TKey& key) override {
    for (size_t i = 0; i < _rows.size(); i++) {
      if (_rows[i].first == key) {
        _rows.erase(i);
        return;
      }
    }
  }

  TValue* find(const TKey& key) noexcept override {
    for (size_t i = 0; i < _rows.size(); i++) {
      if (_rows[i].first == key) {
        return &_rows[i].second;
      }
    }
    return nullptr;
  }

  bool isEmpty() const noexcept override { return _rows.is_empty(); }

  bool contains(const TKey& key) const noexcept override {
    for (size_t i = 0; i < _rows.size(); i++) {
      if (_rows[i].first == key) {
        return true;
      }
    }
    return false;
  }

  void print(std::ostream& out) const override {
    out << "UnsortedTableM (" << _rows.size() << " rows):\n";
    for (size_t i = 0; i < _rows.size(); i++) {
      out << "  " << _rows[i].first << " -> " << _rows[i].second << "\n";
    }
  }
};

#endif  // LIB_UNSORTEDTABLEM_UNSORTEDTABLEM_H_