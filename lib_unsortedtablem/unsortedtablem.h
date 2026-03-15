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

  void insert(const TKey& key, const TValue& value) override;

  void erase(const TKey& key) override;

  TValue* find(const TKey& key) noexcept override;

  bool isEmpty() const noexcept override { return _rows.is_empty(); }

  bool contains(const TKey& key) const noexcept override;

  void print(std::ostream& out) const override;

  private:
  int findPos(const TKey& key) const noexcept;
};

template <class TKey, class TValue>
void UnsortedTableM<TKey, TValue>::insert(const TKey& key,
                                          const TValue& value) {
  int pos = findPos(key);
  if (pos != -1) {
    _rows[pos].second = value;
    return;
  }

  _rows.push_back({key, value});
}

template <class TKey, class TValue>
void UnsortedTableM<TKey, TValue>::erase(const TKey& key) {
  int pos = findPos(key);
  if (pos != -1) {
    _rows.erase(pos);
    return;
  }
}

template <class TKey, class TValue>
TValue* UnsortedTableM<TKey, TValue>::find(const TKey& key) noexcept {
  int pos = findPos(key);
  if (pos != -1) {
    return &_rows[pos].second;
  }
  return nullptr;
}

template <class TKey, class TValue>
bool UnsortedTableM<TKey, TValue>::contains(const TKey& key) const noexcept {
  int pos = findPos(key);
  if (pos != -1) {
    return true;
  }
  return false;
}

template <class TKey, class TValue>
void UnsortedTableM<TKey, TValue>::print(std::ostream& out) const {
  out << "UnsortedTableM (" << _rows.size() << " rows):\n";
  for (size_t i = 0; i < _rows.size(); i++) {
    out << "  " << _rows[i].first << " -> " << _rows[i].second << "\n";
  }
}

template <class TKey, class TValue>
int UnsortedTableM<TKey, TValue>::findPos(const TKey& key) const noexcept {
  for (size_t i = 0; i < _rows.size(); i++) {
    if (_rows[i].first == key) {
      return i;
    }
  }
  return -1;
}

#endif  // LIB_UNSORTEDTABLEM_UNSORTEDTABLEM_H_