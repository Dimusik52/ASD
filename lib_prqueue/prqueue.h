// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2

#ifndef LIB_PRQUEUE_PRQUEUE_H_
#define LIB_PRQUEUE_PRQUEUE_H_

#include <utility>
#include "../lib_heap/heap.h"

template <class TKey, class TValue>
class PriorityQueue {
  Heap<TKey, TValue> _heap;

 public:
  PriorityQueue() = default;
  ~PriorityQueue() = default;

  void enqueue(const TKey& key, const TValue& value) {
    _heap.insert(key, value);
  };
  std::pair<TKey, TValue> dequeue() { return _heap.extract(); }
  std::pair<TKey, TValue> peek();

  bool empty() const { return _heap.empty(); }

  void print() const { return _heap.print(); }

  size_t size() const { return _heap.size(); }
};

template <class TKey, class TValue>
std::pair<TKey, TValue> PriorityQueue<TKey, TValue>::peek() {
  if (empty()) {
    throw std::logic_error("Priority Queue is empty!");
  }
  return _heap.top();
};
#endif  // LIB_PRQUEUE_PRQUEUE_H_