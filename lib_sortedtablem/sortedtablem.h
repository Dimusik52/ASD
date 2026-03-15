// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2
#ifndef LIB_UNSORTEDTABLEM_SORTEDTABLEM_H_
#define LIB_UNSORTEDTABLEM_SORTEDTABLEM_H_

#include <vector>
#include "../lib_itable/itable.h"

template <class TKey, class TValue>
class SortedTableM : public ITable<TKey, TValue> {
 private:
  std::vector<std::pair<TKey, TValue>> _rows;

  int binarySearch(const TKey& key) const;
  bool tryGetPos(const TKey& key, int& pos) const;

 public:
  SortedTableM() = default;

  void insert(const TKey& key, const TValue& value) override;
  void erase(const TKey& key) override;
  TValue* find(const TKey& key) noexcept override;
  bool isEmpty() const noexcept override { return _rows.empty(); }
  void print(std::ostream& out) const override;
  bool contains(const TKey& key) const noexcept override;
};

template <class TKey, class TValue>
int SortedTableM<TKey, TValue>::binarySearch(const TKey& key) const {
  int left = 0;
  int right = static_cast<int>(_rows.size()) - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (_rows[mid].first == key) return mid;
    if (_rows[mid].first < key)
      left = mid + 1;
    else
      right = mid - 1;
  }
  return -(left + 1);
}

template <class TKey, class TValue>
bool SortedTableM<TKey, TValue>::tryGetPos(const TKey& key, int& pos) const {
  pos = binarySearch(key);
  return pos >= 0;
}

template <class TKey, class TValue>
void SortedTableM<TKey, TValue>::insert(const TKey& key, const TValue& value) {
  int pos;
  if (tryGetPos(key, pos)) {
    _rows[pos].second = value;
    return;
  }
  _rows.insert(_rows.begin() + (-(pos + 1)), {key, value});
}

template <class TKey, class TValue>
void SortedTableM<TKey, TValue>::erase(const TKey& key) {
  int pos;
  if (tryGetPos(key, pos)) {
    _rows.erase(_rows.begin() + pos);
  }
}

template <class TKey, class TValue>
TValue* SortedTableM<TKey, TValue>::find(const TKey& key) noexcept {
  int pos;
  if (tryGetPos(key, pos)) {
    return &_rows[pos].second;
  }
  return nullptr;
}

template <class TKey, class TValue>
void SortedTableM<TKey, TValue>::print(std::ostream& out) const {
  out << "SortedTableM (" << _rows.size() << " rows):\n";
  for (size_t i = 0; i < _rows.size(); ++i) {
    out << "  " << _rows[i].first << " -> " << _rows[i].second << "\n";
  }
}

template <class TKey, class TValue>
bool SortedTableM<TKey, TValue>::contains(const TKey& key) const noexcept {
  return binarySearch(key) >= 0;
}

#endif LIB_UNSORTEDTABLEM_SORTEDTABLEM_H_