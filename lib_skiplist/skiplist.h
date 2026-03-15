// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2

#ifndef LIB_SKIPLIST_SKIPLIST_H_
#define LIB_SKIPLIST_SKIPLIST_H_

#include <utility>
#include <string>

#include "../lib_TVector/include/TVector.h"

template <typename TKey, typename TValue>
struct NodeSL {
  std::pair<TKey, TValue> _data;
  NodeSL** _next;
  size_t _level;

  NodeSL(TKey key, TValue value, size_t level) : _level(level) {
    _data = {key, value};
    _next = new NodeSL*[level + 1];
    for (size_t i = 0; i <= level; i++) {
      _next[i] = nullptr;
    }
  }

  ~NodeSL() { delete[] _next; }
};

template <typename TKey, typename TValue>
class SkipList {
 private:
  size_t MAX_LVLS;
  size_t _lvl;
  TVector<NodeSL<TKey, TValue>*> _heads;

 public:
  SkipList(size_t maxLevels = 10) : MAX_LVLS(maxLevels), _lvl(0) {
    srand(time(nullptr));
    for (size_t i = 0; i <= MAX_LVLS; i++) {
      _heads.push_back(nullptr);
    }
  }

  ~SkipList() {
    if (_heads.size() > 0 && _heads[0] != nullptr) {
      NodeSL<TKey, TValue>* current = _heads[0];
      while (current != nullptr) {
        NodeSL<TKey, TValue>* next = current->_next[0];
        delete current;
        current = next;
      }
    }
  }

  void insert(const TKey& key, const TValue& value) {
    TVector<NodeSL<TKey, TValue>*> update;
    for (size_t i = 0; i <= MAX_LVLS; i++) {
      update.push_back(nullptr);
    }

    NodeSL<TKey, TValue>* current = find_nearest(key, update);

    if (current != nullptr && current->_data.first == key) {
      std::cout << "Key " << key << " is already exists!\n";
      return;
    }

    size_t newLevel = flipCoin();
    if (newLevel > _lvl) {
      _lvl = newLevel;
    }

    NodeSL<TKey, TValue>* newNode = new NodeSL<TKey, TValue>(key, value, newLevel);

    for (size_t i = 0; i <= newLevel; i++) {
      if (update[i] != nullptr) {
        newNode->_next[i] = update[i]->_next[i];
        update[i]->_next[i] = newNode;
      } else {
        newNode->_next[i] = _heads[i];
        _heads[i] = newNode;
      }
    }
  }

  void print() const noexcept {
    TVector<NodeSL<TKey, TValue>*> nodes;
    NodeSL<TKey, TValue>* current = _heads[0];
    while (current != nullptr) {
      nodes.push_back(current);
      current = current->_next[0];
    }
    for (int i = 0; i < nodes.size() - 1; i++) {
      for (int j = 0; j < nodes.size() - i - 1; j++) {
        if (nodes[j]->_data.first > nodes[j + 1]->_data.first) {
          auto temp = nodes[j];
          nodes[j] = nodes[j + 1];
          nodes[j + 1] = temp;
        }
      }
    }
    std::cout << "Index: ";
    for (int i = 0; i < nodes.size(); i++) {
      std::printf("%5d ", i);
    }
    std::cout << "\n";

    std::cout << "Key:   ";
    for (int i = 0; i < nodes.size(); i++) {
      std::printf("%5d ", nodes[i]->_data.first);
    }
    std::cout << "\n";

   /* std::cout << "Value: ";
    for (int i = 0; i < nodes.size(); i++) {
      std::cout << "  ";
      std::cout.width(3);
      std::cout << nodes[i]->_data.second << " ";
    }
    std::cout << "\n";*/

    for (int level = _lvl; level >= 0; level--) {
      std::cout << "Level " << level << ":";
      for (int i = 0; i < nodes.size(); i++) {
        if (level <= nodes[i]->_level) {
          std::cout << "  X   ";
        } else {
          std::cout << "  .   ";
        }
      }
      std::cout << "\n";
    }
  }

  protected:
  size_t flipCoin() const noexcept {
    size_t level = 0;
    while (rand() % 2 == 1 && level < MAX_LVLS) {
      level++;
    }
    return level;
  }
  NodeSL<TKey, TValue>* find_nearest(
      const TKey& key, TVector<NodeSL<TKey, TValue>*>& update) const noexcept {
    NodeSL<TKey, TValue>* current = nullptr;
    for (int level = _lvl; level >= 0; level--) {
      if (current == nullptr) {
        current = _heads[level];
      }
      while (current != nullptr) {
        if (level < current->_level && current->_next[level] != nullptr &&
            current->_next[level]->_data.first < key) {
          current = current->_next[level];
        } else {
          break;
        }
      }

      if (level < update.size()) {
        update[level] = current;
      }
    }
    if (current != nullptr) {
      current = current->_next[0];
    }

    return current;
  }

  public:
  bool find(const TKey& key, TValue& value) const {
    TVector<NodeSL<TKey, TValue>*> update;
    for (size_t i = 0; i <= MAX_LVLS; i++) {
      update.push_back(nullptr);
    }
    NodeSL<TKey, TValue>* current = nullptr;

    for (int level = _lvl; level >= 0; level--) {
      if (current == nullptr && level < _heads.size()) {
        current = _heads[level];
      }

      while (current != nullptr && current->_next[level] != nullptr &&
             current->_next[level]->_data.first < key) {
        current = current->_next[level];
      }
    }

    if (current != nullptr) {
      current = current->_next[0];
    }

    if (current != nullptr && current->_data.first == key) {
      value = current->_data.second;
      return true;
    }
    return false;
  }
  bool remove(const TKey& key) {
    TVector<Node<TKey, TValue>*> update;
    for (size_t i = 0; i <= MAX_LVLS; i++) {
      update.push_back(nullptr);
    }

    NodeSL<TKey, TValue>* current = find_nearest(key, update);

    if (current == nullptr || current->_data.first != key) {
      return false;
    }

    for (size_t i = 0; i <= _lvl; i++) {
      if (update[i] != nullptr && update[i]->_next[i] == current) {
        update[i]->_next[i] = current->_next[i];
      }
    }
    delete current;
    while (_lvl > 0 && _heads[_lvl] == nullptr) {
      _lvl--;
    }
    return true;
  }
};

#endif  // LIB_SKIPLIST_SKIPLIST_H_