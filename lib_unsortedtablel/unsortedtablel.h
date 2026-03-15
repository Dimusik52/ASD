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

  auto findIterator(const TKey& key);
  auto findIterator(const TKey& key) const;

 public:
  UnsortedTableL() = default;

  void insert(const TKey& key, const TValue& value) override;
  void erase(const TKey& key) override;
  TValue* find(const TKey& key) noexcept override;
  bool isEmpty() const noexcept override {
    return _list.begin() == _list.end();
  }
  void print(std::ostream& out) const override;
  bool contains(const TKey& key) const noexcept override;
  size_t size() const;
};

template <class TKey, class TValue>
auto UnsortedTableL<TKey, TValue>::findIterator(const TKey& key) {
  for (auto it = _list.begin(); it != _list.end(); ++it) {
    if (it->first == key) return it;
  }
  return _list.end();
}

template <class TKey, class TValue>
auto UnsortedTableL<TKey, TValue>::findIterator(const TKey& key) const {
  for (auto it = _list.begin(); it != _list.end(); ++it) {
    if (it->first == key) return it;
  }
  return _list.end();
}

template <class TKey, class TValue>
void UnsortedTableL<TKey, TValue>::insert(const TKey& key,
                                          const TValue& value) {
  auto it = findIterator(key);
  if (it != _list.end()) {
    it->second = value;
    return;
  }
  _list.push_back({key, value});
}

template <class TKey, class TValue>
void UnsortedTableL<TKey, TValue>::erase(const TKey& key) {
  auto it = findIterator(key);
  if (it != _list.end()) {
    size_t pos = 0;
    for (auto searchIt = _list.begin(); searchIt != it; ++searchIt, ++pos) {
    }
    _list.erase(pos);
  }
}

template <class TKey, class TValue>
TValue* UnsortedTableL<TKey, TValue>::find(const TKey& key) noexcept {
  auto it = findIterator(key);
  if (it != _list.end()) {
    return &(it->second);
  }
  return nullptr;
}

template <class TKey, class TValue>
void UnsortedTableL<TKey, TValue>::print(std::ostream& out) const {
  out << "UnsortedTableL (" << size() << "):\n";
  for (auto it = _list.begin(); it != _list.end(); ++it) {
    out << "  " << it->first << " -> " << it->second << "\n";
  }
}

template <class TKey, class TValue>
bool UnsortedTableL<TKey, TValue>::contains(const TKey& key) const noexcept {
  auto it = findIterator(key);
  return it != _list.end();
}

template <class TKey, class TValue>
size_t UnsortedTableL<TKey, TValue>::size() const {
  size_t count = 0;
  for (auto it = _list.begin(); it != _list.end(); ++it) {
    ++count;
  }
  return count;
}

#endif  // LIB_UNSORTEDTABLEL_UNSORTEDTABLEL_H_