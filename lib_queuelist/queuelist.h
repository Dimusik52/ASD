// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#ifndef _LIB_QUEUELIST_QUEUELIST_H_
#define _LIB_QUEUELIST_QUEUELIST_H_

#include <iostream>
#include <vector>

#include "../lib_list/list.h"

template <class T>
class QueueList {
  List<T> _data;

 public:
  QueueList() = default;
  QueueList(std::initializer_list<T> init_list);
  QueueList(QueueList<T>& other);

  void push(T val);
  void pop();
  inline T head();
  inline T tail();
  inline bool is_empty() noexcept;
  inline bool is_full() noexcept;
  void clear() noexcept;

};

template <class T>
QueueList<T>::QueueList(std::initializer_list<T> init_list) {
  for (const auto& item : init_list) {
    push(item);
  }
}

template <class T>
QueueList<T>::QueueList(QueueList<T>& other) {
  for (auto it = other._data.begin(); it != other._data.end(); ++it) {
    _data.push_back(*it);
  }
}

template <class T>
void QueueList<T>::push(T val) {
  _data.push_back(val);
}

template <class T>
void QueueList<T>::pop() {
  if (is_empty()) {
    throw std::logic_error("pop(): Queue is empty!");
  }

  auto first = _data.begin();
  if (++first == _data.end()) {
    _data.pop_back();
    return;
  }

  List<T> temp;
  auto it = _data.begin();
  ++it;

  while (it != _data.end()) {
    temp.push_back(*it);
    ++it;
  }

  _data = List<T>();
  for (const auto& val : temp) {
    _data.push_back(val);
  }
}

template <class T>
T QueueList<T>::head() {
  if (is_empty()) {
    throw std::logic_error("head(): Queue is empty!");
  }
  return *_data.begin();
}

template <class T>
T QueueList<T>::tail() {
  if (is_empty()) {
    throw std::logic_error("tail(): Queue is empty!");
  }
  auto it = _data.begin();
  auto prev = it;
  while (it != _data.end()) {
    prev = it;
    ++it;
  }
  return *prev;
}

template <class T>
bool QueueList<T>::is_empty() noexcept {
  return _data.is_empty();
}

template <class T>
bool QueueList<T>::is_full() noexcept {
  return false;
}

template <class T>
void QueueList<T>::clear() noexcept {
  _data = List<T>();
}


#endif  // !_LIB_QUEUELIST_QUEUELIST_H_
