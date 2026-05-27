// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2
#ifndef LIB_AVLTABLE_AVLTABLE_H_
#define LIB_AVLTABLE_AVLTABLE_H_

#include <iostream>

#include "../lib_avltree/avltree.h"
#include "../lib_itable/itable.h"

template <class TKey, class TValue>
class AVLTable : public ITable<TKey, TValue> {
 private:
  AVLTree<TKey, TValue> _tree;

 public:
  AVLTable() = default;
  AVLTable(const AVLTable& other) = default;
  ~AVLTable() = default;

  void insert(const TKey& key, const TValue& value) override {
    _tree.insert(key, value);
  }

  void erase(const TKey& key) override { _tree.erase(key); }

  TValue* find(const TKey& key) noexcept override { return _tree.find(key); }

  bool isEmpty() const noexcept override { return _tree.isEmpty(); }

  bool contains(const TKey& key) const noexcept override {
    return _tree.contains(key);
  }

  size_t size() const noexcept { return _tree.size(); }

  void print(std::ostream& out) const override { _tree.printTree(out); }

  void printSorted(std::ostream& out = std::cout) const {
    _tree.printSorted(out);
  }

  std::string toStringSorted() const {
    std::stringstream ss;
    printSorted(ss);
    return ss.str();
  }

  void clear() noexcept { _tree.clear(); }
};

#endif  // LIB_AVLTABLE_AVLTABLE_H_