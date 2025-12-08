// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2
#ifndef LIB_LIST_DOUBLYLINKEDLIST_H_
#define LIB_LIST_DOUBLYLINKEDLIST_H_

template <class T>
class DoublyLinkedList {
 private:
  struct Node {
    T value;
    Node* next;
    Node* prev;

    Node(T val, Node* nxt = nullptr, Node* prv = nullptr)
        : value(val), next(nxt), prev(prv) {}
  };

  Node *_head, *_tail;

 public:
  DoublyLinkedList();
  DoublyLinkedList(const DoublyLinkedList<T>&);
  ~DoublyLinkedList();

  bool is_empty();
  void push_front(const T& value) noexcept;
  void push_back(const T& value) noexcept;
  void insert_after(Node* node, const T& value);
  void insert_before(Node* node, const T& value);
  void insert(size_t pos, const T& value);
  void pop_back();
  void pop_front();
  void erase(size_t pos);
  void erase(Node* node);

  class Iterator {
    Node* _current;

   public:
    Iterator() : _current(nullptr){};
    Iterator(Node* node) : _current(node){};

    Node* get_node() { return _current; }

    Iterator& operator=(const Iterator& other) noexcept {
      _current = other._current;
      return *this;
    }

    Iterator& operator++() noexcept {
      if (_current != nullptr) {
        _current = _current->next;
      }
      return *this;
    }

    Iterator operator++(int) noexcept {
      Iterator temp = *this;
      ++(*this);
      return temp;
    }

    Iterator& operator--() noexcept {
      if (_current != nullptr) {
        _current = _current->prev;
      }
      return *this;
    }

    Iterator operator--(int) noexcept {
      Iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator!=(const Iterator& other) const noexcept {
      return _current != other._current;
    }

    bool operator==(const Iterator& other) const noexcept {
      return _current == other._current;
    }

    T& operator*() {
      if (_current == nullptr) {
        throw std::runtime_error(
            "DoublyLinkedList::Iterator.operator*(): Dereferencing end "
            "iterator");
      }
      return _current->value;
    }

    T* operator->() {
      if (_current == nullptr) {
        throw std::runtime_error(
            "DoublyLinkedList::Iterator.operator->(): Accessing end iterator");
      }
      return &(_current->value);
    }

    Iterator& operator+=(size_t n) {
      for (size_t i = 0; i < n && _current != nullptr; ++i) {
        _current = _current->next;
      }
      return *this;
    }

    Iterator& operator-=(size_t n) {
      for (size_t i = 0; i < n && _current != nullptr; ++i) {
        _current = _current->prev;
      }
      return *this;
    }
  };

  class ReverseIterator {
    Node* _current;

   public:
    ReverseIterator() : _current(nullptr){};
    ReverseIterator(Node* node) : _current(node){};

    Node* get_node() { return _current; }

    ReverseIterator& operator++() noexcept {
      if (_current != nullptr) {
        _current = _current->prev;
      }
      return *this;
    }

    ReverseIterator& operator--() noexcept {
      if (_current != nullptr) {
        _current = _current->next;
      }
      return *this;
    }

        ReverseIterator operator++(int) noexcept {
      ReverseIterator temp = *this;
      ++(*this);
      return temp;
    }

    ReverseIterator operator--(int) noexcept {
      ReverseIterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator!=(const ReverseIterator& other) const noexcept {
      return _current != other._current;
    }

    T& operator*() {
      if (_current == nullptr) {
        throw std::runtime_error("ReverseIterator: Dereferencing end iterator");
      }
      return _current->value;
    }

    ReverseIterator& operator+=(size_t n) {
      for (size_t i = 0; i < n && _current != nullptr; ++i) {
        _current = _current->prev;
      }
      return *this;
    }

    ReverseIterator& operator-=(size_t n) {
      for (size_t i = 0; i < n && _current != nullptr; ++i) {
        _current = _current->next;
      }
      return *this;
    }

    bool operator==(const ReverseIterator& other) const noexcept {
      return _current == other._current;
    }

    T* operator->() {
      if (_current == nullptr) {
        throw std::runtime_error("ReverseIterator: Accessing end iterator");
      }
      return &(_current->value);
    }
  };

  inline Iterator begin();
  inline Iterator end();
  inline ReverseIterator rbegin();
  inline ReverseIterator rend();
};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() : _head(nullptr), _tail(nullptr) {}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other)
    : _head(nullptr), _tail(nullptr) {
  Node* current = other._head;
  while (current != nullptr) {
    push_back(current->value);
    current = current->next;
  }
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  while (_head != nullptr) {
    Node* temp = _head;
    _head = _head->next;
    delete temp;
  }
}

template <class T>
bool DoublyLinkedList<T>::is_empty() {
  return _head == nullptr;
}

template <class T>
void DoublyLinkedList<T>::push_front(const T& value) noexcept {
  Node* node = new Node(value, _head, nullptr);
  if (_head != nullptr) {
    _head->prev = node;
  }
  _head = node;
  if (_tail == nullptr) {
    _tail = node;
  }
}

template <class T>
void DoublyLinkedList<T>::push_back(const T& val) noexcept {
  Node* node = new Node(val, nullptr, _tail);
  if (_tail != nullptr) {
    _tail->next = node;
  }
  _tail = node;
  if (_head == nullptr) {
    _head = node;
  }
}

template <class T>
void DoublyLinkedList<T>::insert_after(Node* node, const T& val) {
  if (node == nullptr || is_empty()) {
    throw std::logic_error(
        "DoublyLinkedList::insert_after(): Invalid node or empty list");
  }

  Node* new_node = new Node(val, node->next, node);
  node->next = new_node;

  if (new_node->next != nullptr) {
    new_node->next->prev = new_node;
  }

  if (node == _tail) {
    _tail = new_node;
  }
}

template <class T>
void DoublyLinkedList<T>::insert_before(Node* node, const T& val) {
  if (node == nullptr || is_empty()) {
    throw std::logic_error(
        "DoublyLinkedList::insert_before(): Invalid node or empty list");
  }

  Node* new_node = new Node(val, node, node->prev);
  node->prev = new_node;

  if (new_node->prev != nullptr) {
    new_node->prev->next = new_node;
  }

  if (node == _head) {
    _head = new_node;
  }
}

template <class T>
void DoublyLinkedList<T>::insert(size_t pos, const T& val) {
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
    throw std::logic_error("DoublyLinkedList::insert(): Position out of range");
  }
  insert_after(cur, val);
}

template <class T>
void DoublyLinkedList<T>::pop_back() {
  if (is_empty()) {
    throw std::logic_error("DoublyLinkedList::pop_back(): List is empty");
  }

  if (_head == _tail) {
    delete _head;
    _head = nullptr;
    _tail = nullptr;
    return;
  }

  Node* old_tail = _tail;
  _tail = _tail->prev;
  if (_tail != nullptr) {
    _tail->next = nullptr;
  }
  delete old_tail;
}

template <class T>
void DoublyLinkedList<T>::pop_front() {
  if (is_empty()) {
    throw std::logic_error("DoublyLinkedList::pop_front(): List is empty");
  }

  Node* old_head = _head;
  _head = _head->next;
  if (_head != nullptr) {
    _head->prev = nullptr;
  } else {
    _tail = nullptr;
  }
  delete old_head;
}

template <class T>
void DoublyLinkedList<T>::erase(size_t pos) {
  if (is_empty()) {
    throw std::logic_error("DoublyLinkedList::erase(): List is empty");
  }

  if (pos == 0) {
    pop_front();
    return;
  }

  Node* current = _head;
  for (size_t i = 0; i < pos && current != nullptr; i++) {
    current = current->next;
  }

  if (current == nullptr) {
    throw std::logic_error("DoublyLinkedList::erase(): Position out of range");
  }

  if (current->prev != nullptr) {
    current->prev->next = current->next;
  }
  if (current->next != nullptr) {
    current->next->prev = current->prev;
  }

  if (current == _head) {
    _head = current->next;
  }
  if (current == _tail) {
    _tail = current->prev;
  }

  delete current;
}

template <class T>
void DoublyLinkedList<T>::erase(Node* node) {
  if (is_empty() || node == nullptr) {
    throw std::logic_error("DoublyLinkedList::erase(): Invalid arguments");
  }

  if (node->prev != nullptr) {
    node->prev->next = node->next;
  }
  if (node->next != nullptr) {
    node->next->prev = node->prev;
  }

  if (node == _head) {
    _head = node->next;
  }
  if (node == _tail) {
    _tail = node->prev;
  }

  delete node;
}

template <class T>
inline typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin() {
  return Iterator(_head);
}

template <class T>
inline typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end() {
  return Iterator(nullptr);
}

template <class T>
inline typename DoublyLinkedList<T>::ReverseIterator
DoublyLinkedList<T>::rbegin() {
  return ReverseIterator(_tail);
}

template <class T>
inline typename DoublyLinkedList<T>::ReverseIterator
DoublyLinkedList<T>::rend() {
  return ReverseIterator(nullptr);
}


#endif  // !LIB_LIST_DOUBLYLINKEDLIST_H_