// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2
#ifndef _LIB_TREE_TREE_H_
#define _LIB_TREE_TREE_H_

#include <iostream>
#include <queue>
#include <utility>

template <typename TKey, typename TVal>
class Tree {
  struct Node {
    std::pair<TKey, TVal> data;
    Node *left, *right;

    Node(const TKey& key, const TVal& val)
        : data(key, val), left(nullptr), right(nullptr) {}
  };

  Node* _root;
  size_t _size;

  void print_DCLR_rec_helper(Node* node, std::ostream& out) const;
  void print_DLRC_rec_helper(Node* node, std::ostream& out) const;
  void print_DLCK_rec_helper(Node* node, std::ostream& out) const;
  void delete_tree(Node* node);
  void copyTree(Node*& dest, Node* src);
  Node* find_node(const TKey& key) const noexcept;
  Node* find_node_with_parent(const TKey& key, Node*& parent) const noexcept;
  Node* get_deepest_rightmost_node(Node*& parent) const noexcept;

 public:
  Tree();
  Tree(const Tree& other);
  Tree& operator=(const Tree& other);
  ~Tree();

  void insert(const TKey& key, const TVal& val);
  TVal* find(const TKey& key) noexcept;
  bool erase(const TKey& key) noexcept;
  void clear() noexcept;

  void print_w(std::ostream& out = std::cout) const noexcept;
  void print_DLCK(std::ostream& out = std::cout) const noexcept;
  void print_DLRC(std::ostream& out = std::cout) const noexcept;
  void print_DCLR_rec(std::ostream& out = std::cout) const noexcept;

  bool is_empty() const { return _root == nullptr; }
  size_t size() const noexcept { return _size; }
  bool contains(const TKey& key) const noexcept {
    return find_node(key) != nullptr;
  }
};

template <typename TKey, typename TVal>
Tree<TKey, TVal>::Tree() : _root(nullptr), _size(0) {}

template <typename TKey, typename TVal>
Tree<TKey, TVal>::Tree(const Tree& other) : _root(nullptr), _size(0) {
  copyTree(_root, other._root);
}

template <typename TKey, typename TVal>
Tree<TKey, TVal>& Tree<TKey, TVal>::operator=(const Tree& other) {
  if (this != &other) {
    delete_tree(_root);
    _root = nullptr;
    _size = 0;
    copyTree(_root, other._root);
  }
  return *this;
}

template <typename TKey, typename TVal>
void Tree<TKey, TVal>::copyTree(Node*& dest, Node* src) {
  if (src == nullptr) {
    dest = nullptr;
    return;
  }
  dest = new Node(src->data.first, src->data.second);
  copyTree(dest->left, src->left);
  copyTree(dest->right, src->right);
  _size++;
}

template <typename TKey, typename TVal>
Tree<TKey, TVal>::~Tree() {
  delete_tree(_root);
}

template <typename TKey, typename TVal>
void Tree<TKey, TVal>::delete_tree(Node* node) {
  if (node == nullptr) return;
  delete_tree(node->left);
  delete_tree(node->right);
  delete node;
}

template <typename TKey, typename TVal>
void Tree<TKey, TVal>::print_w(std::ostream& out) const noexcept {
  /*
          1(A)
        /     \
        2(B)   3(C)       A B C D E F
       /   \      \
      4(D)  5(E)   6(F)

  */
  if (is_empty()) return;

  std::queue<Node*> q;
  q.push(_root);

  while (!q.empty()) {
    Node* cur = q.front();
    q.pop();

    out << cur->data.second << " ";

    if (cur->left) q.push(cur->left);
    if (cur->right) q.push(cur->right);
  }
  out << std::endl;
}

template <typename TKey, typename TVal>
void Tree<TKey, TVal>::print_DCLR_rec_helper(Node* node,
                                             std::ostream& out) const {
  if (node == nullptr) return;

  out << node->data.second << " ";
  print_DCLR_rec_helper(node->left, out);
  print_DCLR_rec_helper(node->right, out);
}

template <typename TKey, typename TVal>
void Tree<TKey, TVal>::print_DCLR_rec(std::ostream& out) const noexcept {
  /*
        1(A)
      /     \
      2(B)   3(C)       A B D E C F
     /   \      \
    4(D)  5(E)   6(F)

*/
  print_DCLR_rec_helper(_root, out);
  out << std::endl;
}

template <typename TKey, typename TVal>
void Tree<TKey, TVal>::print_DLRC_rec_helper(Node* node,
                                             std::ostream& out) const {
  if (node == nullptr) return;

  print_DLRC_rec_helper(node->left, out);
  print_DLRC_rec_helper(node->right, out);
  out << node->data.second << " ";
}

template <typename TKey, typename TVal>
void Tree<TKey, TVal>::print_DLRC(std::ostream& out) const noexcept {
  /*
        1(A)
      /     \
      2(B)   3(C)       D E B F C A
     /   \      \
    4(D)  5(E)   6(F)

*/
  print_DLRC_rec_helper(_root, out);
  out << std::endl;
}

template <typename TKey, typename TVal>
void Tree<TKey, TVal>::print_DLCK_rec_helper(Node* node,
                                             std::ostream& out) const {
  if (node == nullptr) return;

  print_DLCK_rec_helper(node->left, out);
  out << node->data.second << " ";
  print_DLCK_rec_helper(node->right, out);
}

template <typename TKey, typename TVal>
void Tree<TKey, TVal>::print_DLCK(std::ostream& out) const noexcept {
  /*
        1(A)
      /     \
      2(B)   3(C)       D B E A C F
     /   \      \
    4(D)  5(E)   6(F)

*/
  print_DLCK_rec_helper(_root, out);
  out << std::endl;
}

template <typename TKey, typename TVal>
typename Tree<TKey, TVal>::Node* Tree<TKey, TVal>::find_node(
    const TKey& key) const noexcept {
  if (is_empty()) return nullptr;

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

template <typename TKey, typename TVal>
typename Tree<TKey, TVal>::Node* Tree<TKey, TVal>::find_node_with_parent(
    const TKey& key, Node*& parent) const noexcept {
  if (is_empty()) return nullptr;

  std::queue<std::pair<Node*, Node*>> q;
  q.push({_root, nullptr});

  while (!q.empty()) {
    auto [cur, par] = q.front();
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

template <typename TKey, typename TVal>
typename Tree<TKey, TVal>::Node* Tree<TKey, TVal>::get_deepest_rightmost_node(
    Node*& parent) const noexcept {
  if (is_empty()) return nullptr;

  std::queue<std::pair<Node*, Node*>> q;
  q.push({_root, nullptr});

  Node* deepest = nullptr;
  parent = nullptr;

  while (!q.empty()) {
    auto [cur, par] = q.front();
    q.pop();

    deepest = cur;
    parent = par;

    if (cur->left) q.push({cur->left, cur});
    if (cur->right) q.push({cur->right, cur});
  }

  return deepest;
}

template <typename TKey, typename TVal>
void Tree<TKey, TVal>::insert(const TKey& key, const TVal& val) {
  Node* existing = find_node(key);
  if (existing != nullptr) {
    existing->data.second = val;
    return;
  }

  Node* node = new Node(key, val);

  if (is_empty()) {
    _root = node;
    _size++;
    return;
  }

  std::queue<Node*> q;
  q.push(_root);

  while (!q.empty()) {
    Node* cur = q.front();
    q.pop();

    if (!cur->left) {
      cur->left = node;
      _size++;
      return;
    }
    if (!cur->right) {
      cur->right = node;
      _size++;
      return;
    }
    q.push(cur->left);
    q.push(cur->right);
  }
}

template <typename TKey, typename TVal>
TVal* Tree<TKey, TVal>::find(const TKey& key) noexcept {
  Node* node = find_node(key);
  if (node != nullptr) {
    return &(node->data.second);
  }
  return nullptr;
}

template <typename TKey, typename TVal>
bool Tree<TKey, TVal>::erase(const TKey& key) noexcept {
  if (is_empty()) return false;

  Node* parent = nullptr;
  Node* target = find_node_with_parent(key, parent);

  if (target == nullptr) return false;

  // Случай 1: удаляемый узел - лист
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
    return true;
  }

  // Случай 2: узел имеет хотя бы одного ребенка
  Node* parent_of_deepest = nullptr;
  Node* deepest = get_deepest_rightmost_node(parent_of_deepest);

  // Если deepest - это сам target, просто удаляем его и поднимаем ребенка
  if (deepest == target) {
    Node* child = target->left ? target->left : target->right;
    if (parent == nullptr) {
      delete target;
      _root = child;
    } else {
      if (parent->left == target)
        parent->left = child;
      else
        parent->right = child;
      delete target;
    }
    _size--;
    return true;
  }

  // Копируем данные из deepest в target
  target->data = deepest->data;

  // Удаляем deepest узел
  if (parent_of_deepest) {
    if (parent_of_deepest->left == deepest)
      parent_of_deepest->left = nullptr;
    else
      parent_of_deepest->right = nullptr;
  }
  delete deepest;
  _size--;
  return true;
}

template <typename TKey, typename TVal>
void Tree<TKey, TVal>::clear() noexcept {
  delete_tree(_root);
  _root = nullptr;
  _size = 0;
}

#endif  // _LIB_TREE_TREE_H_