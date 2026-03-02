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
    for (auto it = _list.begin(); it != _list.end(); it++) {
      if (it->first == key) {
        it->second = value;
        return;
      }
    }
    _list.push_back({key, value});
  }

  void erase(const TKey& key) override {
    size_t pos = 0;
    for (auto it = _list.begin(); it != _list.end(); it++, pos++) {
      if (it->first == key) {
        _list.erase(pos);
        return;
      }
    }
  }

  TValue* find(const TKey& key) noexcept override {
    for (auto it = _list.begin(); it != _list.end(); it++) {
      if (it->first == key) {
        return &(it->second);
      }
    }
    return nullptr;
  }

  bool isEmpty() const noexcept override {
    return const_cast<List<std::pair<TKey, TValue>>&>(_list).is_empty();
  }

  void print(std::ostream& out) const override {
    out << "UnsortedTableL (" << size() <<"):\n";
    auto& mutableList = const_cast<List<std::pair<TKey, TValue>>&>(_list);
    for (auto it = mutableList.begin(); it != mutableList.end(); ++it) {
      out << "  " << it->first << " -> " << it->second << "\n";
    }
  }

  size_t size() const {
    size_t count = 0;
    auto& mutableList = const_cast<List<std::pair<TKey, TValue>>&>(_list);
    for (auto it = mutableList.begin(); it != mutableList.end(); ++it) {
      ++count;
    }
    return count;
  }
};

#endif  // LIB_UNSORTEDTABLEL_UNSORTEDTABLEL_H_