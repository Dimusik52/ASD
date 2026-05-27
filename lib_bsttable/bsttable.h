// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2
#ifndef LIB_BSTREETABLE_BSTREETABLE_H_
#define LIB_BSTREETABLE_BSTREETABLE_H_

#include <iostream>

#include "../lib_binarytree/binarytree.h"
#include "../lib_itable/itable.h"

template <class TKey, class TValue>
class BSTreeTable : public ITable<TKey, TValue> {
 private:
  BSTree<TKey, TValue> _tree;

 public:
  BSTreeTable() = default;
  BSTreeTable(const BSTreeTable& other) = default;
  BSTreeTable& operator=(const BSTreeTable& other) = default;
  ~BSTreeTable() = default;

  void insert(const TKey& key, const TValue& value) override {
    _tree.insert(key, value);
  }

  void erase(const TKey& key) override { _tree.erase(key); }

  TValue* find(const TKey& key) noexcept override { return _tree.find(key); }

  bool isEmpty() const noexcept override { return _tree.isEmpty(); }

  bool contains(const TKey& key) const noexcept override {
    return _tree.find(key) != nullptr;
  }

  size_t size() const noexcept { return _tree.size(); }

  void print(std::ostream& out) const override { _tree.print(out); }

  void printSorted(std::ostream& out = std::cout) const {
    _tree.printSorted(out);
  }

  std::string toStringSorted() const { return _tree.toStringSorted(); }

  void clear() noexcept { _tree.clear(); }
};

#endif  // LIB_BSTREETABLE_BSTREETABLE_H_