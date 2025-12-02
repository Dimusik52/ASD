// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#ifndef _LIB_QUEUE_QUEUE_H_
#define _LIB_QUEUE_QUEUE_H_

#include <iostream>
#include <initializer_list>


template <class T>
class Queue {
  T* _data;
  int _size;
  int _head;
  int _tail;
  int _count;

 public:
  Queue();
  Queue(int);
  Queue(std::initializer_list<T>);
  Queue(const Queue<T>&);
  ~Queue();

  void push(T val);
  void pop();
  inline T tail() const;
  inline bool is_empty() const noexcept;
  inline bool is_full() const noexcept;
  void clear() noexcept;
  T head() const;

 private:
};

template <class T>
Queue<T>::Queue() {
  _data = new T[1];
  _size = 1;
  _head = 0;
  _tail = 0;
  _count = 0;
}

template <class T>
Queue<T>::Queue(int size) {
  if (size < 0) {
    throw std::invalid_argument(
        "Queue: Invalid argument 'size' - must be >= 0");
  }
  _data = new T[size > 0 ? size : 1];
  _size = size > 0 ? size : 1;
  _head = 0;
  _tail = 0;
  _count = 0;
}


template <class T>
Queue<T>::Queue(std::initializer_list<T> init) {
  if (init.size() <= 0) {
    throw std::invalid_argument(
        "Queue: Invalid argument - list must not be empty");
  }
  _size = init.size();
  _data = new T[_size];
  _head = 0;
  _count = init.size();

  const T* src = init.begin();
  for (int i = 0; i < _size; i++) {
    _data[i] = src[i];
  }
  _tail = _count % _size;
}

template <class T>
Queue<T>::Queue(const Queue<T>& other) {
  _data = new T[other._size];
  for (int i = 0; i < other._size; i++) {
    _data[i] = other._data[i];
  }
  _size = other._size;
  _head = other._head;
  ;
  _tail = other._tail;
  _count = other._count;
}

template <class T>
Queue<T>::~Queue() {
  delete[] _data;
}



template <class T>
inline bool Queue<T>::is_empty() const noexcept { // O(1)
  return _count == 0;
}

template <class T>
inline bool Queue<T>::is_full() const noexcept { // O(1)
  return _count == _size;
}

template <class T>
void Queue<T>::push(T val) { // O(1)
  if (is_full()) throw std::logic_error("push(): Queue is full!");
  _count++;
  _data[_tail] = val;
  _tail = (_tail + 1) % _size;
}

template <class T>
void Queue<T>::pop() { // O(1)
  if (is_empty()) throw std::logic_error("pop(): Queue is empty!");
  _head = (_head + 1) % _size;
  _count--;
}

template <class T>
inline T Queue<T>::tail() const { // O(1)
  if (is_empty()) throw std::logic_error("tail(): Queue is empty!");
  return _data[(_tail - 1 + _size) % _size];
}

template <class T>
T Queue<T>::head() const { // O(1)
  if (is_empty()) throw std::logic_error("tail(): Queue is empty!");
  return _data[_head];
}

template <class T>
void Queue<T>::clear() noexcept { // O(1)
  if (is_empty()) return;
  _head = 0;
  _tail = 0;
  _count = 0;
}

#endif  // !_LIB_QUEUE_QUEUE_H_
