// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2
#ifndef LIB_BINARYTREE_BINARYTREE_H_
#define LIB_BINARYTREE_BINARYTREE_H_

#include <utility>
#include <iostream>
#include <stdexcept>

template <class TKey, class TValue>
class BSTree {
 private:
  struct Node {
    std::pair<TKey, TValue> data;
    Node* left;
    Node* right;

    Node(TKey key, TValue value)
        : data({key, value}), left(nullptr), right(nullptr){};
  };

  Node* _root;
  Node* findParent(const TKey& key) const noexcept;

 public:
  BSTree() : _root(nullptr){};
  ~BSTree() = default;
  bool isEmpty() const { return _root == nullptr; }

  TValue* find(const TKey& key) const noexcept;

  void insert(const TKey& key, const TValue& value);

  void print() const noexcept;
  void printSimple(Node* node, int level) const noexcept;
};

template <class TKey, class TValue>
typename BSTree<TKey,TValue>::Node* BSTree<TKey,TValue>::findParent(const TKey& key) const noexcept {
  if (isEmpty()) return nullptr;
  if (_root->data.first == key) return _root;

  Node* cur = _root;
  while (1) {
    if (cur->data.first > key) {
      if (!cur->left) return cur;  // parent insert
      if (cur->left->data.first == key)
        return cur;  // parent found
      else
        cur = cur->left;  // continue
    } else {
      if (!cur->right) return cur;  // parent insert
      if (cur->right->data.first == key)
        return cur;  // parent found
      else
        cur = cur->right;  // continue
    }
  }
}

template <class TKey, class TValue>
TValue* BSTree<TKey, TValue>::find(const TKey& key) const noexcept {
  Node* parent = findParent(key);
  if (!parent) return nullptr;
  if (parent->left && parent->left->data.first == key)
    return &parent->left->data.second;
  else if (parent->right && parent->right->data.first == key)
    return &parent->right->data.second;
  else if (parent == _root)
    return &_root->data.second;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
  Node* parent = findParent(key);
  if (!parent) {
    _root = new Node(key, value);
    return;
  }
  if (parent->data.first < key && !parent->right) {
    parent->right = new Node(key, value);
    return;
  }
  if (parent->data.first > key && !parent->left) {
    parent->left = new Node(key, value);
    return;
  }

  throw std::logic_error("The key is in tree!");
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::print() const noexcept {
  if (isEmpty()) {
    std::cout << "Tree is empty!" << std::endl;
    return;
  }

  printSimple(_root, 0);
}

template <typename TKey, typename TValue>
void BSTree<TKey, TValue>::printSimple(Node* node, int level) const noexcept {
  if (node == nullptr) return;

  printSimple(node->right, level + 1);

  for (int i = 0; i < level; i++) {
    std::cout << "  ";
  }

  std::cout << node->data.first << std::endl;

  printSimple(node->left, level + 1);
}

#endif  // LIB_BINARYTREE_BINARYTREE_H_