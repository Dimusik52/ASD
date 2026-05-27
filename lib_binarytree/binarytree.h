// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2
#ifndef LIB_BINARYTREE_BINARYTREE_H_
#define LIB_BINARYTREE_BINARYTREE_H_

#include <iostream>
#include <stdexcept>
#include <utility>

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
  size_t _size;

  Node* findParent(const TKey& key) const noexcept;
  void deleteTree(Node* node) noexcept;
  void copyTree(Node*& dest, Node* src) noexcept;
  Node* findMin(Node* node) const noexcept;
  Node* eraseRecursive(Node* node, const TKey& key, bool& deleted) noexcept;
  void printSimple(Node* node, int level,
                   std::ostream& out) const noexcept;
  void printSortedRecursive(Node* node, std::ostream& out) const noexcept;

 public:
  BSTree() : _root(nullptr), _size(0){};
  BSTree(const BSTree& other);
  BSTree& operator=(const BSTree& other);
  ~BSTree() noexcept;

  bool isEmpty() const { return _root == nullptr; }
  size_t size() const noexcept { return _size; }
  TValue* find(const TKey& key) const noexcept;
  void insert(const TKey& key, const TValue& value);
  bool erase(const TKey& key) noexcept;
  void clear() noexcept;

  void print(std::ostream& out = std::cout) const noexcept;
  void printSorted(std::ostream& out = std::cout) const noexcept;
  std::string toStringSorted() const noexcept;
};

template <class TKey, class TValue>
BSTree<TKey, TValue>::BSTree(const BSTree& other) : _root(nullptr), _size(0) {
  copyTree(_root, other._root);
}

template <class TKey, class TValue>
BSTree<TKey, TValue>& BSTree<TKey, TValue>::operator=(const BSTree& other) {
  if (this != &other) {
    deleteTree(_root);
    _root = nullptr;
    _size = 0;
    copyTree(_root, other._root);
  }
  return *this;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::copyTree(Node*& dest, Node* src) noexcept {
  if (src == nullptr) {
    dest = nullptr;
    return;
  }
  dest = new Node(src->data.first, src->data.second);
  copyTree(dest->left, src->left);
  copyTree(dest->right, src->right);
  _size++;
}

template <class TKey, class TValue>
typename BSTree<TKey, TValue>::Node* BSTree<TKey, TValue>::findParent(
    const TKey& key) const noexcept {
  if (isEmpty() || _root->data.first == key) return nullptr;

  Node* cur = _root;
  while (cur) {
    if (key < cur->data.first) {
      if (!cur->left) return nullptr;
      if (cur->left->data.first == key) return cur;
      cur = cur->left;
    } else if (key > cur->data.first) {
      if (!cur->right) return nullptr;
      if (cur->right->data.first == key) return cur;
      cur = cur->right;
    } else {
      return nullptr;
    }
  }
  return nullptr;
}

template <class TKey, class TValue>
TValue* BSTree<TKey, TValue>::find(const TKey& key) const noexcept {
  if (isEmpty()) return nullptr;

  if (_root->data.first == key) return &_root->data.second;

  Node* parent = findParent(key);
  if (!parent) return nullptr;

  if (parent->left && parent->left->data.first == key)
    return &parent->left->data.second;
  if (parent->right && parent->right->data.first == key)
    return &parent->right->data.second;

  return nullptr;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
  if (isEmpty()) {
    _root = new Node(key, value);
    _size++;
    return;
  }

  Node* cur = _root;
  while (cur) {
    if (key < cur->data.first) {
      if (!cur->left) {
        cur->left = new Node(key, value);
        _size++;
        return;
      }
      cur = cur->left;
    } else if (key > cur->data.first) {
      if (!cur->right) {
        cur->right = new Node(key, value);
        _size++;
        return;
      }
      cur = cur->right;
    } else {
      // Ключ существует - обновляем значение
      cur->data.second = value;
      return;
    }
  }
}

template <class TKey, class TValue>
typename BSTree<TKey, TValue>::Node* BSTree<TKey, TValue>::findMin(
    Node* node) const noexcept {
  while (node && node->left) node = node->left;
  return node;
}

template <class TKey, class TValue>
typename BSTree<TKey, TValue>::Node* BSTree<TKey, TValue>::eraseRecursive(
    Node* node, const TKey& key, bool& deleted) noexcept {
  if (!node) {
    deleted = false;
    return nullptr;
  }

  if (key < node->data.first) {
    node->left = eraseRecursive(node->left, key, deleted);
  } else if (key > node->data.first) {
    node->right = eraseRecursive(node->right, key, deleted);
  } else {
    deleted = true;

    if (!node->left) {
      Node* rightChild = node->right;
      delete node;
      return rightChild;
    }

    if (!node->right) {
      Node* leftChild = node->left;
      delete node;
      return leftChild;
    }

    Node* successor = findMin(node->right);
    node->data = successor->data;
    node->right = eraseRecursive(node->right, successor->data.first, deleted);
  }
  return node;
}

template <class TKey, class TValue>
bool BSTree<TKey, TValue>::erase(const TKey& key) noexcept {
  bool deleted = false;
  _root = eraseRecursive(_root, key, deleted);
  if (deleted) _size--;
  return deleted;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::clear() noexcept {
  deleteTree(_root);
  _root = nullptr;
  _size = 0;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::deleteTree(Node* node) noexcept {
  if (!node) return;
  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
}

template <class TKey, class TValue>
BSTree<TKey, TValue>::~BSTree() noexcept {
  deleteTree(_root);
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::print(std::ostream& out) const noexcept {
  if (isEmpty()) {
    out << "Tree is empty!" << std::endl;
    return;
  }
  printSimple(_root, 0, out);
}

template <typename TKey, typename TValue>
void BSTree<TKey, TValue>::printSimple(Node* node, int level,
                                       std::ostream& out) const noexcept {
  if (node == nullptr) return;

  printSimple(node->right, level + 1, out);

  for (int i = 0; i < level; i++) {
    out << "  ";
  }
  out << node->data.first << ":" << node->data.second << std::endl;

  printSimple(node->left, level + 1, out);
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::printSortedRecursive(
    Node* node, std::ostream& out) const noexcept {
  if (node == nullptr) return;

  printSortedRecursive(node->left, out);
  out << node->data.first << ":" << node->data.second << " ";
  printSortedRecursive(node->right, out);
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::printSorted(std::ostream& out) const noexcept {
  if (isEmpty()) {
    out << "Tree is empty!" << std::endl;
    return;
  }
  printSortedRecursive(_root, out);
  out << std::endl;
}

template <class TKey, class TValue>
std::string BSTree<TKey, TValue>::toStringSorted() const noexcept {
  std::stringstream ss;
  printSorted(ss);
  return ss.str();
}

#endif  // LIB_BINARYTREE_BINARYTREE_H_