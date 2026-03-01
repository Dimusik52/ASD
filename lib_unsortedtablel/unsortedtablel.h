// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2
#ifndef LIB_UNSORTEDTABLEL_UNSORTEDTABLEL_H_
#define LIB_UNSORTEDTABLEL_UNSORTEDTABLEL_H_

#include "../lib_TVector/include/TVector.h"
#include "../lib_itable/itable.h"
#include "../lib_list/list.h"

template <class TKey, class TValue>
class UnsortedTableL : public ITable<TKey, TValue> {
 private:
  List<std::pair<TKey, TValue>> _list;

 public:
  UnsortedTableL() = default;

  void insert(const TKey& key, const TValue& value) override {
    for (size_t i = 0; i < _list.size(); i++) {
      if (_list[i].first == key) {
        _list[i].second = value;
        return;
      }
    }
    _list.push_back({key, value});
  }

  void erase(const TKey& key) override {
    for (size_t i = 0; i < _list.size(); i++) {
      if (_list[i].first == key) {
        _list.erase(i);
        return;
      }
    }
  }

  TValue* find(const TKey& key) noexcept override {
    for (size_t i = 0; i < _list.size(); i++) {
      if (_list[i].first == key) {
        return &_list[i].;
      }
    }
    return nullptr;
  }

  bool isEmpty() const noexcept override { return _list.empty(); }

  void print(std::ostream& out) const override {
    out << "UnsortedTableL (" << _list.size() << " rows):\n";
    for (size_t i = 0; i < _list.size(); ++i) {
      out << "  " << _list[i].first << " -> " << _list[i].second << "\n";
    }
  }
};

#endif  // LIB_UNSORTEDTABLEL_UNSORTEDTABLEL_H_