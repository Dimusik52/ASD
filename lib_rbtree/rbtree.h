// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2
#ifndef _LIB_TREE_RB_TREE_H_
#define _LIB_TREE_RB_TREE_H_

#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>

template <typename TKey, typename TVal>
class RBTree {
  enum Color { BLACK, RED };

  struct Node {
    std::pair<TKey, TVal> data;
    Node* left;
    Node* right;
    Node* parent;
    Color color;
    int blackHeight;

    Node(const TKey& key, const TVal& val)
        : data(key, val),
          left(nullptr),
          right(nullptr),
          parent(nullptr),
          color(RED),
          blackHeight(1) {}
  };

  Node* _root;
  size_t _size;

  void deleteTree(Node* node);
  void copyTree(Node*& dest, Node* src);

  Color getColor(Node* node) const noexcept {
    return node ? node->color : BLACK;
  }
  void setColor(Node* node, Color color) noexcept {
    if (node) node->color = color;
  }

  int getBlackHeight(Node* node) const noexcept {
    return node ? node->blackHeight : 0;
  }
  void recalcBlackHeight(Node* node) noexcept;

  void leftRotate(Node* node);
  void rightRotate(Node* node);

  void recolor(Node* node);

  Node* getUncle(Node* node) const noexcept;
  Node* getGrandparent(Node* node) const noexcept;

  void recoverBalance(Node* node);

  Node* findNode(const TKey& key) const noexcept;

  void printTreeHelper(Node* node, int space, int indent,
                       std::ostream& out) const;
  void printSortedHelper(Node* node, std::ostream& out) const;

 public:
  RBTree();
  RBTree(const RBTree& other);
  ~RBTree();

  void insert(const TKey& key, const TVal& val);
  TVal* find(const TKey& key) noexcept;
  void clear() noexcept;

  void printTree(std::ostream& out = std::cout) const noexcept;
  void printSorted(std::ostream& out = std::cout) const noexcept;

  bool isEmpty() const { return _root == nullptr; }
  size_t size() const noexcept { return _size; }
  bool contains(const TKey& key) const noexcept {
    return findNode(key) != nullptr;
  }

  int getTreeBlackHeight() const { return getBlackHeight(_root); }

  bool isRBTree() const {
    if (_root && getColor(_root) != BLACK) return false;
    return isRBTreeHelper(_root);
  }

  bool isRBTreeHelper(Node* node) const {
    if (!node) return true;

    if (getColor(node) == RED) {
      if (getColor(node->left) == RED || getColor(node->right) == RED)
        return false;
    }

    int leftBlackHeight = getBlackHeight(node->left);
    int rightBlackHeight = getBlackHeight(node->right);

    if (node->color == BLACK) {
      leftBlackHeight++;
      rightBlackHeight++;
    }

    if (leftBlackHeight != rightBlackHeight) return false;

    return isRBTreeHelper(node->left) && isRBTreeHelper(node->right);
  }
};

template <typename TKey, typename TVal>
RBTree<TKey, TVal>::RBTree() : _root(nullptr), _size(0) {}

template <typename TKey, typename TVal>
RBTree<TKey, TVal>::RBTree(const RBTree& other) : _root(nullptr), _size(0) {
  copyTree(_root, other._root);
}

template <typename TKey, typename TVal>
RBTree<TKey, TVal>::~RBTree() {
  deleteTree(_root);
}

template <typename TKey, typename TVal>
void RBTree<TKey, TVal>::deleteTree(Node* node) {
  if (node == nullptr) return;
  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
}

template <typename TKey, typename TVal>
void RBTree<TKey, TVal>::copyTree(Node*& dest, Node* src) {
  if (src == nullptr) {
    dest = nullptr;
    return;
  }
  dest = new Node(src->data.first, src->data.second);
  dest->color = src->color;
  dest->blackHeight = src->blackHeight;
  copyTree(dest->left, src->left);
  copyTree(dest->right, src->right);
  if (dest->left) dest->left->parent = dest;
  if (dest->right) dest->right->parent = dest;
  _size++;
}

template <typename TKey, typename TVal>
void RBTree<TKey, TVal>::recalcBlackHeight(Node* node) noexcept {
  if (node) {
    int leftBH = getBlackHeight(node->left);
    int rightBH = getBlackHeight(node->right);
    node->blackHeight = std::max(leftBH, rightBH);
    if (node->color == BLACK) node->blackHeight++;
  }
}

template <typename TKey, typename TVal>
void RBTree<TKey, TVal>::leftRotate(Node* node) {
  Node* parent = node->parent;
  Node* rightChild = node->right;

  if (!rightChild) return;

  node->right = rightChild->left;
  if (rightChild->left) rightChild->left->parent = node;

  rightChild->left = node;
  rightChild->parent = parent;
  node->parent = rightChild;

  if (parent) {
    if (parent->left == node)
      parent->left = rightChild;
    else
      parent->right = rightChild;
  } else {
    _root = rightChild;
  }

  recalcBlackHeight(node);
  recalcBlackHeight(rightChild);
}

template <typename TKey, typename TVal>
void RBTree<TKey, TVal>::rightRotate(Node* node) {
  Node* parent = node->parent;
  Node* leftChild = node->left;

  if (!leftChild) return;

  node->left = leftChild->right;
  if (leftChild->right) leftChild->right->parent = node;

  leftChild->right = node;
  leftChild->parent = parent;
  node->parent = leftChild;

  if (parent) {
    if (parent->left == node)
      parent->left = leftChild;
    else
      parent->right = leftChild;
  } else {
    _root = leftChild;
  }

  recalcBlackHeight(node);
  recalcBlackHeight(leftChild);
}

template <typename TKey, typename TVal>
void RBTree<TKey, TVal>::recolor(Node* node) {
  if (node) {
    node->color = (node->color == RED) ? BLACK : RED;
    recalcBlackHeight(node);
  }
}

template <typename TKey, typename TVal>
typename RBTree<TKey, TVal>::Node* RBTree<TKey, TVal>::getUncle(
    Node* node) const noexcept {
  Node* parent = node->parent;
  if (!parent) return nullptr;
  Node* grandparent = parent->parent;
  if (!grandparent) return nullptr;

  return (grandparent->left == parent) ? grandparent->right : grandparent->left;
}

template <typename TKey, typename TVal>
typename RBTree<TKey, TVal>::Node* RBTree<TKey, TVal>::getGrandparent(
    Node* node) const noexcept {
  return node && node->parent ? node->parent->parent : nullptr;
}

template <typename TKey, typename TVal>
void RBTree<TKey, TVal>::recoverBalance(Node* node) {
  Node* C = node;
  Node* P = C->parent;
  Node* G = nullptr;
  Node* U = nullptr;

  while (P && getColor(P) == RED) {
    G = getGrandparent(C);
    U = getUncle(C);

    // Случай 1: Дядя красный -> перекрашивание
    /*
         [G]                  (G) <- перекрас
        /   \                /   \
      (P)   (U)            [P]   [U]
      /                    /
    (C)                  (C)
    */
    if (U && getColor(U) == RED) {
      recolor(P);
      recolor(U);
      recolor(G);

      if (G == _root) {
        recolor(G);
        break;
      }

      C = G;
      P = C->parent;
      continue;
    }

    // Случай 2: Дядя черный -> повороты
    if (G->right == P && P->right == C) {
      // RR случай: левый поворот
      /*
          [G]                  (P)
         /   \                /   \
       [U]   (P)            [G]   (C)
              \            /
              (C)        [U]
      */
      leftRotate(G);
      std::swap(G->color, P->color);
      recalcBlackHeight(G);
      recalcBlackHeight(P);
      break;
    } else if (G->right == P && P->left == C) {
      // RL случай: правый + левый поворот
      /*
         [G]                  (C)
        /   \                /   \
      [U]   (P)            [G]   (P)
            /                    /
          (C)                  [U]
      */
      rightRotate(P);
      leftRotate(G);
      std::swap(G->color, C->color);
      recalcBlackHeight(G);
      recalcBlackHeight(C);
      break;
    } else if (G->left == P && P->left == C) {
      // LL случай: правый поворот
      /*
           [G]                  (P)
          /   \                /   \
        (P)   [U]            (C)   [G]
        /                           \
      (C)                            [U]
      */
      rightRotate(G);
      std::swap(G->color, P->color);
      recalcBlackHeight(G);
      recalcBlackHeight(P);
      break;
    } else if (G->left == P && P->right == C) {
      // LR случай: левый + правый поворот
      /*
           [G]                  (C)
          /   \                /   \
        (P)   [U]            (P)   [G]
          \                        \
          (C)                      [U]
      */
      leftRotate(P);
      rightRotate(G);
      std::swap(G->color, C->color);
      recalcBlackHeight(G);
      recalcBlackHeight(C);
      break;
    }

    break;
  }
}


template <typename TKey, typename TVal>
void RBTree<TKey, TVal>::insert(const TKey& key, const TVal& val) {
  Node* existing = findNode(key);
  if (existing) {
    existing->data.second = val;
    return;
  }

  /*
  Вставка нового узла:
        Вставляем RED узел
              |
              v
          [25]
            /    \
        (15)    (50)

      Вставляем 30 (красный):
            [25]
            /    \
        (15)    (50)
              /
          (30)           // Нарушение! Два красных подряд
  */

  // BST вставка красного узла
  Node* newNode = new Node(key, val);
  _size++;

  if (!_root) {
    _root = newNode;
    recolor(_root);  // Корень черный
    return;
  }

  Node* cur = _root;
  Node* parent = nullptr;

  while (cur) {
    parent = cur;
    if (key < cur->data.first)
      cur = cur->left;
    else
      cur = cur->right;
  }

  newNode->parent = parent;
  if (key < parent->data.first)
    parent->left = newNode;
  else
    parent->right = newNode;

  // Обновляем blackHeight
  Node* temp = newNode;
  while (temp) {
    recalcBlackHeight(temp);
    temp = temp->parent;
  }

  // Восстановление баланса если родитель красный
  if (getColor(parent) == RED) {
    recoverBalance(newNode);
  }
}

template <typename TKey, typename TVal>
typename RBTree<TKey, TVal>::Node* RBTree<TKey, TVal>::findNode(
    const TKey& key) const noexcept {
  Node* cur = _root;
  while (cur) {
    if (key == cur->data.first)
      return cur;
    else if (key < cur->data.first)
      cur = cur->left;
    else
      cur = cur->right;
  }
  return nullptr;
}

template <typename TKey, typename TVal>
TVal* RBTree<TKey, TVal>::find(const TKey& key) noexcept {
  Node* node = findNode(key);
  return node ? &node->data.second : nullptr;
}

template <typename TKey, typename TVal>
void RBTree<TKey, TVal>::clear() noexcept {
  deleteTree(_root);
  _root = nullptr;
  _size = 0;
}

template <typename TKey, typename TVal>
void RBTree<TKey, TVal>::printTreeHelper(Node* node, int space, int indent,
                                         std::ostream& out) const {
  if (node == nullptr) return;

  space += indent;
  printTreeHelper(node->right, space, indent, out);

  out << std::endl;
  for (int i = indent; i < space; i++) out << " ";
  out << node->data.first << ":" << node->data.second;
  out << " (" << (node->color == RED ? "R" : "B");
  out << ", bh=" << node->blackHeight << ")" << std::endl;

  printTreeHelper(node->left, space, indent, out);
}

template <typename TKey, typename TVal>
void RBTree<TKey, TVal>::printTree(std::ostream& out) const noexcept {
  if (isEmpty()) {
    out << "Tree is empty!" << std::endl;
    return;
  }
  printTreeHelper(_root, 0, 4, out);
}

template <typename TKey, typename TVal>
void RBTree<TKey, TVal>::printSortedHelper(Node* node,
                                           std::ostream& out) const {
  if (node == nullptr) return;
  printSortedHelper(node->left, out);
  out << node->data.first << ":" << node->data.second << " ";
  printSortedHelper(node->right, out);
}

template <typename TKey, typename TVal>
void RBTree<TKey, TVal>::printSorted(std::ostream& out) const noexcept {
  if (isEmpty()) {
    out << "Tree is empty!" << std::endl;
    return;
  }
  printSortedHelper(_root, out);
  out << std::endl;
}

#endif  // _LIB_TREE_RB_TREE_H_