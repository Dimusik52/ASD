// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2
#ifndef _LIB_TREE_AVL_TREE_H_
#define _LIB_TREE_AVL_TREE_H_

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>

template <typename TKey, typename TVal>
class AVLTree {
  struct Node {
    std::pair<TKey, TVal> data;
    Node *left, *right, *parent;
    size_t height;

    Node(const TKey& key, const TVal& val)
        : data(key, val),
          left(nullptr),
          right(nullptr),
          parent(nullptr),
          height(1) {}
  };

  Node* _root;
  size_t _size;

  void deleteTree(Node* node);
  void copyTree(Node*& dest, Node* src);

  int getHeight(Node* node) const noexcept;
  void recalcHeight(Node* node) noexcept;
  int calculateBalance(Node* node) const noexcept;

  void leftRotate(Node* node);
  void rightRotate(Node* node);

  void RR(Node* node);  // Правый-правый случай
  void LL(Node* node);  // Левый-левый случай
  void RL(Node* node);  // Правый-левый случай
  void LR(Node* node);  // Левый-правый случай

  void recoverBalance(Node* node);

  Node* findNode(const TKey& key) const noexcept;
  Node* findMin(Node* node) const noexcept;

  Node* bstErase(Node* node);

  void printTreeHelper(Node* node, int space, int indent,
                       std::ostream& out) const;
  void printSortedHelper(Node* node, std::ostream& out) const;

 public:
  AVLTree();
  AVLTree(const AVLTree& other);
  ~AVLTree();

  void insert(const TKey& key, const TVal& val);
  TVal* find(const TKey& key) noexcept;
  bool erase(const TKey& key) noexcept;
  void clear() noexcept;

  void printTree(std::ostream& out = std::cout) const noexcept;
  void printSorted(std::ostream& out = std::cout) const noexcept;

  bool isEmpty() const { return _root == nullptr; }
  size_t size() const noexcept { return _size; }
  bool contains(const TKey& key) const noexcept {
    return findNode(key) != nullptr;
  }

  // Для тестов
  int getTreeHeight() const { return getHeight(_root); }

  bool isBalanced() const { return isBalancedHelper(_root); }

  bool isBalancedHelper(Node* node) const {
    if (!node) return true;
    int balance = calculateBalance(node);
    if (abs(balance) > 1) return false;
    return isBalancedHelper(node->left) && isBalancedHelper(node->right);
  }
};

template <typename TKey, typename TVal>
AVLTree<TKey, TVal>::AVLTree() : _root(nullptr), _size(0) {}

template <typename TKey, typename TVal>
AVLTree<TKey, TVal>::AVLTree(const AVLTree& other) : _root(nullptr), _size(0) {
  copyTree(_root, other._root);
}

template <typename TKey, typename TVal>
AVLTree<TKey, TVal>::~AVLTree() {
  deleteTree(_root);
}

template <typename TKey, typename TVal>
void AVLTree<TKey, TVal>::deleteTree(Node* node) {
  if (node == nullptr) return;
  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
}

template <typename TKey, typename TVal>
void AVLTree<TKey, TVal>::copyTree(Node*& dest, Node* src) {
  if (src == nullptr) {
    dest = nullptr;
    return;
  }
  dest = new Node(src->data.first, src->data.second);
  dest->height = src->height;
  copyTree(dest->left, src->left);
  copyTree(dest->right, src->right);
  if (dest->left) dest->left->parent = dest;
  if (dest->right) dest->right->parent = dest;
  _size++;
}

template <typename TKey, typename TVal>
int AVLTree<TKey, TVal>::getHeight(Node* node) const noexcept {
  return node ? node->height : 0;
}

template <typename TKey, typename TVal>
void AVLTree<TKey, TVal>::recalcHeight(Node* node) noexcept {
  if (node) {
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
  }
}

template <typename TKey, typename TVal>
int AVLTree<TKey, TVal>::calculateBalance(Node* node) const noexcept {
  return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

/*
Левый поворот (leftRotate):

      G                    P
       \                  / \
        P      -->       G   C
         \
          C
*/
template <typename TKey, typename TVal>
void AVLTree<TKey, TVal>::leftRotate(Node* node) {
  Node* G = node;
  Node* P = G->right;

  G->right = P->left;
  if (P->left) {
    P->left->parent = G;
  }

  P->left = G;
  P->parent = G->parent;
  G->parent = P;

  if (P->parent == nullptr) {
    _root = P;
  } else if (P->parent->left == G) {
    P->parent->left = P;
  } else {
    P->parent->right = P;
  }

  recalcHeight(G);
  recalcHeight(P);
}

/*
Правый поворот (rightRotate):

        G              P
       /              / \
      P      -->     C   G
     /
    C
*/
template <typename TKey, typename TVal>
void AVLTree<TKey, TVal>::rightRotate(Node* node) {
  Node* G = node;
  Node* P = G->left;

  G->left = P->right;
  if (P->right) {
    P->right->parent = G;
  }

  P->right = G;
  P->parent = G->parent;
  G->parent = P;

  if (P->parent == nullptr) {
    _root = P;
  } else if (P->parent->left == G) {
    P->parent->left = P;
  } else {
    P->parent->right = P;
  }

  recalcHeight(G);
  recalcHeight(P);
}

/*
RR случай (правый-правый):
Передаем G (сломал баланс)

    G(-2)               P
     \                 / \
      P      -->      G   C
       \
        C
*/
template <typename TKey, typename TVal>
void AVLTree<TKey, TVal>::RR(Node* node) {
  leftRotate(node);
}

/*
LL случай (левый-левый):
Передаем G (сломал баланс)

    G(+2)               P
   /                   / \
  P         -->       C   G
 /
C
*/
template <typename TKey, typename TVal>
void AVLTree<TKey, TVal>::LL(Node* node) {
  rightRotate(node);
}

/*
RL случай (правый-левый):
Передаем G (сломал баланс)

    G(-2)                G(-2)                 C
     \                    \                  / \
      P        -->          C      -->      G   P
     /                      \
    C                        P
*/
template <typename TKey, typename TVal>
void AVLTree<TKey, TVal>::RL(Node* node) {
  Node* G = node;
  Node* P = G->right;

  rightRotate(P);
  leftRotate(G);
}

/*
LR случай (левый-правый):
Передаем G (сломал баланс)

    G(+2)                G(+2)                 C
   /                    /                    / \
  P        -->         C          -->       P   G
   \                  /
    C                P
*/
template <typename TKey, typename TVal>
void AVLTree<TKey, TVal>::LR(Node* node) {
  Node* G = node;
  Node* P = G->left;

  leftRotate(P);
  rightRotate(G);
}

template <typename TKey, typename TVal>
void AVLTree<TKey, TVal>::recoverBalance(Node* node) {
  int balance = calculateBalance(node);

  if (balance > 1) {
    if (calculateBalance(node->left) >= 0) {
      LL(node);
    } else {
      LR(node);
    }
  } else if (balance < -1) {
    if (calculateBalance(node->right) <= 0) {
      RR(node);
    } else {
      RL(node);
    }
  }
}


template <typename TKey, typename TVal>
typename AVLTree<TKey, TVal>::Node* AVLTree<TKey, TVal>::findNode(
    const TKey& key) const noexcept {
  Node* cur = _root;
  while (cur) {
    if (key == cur->data.first) {
      return cur;
    } else if (key < cur->data.first) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  return nullptr;
}

template <typename TKey, typename TVal>
typename AVLTree<TKey, TVal>::Node* AVLTree<TKey, TVal>::findMin(
    Node* node) const noexcept {
  while (node && node->left) {
    node = node->left;
  }
  return node;
}

template <typename TKey, typename TVal>
void AVLTree<TKey, TVal>::insert(const TKey& key, const TVal& val) {
  Node* existing = findNode(key);
  if (existing) {
    existing->data.second = val;
    return;
  }

  Node* newNode = new Node(key, val);
  _size++;

  if (isEmpty()) {
    _root = newNode;
    return;
  }

  Node* cur = _root;
  Node* parent = nullptr;

  while (cur) {
    parent = cur;
    if (key < cur->data.first) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }

  newNode->parent = parent;
  if (key < parent->data.first) {
    parent->left = newNode;
  } else {
    parent->right = newNode;
  }

  Node* node = newNode;
  while (node) {
    recalcHeight(node);
    if (abs(calculateBalance(node)) > 1) {
      recoverBalance(node);
    }
    node = node->parent;
  }
}

template <typename TKey, typename TVal>
typename AVLTree<TKey, TVal>::Node* AVLTree<TKey, TVal>::bstErase(Node* node) {
  Node* parent = node->parent;

  if (node->left == nullptr && node->right == nullptr) {
    if (parent) {
      if (parent->left == node)
        parent->left = nullptr;
      else
        parent->right = nullptr;
    } else {
      _root = nullptr;
    }
    delete node;
    _size--;
    return parent;
  }

  if (node->left == nullptr || node->right == nullptr) {
    Node* child = node->left ? node->left : node->right;

    if (parent) {
      if (parent->left == node)
        parent->left = child;
      else
        parent->right = child;
    } else {
      _root = child;
    }
    child->parent = parent;
    delete node;
    _size--;
    return parent;
  }

  Node* successor = findMin(node->right);
  node->data = successor->data;
  return bstErase(successor);
}

template <typename TKey, typename TVal>
bool AVLTree<TKey, TVal>::erase(const TKey& key) noexcept {
  Node* node = findNode(key);
  if (!node) return false;

  Node* startFrom = bstErase(node);

  Node* cur = startFrom;
  while (cur) {
    size_t oldHeight = cur->height;
    recalcHeight(cur);

    if (abs(calculateBalance(cur)) > 1) {
      recoverBalance(cur);
    }
    cur = cur->parent;
  }

  return true;
}

template <typename TKey, typename TVal>
void AVLTree<TKey, TVal>::clear() noexcept {
  deleteTree(_root);
  _root = nullptr;
  _size = 0;
}

template <typename TKey, typename TVal>
TVal* AVLTree<TKey, TVal>::find(const TKey& key) noexcept {
  Node* node = findNode(key);
  return node ? &node->data.second : nullptr;
}

template <typename TKey, typename TVal>
void AVLTree<TKey, TVal>::printTreeHelper(Node* node, int space, int indent,
                                          std::ostream& out) const {
  if (node == nullptr) return;

  space += indent;

  printTreeHelper(node->right, space, indent, out);

  out << std::endl;
  for (int i = indent; i < space; i++) {
    out << " ";
  }
  out << node->data.first << ":" << node->data.second << " (h=" << node->height
      << ")" << std::endl;

  printTreeHelper(node->left, space, indent, out);
}

template <typename TKey, typename TVal>
void AVLTree<TKey, TVal>::printTree(std::ostream& out) const noexcept {
  if (isEmpty()) {
    out << "Tree is empty!" << std::endl;
    return;
  }
  printTreeHelper(_root, 0, 4, out);
}

template <typename TKey, typename TVal>
void AVLTree<TKey, TVal>::printSortedHelper(Node* node,
                                            std::ostream& out) const {
  if (node == nullptr) return;

  printSortedHelper(node->left, out);
  out << node->data.first << ":" << node->data.second << " ";
  printSortedHelper(node->right, out);
}

template <typename TKey, typename TVal>
void AVLTree<TKey, TVal>::printSorted(std::ostream& out) const noexcept {
  if (isEmpty()) {
    out << "Tree is empty!" << std::endl;
    return;
  }
  printSortedHelper(_root, out);
  out << std::endl;
}

#endif  // _LIB_TREE_AVL_TREE_H_