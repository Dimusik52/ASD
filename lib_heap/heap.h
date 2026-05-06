// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2

#ifndef LIB_HEAP_HEAP_H_
#define LIB_HEAP_HEAP_H_

#include <vector>
#include <utility>
#include <iostream>
template <class TKey, class TValue>
class Heap {
  std::vector<std::pair<TKey, TValue>> _data;

  public:
  Heap() = default;
  ~Heap() = default;

  void insert(const TKey& key, const TValue& value) noexcept;
  void ascend() noexcept;
  void descend() noexcept;
  std::pair<TKey, TValue> extract();
  void print() const noexcept;

  std::pair<TKey, TValue>& top() const {
    if (empty()) throw std::logic_error("Heap is empty!");
    return _data[0];
  }
  bool empty() const noexcept { return _data.empty(); }

  size_t size() const { return _data.size(); }
};
template <class TKey, class TValue>
void Heap<TKey, TValue>::insert(const TKey& key, const TValue& value) noexcept {
  _data.push_back({key, value});
  ascend();
}

template <class TKey, class TValue>
void Heap<TKey, TValue>::ascend() noexcept {
  if (_data.empty()) return;
  size_t index = _data.size() - 1;

  while (index > 0) {
    size_t parent = (index - 1) / 2;
    if (_data[parent].first > _data[index].first) {
      std::swap(_data[parent], _data[index]);
      index = parent;
    } else {
      break;
    }
  } 
}

template <class TKey, class TValue>
std::pair<TKey, TValue> Heap<TKey, TValue>::extract() {
  if (_data.empty()) throw std::logic_error("Heap is empty!");

   std::pair<TKey, TValue> root = _data[0];

   _data[0] = _data.back();
   _data.pop_back();

   if (!empty()) {
     descend();
   }

   return root;
}

template <class TKey, class TValue>
void Heap<TKey, TValue>::print() const noexcept {
  if (empty()) throw std::logic_error("Heap is empty!");
  for (size_t i = 0; i < _data.size() - 1; i++) {
    std::cout << _data[i].first << ":" << _data[i].second << " ";
  }
  std::cout << "\n";
}

template <class TKey, class TValue>
void Heap<TKey, TValue>::descend() noexcept {
  if (empty()) return;

  size_t index = 0;
  size_t size = _data.size();

  while (1) {
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;
    size_t smallest = index;
    if (left < size && _data[left].first < _data[smallest].first) {
      smallest = left;
    }
    if (right < size && _data[right].first < _data[smallest].first) {
      smallest = right;
    }

    if (smallest != index) {
      std::swap(_data[index], _data[smallest]);
      index = smallest;
    } else {
      break;
    }
  }
}

#endif  // LIB_HEAP_HEAP_H_