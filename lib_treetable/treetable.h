// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2
#ifndef LIB_TREETABLE_TREETABLE_H_
#define LIB_TREETABLE_TREETABLE_H_

#include <iostream>

#include "../lib_itable/itable.h"
#include "../lib_tree/tree.h"

template <class TKey, class TValue>
class TreeTable : public ITable<TKey, TValue> {
 private:
  Tree<TKey, TValue> _tree;

 public:
  TreeTable() = default;
  TreeTable(const TreeTable& other) = default;
  TreeTable& operator=(const TreeTable& other) = default;
  ~TreeTable() = default;

  void insert(const TKey& key, const TValue& value) override {
    _tree.insert(key, value);
  }

  void erase(const TKey& key) override { _tree.erase(key); }

  TValue* find(const TKey& key) noexcept override { return _tree.find(key); }

  bool isEmpty() const noexcept override { return _tree.is_empty(); }

  bool contains(const TKey& key) const noexcept override {
    return _tree.contains(key);
  }

  size_t size() const noexcept { return _tree.size(); }

  void print(std::ostream& out) const override {
    out << "TreeTable (" << size() << "):\n";
    if (isEmpty()) {
      out << "  empty\n";
      return;
    }
    _tree.print_w(out);
  }

  void clear() noexcept { _tree.clear(); }
};

#endif  // LIB_TREETABLE_TREETABLE_H_