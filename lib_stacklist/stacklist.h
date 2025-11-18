// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#ifndef _LIB_STACKLIST_STACKLIST_H_
#define _LIB_STACKLIST_STACKLIST_H_

#include <iostream>
#include "../lib_list/list.h"

template <class T>
class StackList {
  List<T> _data;

  public:
  StackList();
  StackList(List<T>&);
  StackList(std::initializer_list<T>);
  StackList(StackList<T>&);

  void push(T val);
  void pop();
  inline T top();
  inline bool is_empty() noexcept;
  inline bool is_full() const noexcept;
  void clear() noexcept;
};

template <class T>
StackList<T>::StackList() {
}

template <class T>
StackList<T>::StackList(List<T>& other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    _data.push_back(*it);
  }
}

template <class T>
StackList<T>::StackList(std::initializer_list<T> init_list) {
  for (const auto& item : init_list) {
    _data.push_back(item);
  }
}
template <class T>
StackList<T>::StackList(StackList<T>& other) {
  for (auto it = other._data.begin(); it != other._data.end(); ++it) {
    _data.push_back(*it);
  }
}

template <class T>
void StackList<T>::push(T val) {
  if (is_full()) throw std::logic_error("push(): Stack is full!");
  _data.push_back(val);
}

template <class T>
void StackList<T>::pop() {
  if (is_empty()) throw std::logic_error("pop(): Stack is empty!");
  _data.pop_back();
}

template <class T>
T StackList<T>::top() {
  if (is_empty()) throw std::logic_error("top(): Stack is empty!");
  auto it = _data.begin();
  auto prev = it;
  while (it != _data.end()) {
    prev = it;
    ++it;
  }
  return *prev;
}

template <class T>
inline bool StackList<T>::is_empty() noexcept {
  return _data.is_empty();
}

template <class T>
inline bool StackList<T>::is_full() const noexcept {
  return false;
}

template <class T>
void StackList<T>::clear() noexcept {
  while (!is_empty()) {
    pop();
  }
}


#endif  // !_LIB_STACKLIST_STACKLIST_H_