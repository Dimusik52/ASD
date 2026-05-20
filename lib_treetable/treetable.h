// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2
#ifndef LIB_TREETABLE_TREETABLE_H_
#define LIB_TREETABLE_TREETABLE_H_

#include <iostream>
#include <queue>

#include "../lib_itable/itable.h"

template <class TKey, class TValue>
class TreeTable : public ITable<TKey, TValue> {
 private:
  struct Node {
    std::pair<TKey, TValue> data;
    Node *left, *right;

    Node(const TKey& key, const TValue& value)
        : data(key, value), left(nullptr), right(nullptr) {}
  };

  Node* _root;
  size_t _size;

  Node* findNode(const TKey& key) const;
  Node* findNodeParent(const TKey& key, Node*& parent) const;
  Node* getDeepestRightmostNode(Node*& parentOfDeepest) const;
  void deleteTree(Node* node);
  void copyTree(Node*& dest, Node* src);
  void printRecursive(Node* node, std::ostream& out, int level) const;

 public:
  TreeTable();
  TreeTable(const TreeTable& other);
  TreeTable& operator=(const TreeTable& other);
  ~TreeTable();

  void insert(const TKey& key, const TValue& value) override;
  void erase(const TKey& key) override;
  TValue* find(const TKey& key) noexcept override;
  bool isEmpty() const noexcept override { return _root == nullptr; }
  void print(std::ostream& out) const override;
  bool contains(const TKey& key) const noexcept override;
  size_t size() const noexcept { return _size; }
  void clear();
};

template <class TKey, class TValue>
TreeTable<TKey, TValue>::TreeTable() : _root(nullptr), _size(0) {}

template <class TKey, class TValue>
TreeTable<TKey, TValue>::TreeTable(const TreeTable& other)
    : _root(nullptr), _size(0) {
  copyTree(_root, other._root);
}

template <class TKey, class TValue>
TreeTable<TKey, TValue>& TreeTable<TKey, TValue>::operator=(
    const TreeTable& other) {
  if (this != &other) {
    deleteTree(_root);
    _root = nullptr;
    _size = 0;
    copyTree(_root, other._root);
  }
  return *this;
}

template <class TKey, class TValue>
TreeTable<TKey, TValue>::~TreeTable() {
  deleteTree(_root);
}

template <class TKey, class TValue>
void TreeTable<TKey, TValue>::deleteTree(Node* node) {
  if (node == nullptr) return;
  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
}

template <class TKey, class TValue>
void TreeTable<TKey, TValue>::copyTree(Node*& dest, Node* src) {
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
typename TreeTable<TKey, TValue>::Node* TreeTable<TKey, TValue>::findNode(
    const TKey& key) const {
  if (isEmpty()) return nullptr;

  std::queue<Node*> q;
  q.push(_root);

  while (!q.empty()) {
    Node* cur = q.front();
    q.pop();

    if (cur->data.first == key) {
      return cur;
    }

    if (cur->left) q.push(cur->left);
    if (cur->right) q.push(cur->right);
  }
  return nullptr;
}

template <class TKey, class TValue>
TValue* TreeTable<TKey, TValue>::find(const TKey& key) noexcept {
  Node* node = findNode(key);
  if (node != nullptr) {
    return &(node->data.second);
  }
  return nullptr;
}

template <class TKey, class TValue>
bool TreeTable<TKey, TValue>::contains(const TKey& key) const noexcept {
  return findNode(key) != nullptr;
}

template <class TKey, class TValue>
void TreeTable<TKey, TValue>::insert(const TKey& key, const TValue& value) {
  Node* existing = findNode(key);
  if (existing != nullptr) {
    existing->data.second = value;
    return;
  }

  Node* newNode = new Node(key, value);

  if (isEmpty()) {
    _root = newNode;
    _size++;
    return;
  }

  std::queue<Node*> q;
  q.push(_root);

  while (!q.empty()) {
    Node* cur = q.front();
    q.pop();

    if (!cur->left) {
      cur->left = newNode;
      _size++;
      return;
    }
    if (!cur->right) {
      cur->right = newNode;
      _size++;
      return;
    }
    q.push(cur->left);
    q.push(cur->right);
  }
}

template <class TKey, class TValue>
typename TreeTable<TKey, TValue>::Node* TreeTable<TKey, TValue>::findNodeParent(
    const TKey& key, Node*& parent) const {
  if (isEmpty()) return nullptr;

  std::queue<std::pair<Node*, Node*>> q;
  q.push({_root, nullptr});

  while (!q.empty()) {
    std::pair<Node*, Node*> front = q.front();
    Node* cur = front.first;
    Node* par = front.second;
    q.pop();

    if (cur->data.first == key) {
      parent = par;
      return cur;
    }

    if (cur->left) q.push({cur->left, cur});
    if (cur->right) q.push({cur->right, cur});
  }
  return nullptr;
}

template <class TKey, class TValue>
typename TreeTable<TKey, TValue>::Node*
TreeTable<TKey, TValue>::getDeepestRightmostNode(Node*& parentOfDeepest) const {
  if (isEmpty()) return nullptr;

  std::queue<std::pair<Node*, Node*>> q;
  q.push({_root, nullptr});

  Node* deepest = nullptr;
  parentOfDeepest = nullptr;

  while (!q.empty()) {
    std::pair<Node*, Node*> front = q.front();
    Node* cur = front.first;
    Node* par = front.second;
    q.pop();

    deepest = cur;
    parentOfDeepest = par;

    if (cur->left) q.push({cur->left, cur});
    if (cur->right) q.push({cur->right, cur});
  }

  return deepest;
}

template <class TKey, class TValue>
void TreeTable<TKey, TValue>::erase(const TKey& key) {
  if (isEmpty()) return;

  Node* parent = nullptr;
  Node* target = findNodeParent(key, parent);

  if (target == nullptr) return;

  if (target->left == nullptr && target->right == nullptr) {
    if (parent == nullptr) {
      delete target;
      _root = nullptr;
    } else {
      if (parent->left == target)
        parent->left = nullptr;
      else
        parent->right = nullptr;
      delete target;
    }
    _size--;
    return;
  }

  Node* parentOfDeepest = nullptr;
  Node* deepest = getDeepestRightmostNode(parentOfDeepest);

  if (deepest == target) {
    if (parent == nullptr) {
      if (target->left) {
        Node* temp = target->left;
        delete target;
        _root = temp;
      }
    }
    return;
  }

  target->data = deepest->data;

  if (parentOfDeepest) {
    if (parentOfDeepest->left == deepest) {
      parentOfDeepest->left = nullptr;
    } else {
      parentOfDeepest->right = nullptr;
    }
  }
  delete deepest;
  _size--;
}

template <class TKey, class TValue>
void TreeTable<TKey, TValue>::printRecursive(Node* node, std::ostream& out,
                                             int level) const {
  if (node == nullptr) return;

  printRecursive(node->right, out, level + 1);

  for (int i = 0; i < level; i++) {
    out << "    ";
  }
  out << node->data.first << " -> " << node->data.second << std::endl;

  printRecursive(node->left, out, level + 1);
}

template <class TKey, class TValue>
void TreeTable<TKey, TValue>::print(std::ostream& out) const {
  out << "TreeTable (" << _size << "):\n";
  if (isEmpty()) {
    out << "  empty\n";
    return;
  }
  printRecursive(_root, out, 0);
}

template <class TKey, class TValue>
void TreeTable<TKey, TValue>::clear() {
  deleteTree(_root);
  _root = nullptr;
  _size = 0;
}

#endif  // LIB_TREETABLE_TREETABLE_H_