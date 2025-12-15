// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2
#ifndef LIB_DSU_DSU_H_
#define LIB_DSU_DSU_H_

#include <stdexcept>

template <class T>
class DSU {
 private:
  T* _parent;
  T* _rank;
  size_t _size;

  void check_index(T x) const;

 public:
  explicit DSU(size_t size);
  DSU(const DSU& other);
  ~DSU();

  DSU& operator=(const DSU& other);

  void union_sets(T x, T y);
  T find(T x);
  T find_rec(T x);
  bool connected(T x, T y);

  size_t size() const;
};

template <class T>
void DSU<T>::check_index(T x) const {
  if (x < 0 || x >= _size) {
    throw std::out_of_range("DSU index out of range");
  }
}

template <class T>
DSU<T>::DSU(size_t size) : _size(size) {
  if (size == 0) {
    throw std::invalid_argument("DSU(): DSU size cannot be zero");
  }

  _parent = new T[size];
  _rank = new T[size];

  for (size_t i = 0; i < size; ++i) {
    _parent[i] = i;
    _rank[i] = 0;
  }
}

template <class T>
DSU<T>::DSU(const DSU& other) : _size(other._size) {
  _parent = new T[_size];
  _rank = new T[_size];

  for (size_t i = 0; i < _size; ++i) {
    _parent[i] = other._parent[i];
    _rank[i] = other._rank[i];
  }
}

template <class T>
DSU<T>::~DSU() {
  delete[] _parent;
  delete[] _rank;
}

template <class T>
DSU<T>& DSU<T>::operator=(const DSU& other) {
  if (this != &other) {
    delete[] _parent;
    delete[] _rank;

    _size = other._size;
    _parent = new T[_size];
    _rank = new T[_size];

    for (size_t i = 0; i < _size; ++i) {
      _parent[i] = other._parent[i];
      _rank[i] = other._rank[i];
    }
  }
  return *this;
}

template <class T>
void DSU<T>::union_sets(T x, T y) {
  check_index(x);
  check_index(y);

  T root_x = find(x);
  T root_y = find(y);

  if (root_x == root_y) {
    return;
  }

  if (_rank[root_x] > _rank[root_y]) {
    _parent[root_y] = root_x;
  } else if (_rank[root_x] < _rank[root_y]) {
    _parent[root_x] = root_y;
  } else {
    _parent[root_y] = root_x;
    _rank[root_x]++;
  }
}

template <class T>
T DSU<T>::find(T x) {
  check_index(x);

  T root = x;
  while (root != _parent[root]) {
    root = _parent[root];
  }

  while (x != root) {
    T next = _parent[x];
    _parent[x] = root;
    x = next;
  }

  return root;
}

template <class T>
T DSU<T>::find_rec(T x) {
  check_index(x);

  if (_parent[x] != x) {
    _parent[x] = find_rec(_parent[x]);
  }
  return _parent[x];
}

template <class T>
bool DSU<T>::connected(T x, T y) {
  return find(x) == find(y);
}

template <class T>
size_t DSU<T>::size() const {
  return _size;
}

#endif  // LIB_DSU_DSU_H_
