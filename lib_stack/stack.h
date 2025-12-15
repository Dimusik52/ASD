// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#ifndef _LIB_STACK_STACK_H_
#define _LIB_STACK_STACK_H_

#include <iostream>
#include <initializer_list>
#include "../lib_TVector/include/TVector.h"


template <class T>
class Stack {
  TVector<T> _data;

 public:
  Stack();
  Stack(int);
  Stack(const TVector<T>&);
  Stack(std::initializer_list<T>);
  Stack(Stack<T>&);


  void push(T val);
  void pop();
  inline T top() const;
  inline bool is_empty() const noexcept;
  inline bool is_full() const noexcept;
  void clear() noexcept;
};

template <class T>
Stack<T>::Stack() {
  _data.shrink_to_fit();
}

template <class T>
Stack<T>::Stack(int size) {
  _data.reserve(size);
}

template <class T>
Stack<T>::Stack(const TVector<T>& vector) {
  _data = TVector<T>(vector);
  _data.shrink_to_fit();
}

template <class T>
Stack<T>::Stack(std::initializer_list<T> init_list) {
  _data = TVector<T>(init_list);
  _data.shrink_to_fit();
}
template <class T>
Stack<T>::Stack(Stack<T>& other) {
  _data = other._data;
  _data.shrink_to_fit();
}

template <class T>
void Stack<T>::push(T val) { // O(n) в случае расширения, без расширения O(1)
  if (is_full()) throw std::logic_error("push(): Stack is full!");
  _data.push_back(val);
}

template <class T>
void Stack<T>::pop() { // O(1)
  if (is_empty()) throw std::logic_error("pop(): Stack is empty!");
  _data.pop_back();
}

template <class T>
T Stack<T>::top() const { // O(1)
  if (is_empty()) throw std::logic_error("top(): Stack is empty!");
  return _data.back();
}

template <class T>
inline bool Stack<T>::is_empty() const noexcept { // O(1)
  return _data.is_empty();
}

template <class T>
inline bool Stack<T>::is_full() const noexcept { // O(1)
  return _data.is_full();
}

template <class T>
void Stack<T>::clear() noexcept { // O(n)
  _data.clear();
}


#endif  // !_LIB_STACK_STACK_H_