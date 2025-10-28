// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2
#ifndef LIB_LIST_LIST_H_
#define LIB_LIST_LIST_H_

#include <iostream>



template <class T>
class List {
 private:
  struct Node {
    T value;
    Node* next;

    Node(T value, Node<T>* next = nullptr) : value(val), next(nxt){};
  };
  

  Node* _head, *_tail;

 public:
  List();
  List(const List<T>&);
  ~List();
  
  bool is_empty();
  void push_front(const T& value) noexcept;
  void push_back(const T& value) noexcept;
  void insert(size_t pos, const T& value);
  void insert(Node* node, const T& value);
  void pop_back();
};

template <class T>
List<T>::List() : _head(nullptr), _tail(nullptr){};

template <class T>
List<T>::List(const List<T>& other) {
  Node* current = other._head;
  while (current != nullptr) {
    push_back(current->value);
    current = current->next;
  }
}

template <class T>
List<T>::~List() {
  while (_head != nullptr) {
    Node* temp = _head;
    _head = _head->next;
    delete temp;
  }
}

template <class T>
bool List<T>::is_empty() { return _head == nullptr; }

template <class T>
void List<T>::push_front(const T& value) {
  Node* node = new Node(val, _head);
  if (is_empty()) {
    _tail = node;
  }
  _head = node;
}

template <class T>
void List<T>::push_back(const T& val) {
  Node* node = new Node(val);

  if (is_empty()) {
    _head = node;
    _tail = node;
    return;
  }
  tail->next = node;
  _tail = node;
}

template <class T>
void List<T>::insert(Node* node, const T& val) {
  if (node == nullptr || is_empty()) {
    throw std::logic_error("List.insert(): List is empty");
  }
  Node* new_node = new Node<T>(val);
  new_node->next = node->next;
  node->next = new_node;
  if (node == _tail) {
    _tail = new_node;
  }
}

template <class T>
void List<T>::insert(size_t pos, const T& val) {
  if (pos == 0) {
    push_front(val);
    return;
  }

  Node* cur = _head;
  size_t cur_pos = 0;
  while (cur != nullptr) {
    if (cur_pos == pos - 1) {
      break;
    }
    cur_pos++;
    cur = cur->next;
  }
  if (cur == nullptr) {
    throw std::logic_error("List.insert(): Position out of range");
  }
  insert(cur, val);
}

template <class T>
void List<T>::pop_back() {
  if (is_empty()) {
    throw std::logic_error("List.pop_back(): List is empty");
  }
  if (_head == _tail) {
    delete _head;
    _head = nullptr;
    _tail = nullptr;
    return;
  }
  Node* cur = _head;
  while (cur->next != _tail) {
    cur = cur->next;
    delete _tail;
    _tail = cur;
    cur->next = nullptr;
  }
}



#endif  // !LIB_LIST_LIST_H_