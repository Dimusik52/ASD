// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2

#ifndef LIB_HASHTABLEC_HASHTABLEC_H_
#define LIB_HASHTABLEC_HASHTABLEC_H_
#include <iostream>
#include <string>
#include <vector>
#include "../lib_itable/itable.h"
#include "../lib_list/list.h"

template <class TValue> 
class HashTableC : public ITable<std::string, TValue> {
  struct HashData {
    std::string _key;
    TValue _value;
    HashData() = default;
    HashData(std::string key, TValue val) : _key(key), _value(val) {};
  };
  std::vector<List<HashData>> _rows;
  size_t _size;
  size_t _elementCount;
 public:
  HashTableC();
  HashTableC(size_t size);
  HashTableC(const HashTableC& other);

  void insert(const std::string&, const TValue&) override;
  void erase(const std::string&) override;
  TValue* find(const std::string&) noexcept override;
  bool isEmpty() const noexcept override;

  bool contains(const std::string&) const noexcept override;

  void print(std::ostream& out) const override;
 private:
  size_t h(const std::string key) const noexcept;
};

template <class TValue>
HashTableC<TValue>::HashTableC() : _size(10000), _elementCount(0) {
  for (size_t i = 0; i < _size; i++) {
    _rows.push_back(List<HashData>());
  }
}
template <class TValue>
HashTableC<TValue>::HashTableC(size_t size) : _size(size), _elementCount(0) {
  for (size_t i = 0; i < size; i++) {
    _rows.push_back(List<HashData>());
  }
}

template <class TValue>
HashTableC<TValue>::HashTableC(const HashTableC& other) {
  for (size_t i = 0; i < other._rows.size(); i++) {
    _rows.push_back(List<HashData>());
    for (auto it = other._rows[i].begin(); it != other._rows[i].end(); ++it) {
      _rows[i].push_back(*it);
    }
  }
}

template <class TValue>
void HashTableC<TValue>::insert(const std::string& key, const TValue& value) {
  size_t hash = h(key);
  HashData* found = nullptr;
  for (auto it = _rows[hash].begin(); it != _rows[hash].end(); it++) {
    if (it.get_node()->value._key == key) {
      found = &(it.get_node()->value);
      break;
    }
  }
  if (found) {
    throw std::logic_error("Key already exists!");
  }
  _rows[hash].push_back(HashData(key, value));
  _elementCount++;
}

template <class TValue>
void HashTableC<TValue>::erase(const std::string& key) {
  size_t hash = h(key);

  for (auto it = _rows[hash].begin(); it != _rows[hash].end(); it++) {
    if (it.get_node()->value._key == key) {
      _rows[hash].erase(it.get_node());
      _elementCount--;
      return;
    }
  }
  throw std::logic_error("Key doesn`t exist!");
}

template <class TValue>
TValue* HashTableC<TValue>::find(const std::string& key) noexcept {
  size_t hash = h(key);

  for (auto it = _rows[hash].begin(); it != _rows[hash].end(); it++) {
    if (it.get_node()->value._key == key) {
      return &(it.get_node()->value._value);
    }
  }
  return nullptr;
}

template <class TValue>
bool HashTableC<TValue>::isEmpty() const noexcept {
  return _elementCount == 0;
}
template <class TValue>
bool HashTableC<TValue>::contains(const std::string& key) const noexcept {
  size_t hash = h(key);

  for (auto it = _rows[hash].begin(); it != _rows[hash].end(); it++) {
    if (it.get_node()->value._key == key) {
      return true;
    }
  }
  return false;
};
template <class TValue>
void HashTableC<TValue>::print(std::ostream& out) const {
  for (size_t i = 0; i < _rows.size() - 1; i++) {
    for (auto it = _rows[i].begin(); it != _rows[i].end(); it++) {
      std::cout << it.get_node()->value._key << ":"
                << it.get_node()->value._value << "\n";
    }
  }
};
template <class TValue>
size_t HashTableC<TValue>::h(const std::string key) const noexcept {
  size_t hash = 0;
  for (size_t i = 0; i < key.length(); i++) {
    hash += key[i];
  }
  hash %= _size;
  return hash;
}

#endif  // LIB_HASHTABLEC_HASHTABLEC_H_