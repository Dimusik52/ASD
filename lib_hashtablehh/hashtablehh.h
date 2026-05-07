// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2

#ifndef LIB_HASHTABLEHH_HASHTABLEHH_H_
#define LIB_HASHTABLEHH_HASHTABLEHH_H_
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include "../lib_itable/itable.h"

enum class Status { EMPTY, BUSY, DELETED };

template <class TValue>
struct HashData {
  Status _state;
  std::string _key;
  TValue _value;

  HashData() : _state(Status::EMPTY), _key(""), _value() {}
  HashData(const std::string& key, const TValue& value, Status state)
      : _state(state), _key(key), _value(value) {}
};

template <class TValue>
class HashTableHH : public ITable<std::string, TValue> {
 private:
  std::vector<HashData<TValue>> _rows;
  size_t _size;
  size_t _shift;
  size_t _elementCount;

  size_t gcd(size_t a, size_t b) const noexcept;

  bool isMutuallyPrime(size_t a, size_t b) const noexcept {
    return gcd(a, b) == 1;
  }

  size_t h(const std::string& key) const noexcept;

  size_t hh(size_t hash) const noexcept { return (hash + _shift) % _size; }

 public:
  HashTableHH();
  HashTableHH(size_t size);
  HashTableHH(const HashTableHH& other)
      : _rows(other._rows),
        _size(other._size),
        _shift(other._shift),
        _elementCount(other._elementCount) {}

  void insert(const std::string& key, const TValue& value) override;

  void erase(const std::string& key) override;

  TValue* find(const std::string& key) noexcept override;

  bool isEmpty() const noexcept override { return _elementCount == 0; }

  bool contains(const std::string& key) const noexcept override;

  void print(std::ostream& out) const override;

  size_t size() const noexcept { return _elementCount; }

  size_t capacity() const noexcept { return _size; }

  bool isFull() const noexcept { return _elementCount == _size; }
};

template <class T>
size_t HashTableHH<T>::gcd(size_t a, size_t b) const noexcept {
  while (b != 0) {
    size_t t = b;
    b = a % b;
    a = t;
  }
  return a;
}

template <class T>
size_t HashTableHH<T>::h(const std::string& key) const noexcept {
  size_t hash = 0;
  for (size_t i = 0; i < key.length(); i++) {
    hash += key[i];
  }
  return hash % _size;
}
template <class T>
HashTableHH<T>::HashTableHH() : _size(100), _elementCount(0) {
  for (size_t i = std::max(2, (int)(_size / 15)); i < _size; i++) {
    if (isMutuallyPrime(i, _size)) {
      _shift = i;
      break;
    }
  }
  _rows.resize(_size);
}

template <class T>
HashTableHH<T>::HashTableHH(size_t size) : _size(size), _elementCount(0) {
  for (size_t i = std::max(2, (int)(_size / 15)); i < _size; i++) {
    if (isMutuallyPrime(i, _size)) {
      _shift = i;
      break;
    }
  }
  _rows.resize(_size);
}

template <class TValue>
void HashTableHH<TValue>::insert(const std::string& key, const TValue& value) {
  if (isFull()) {
    throw std::logic_error("Hash table is full!");
  }

  size_t hash = h(key);
  size_t firstHash = hash;

  while (true) {
    if (_rows[hash]._state != Status::BUSY) {
      _rows[hash] = HashData<TValue>(key, value, Status::BUSY);
      _elementCount++;
      return;
    }

    if (_rows[hash]._state == Status::BUSY && _rows[hash]._key == key) {
      throw std::logic_error("Key already exists!");
    }

    hash = hh(hash);
    if (firstHash == hash) {
      throw std::logic_error("Hash table is full!");
    }
  }
}

template <class T>
void HashTableHH<T>::erase(const std::string& key) {
  size_t hash = h(key);
  size_t firstHash = hash;

  while (true) {
    if (_rows[hash]._state == Status::EMPTY) {
      throw std::logic_error("Key doesn't exist!");
    }

    if (_rows[hash]._state == Status::BUSY && _rows[hash]._key == key) {
      _rows[hash]._state = Status::DELETED;
      _elementCount--;
      return;
    }

    hash = hh(hash);
    if (firstHash == hash) {
      throw std::logic_error("Key doesn't exist!");
    }
  }
}

template <class TValue>
TValue* HashTableHH<TValue>::find(const std::string& key) noexcept {
  size_t hash = h(key);
  size_t firstHash = hash;

  while (true) {
    if (_rows[hash]._state == Status::EMPTY) {
      return nullptr;
    }

    if (_rows[hash]._state == Status::BUSY && _rows[hash]._key == key) {
      return &(_rows[hash]._value);
    }

    hash = hh(hash);
    if (firstHash == hash) {
      return nullptr;
    }
  }
}

template <class T>
bool HashTableHH<T>::contains(
    const std::string& key) const noexcept {
  size_t hash = h(key);
  size_t firstHash = hash;

  while (true) {
    if (_rows[hash]._state == Status::EMPTY) {
      return false;
    }

    if (_rows[hash]._state == Status::BUSY && _rows[hash]._key == key) {
      return true;
    }

    hash = hh(hash);
    if (firstHash == hash) {
      return false;
    }
  }
}
template <class T>
void HashTableHH<T>::print(std::ostream& out) const {
  for (size_t i = 0; i < _size; i++) {
    if (_rows[i]._state == Status::BUSY) {
      out << _rows[i]._key << ":" << _rows[i]._value << "\n";
    }
  }
}

#endif  // LIB_HASHTABLEHH_HASHTABLEHH_H_