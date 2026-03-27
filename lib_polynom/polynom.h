// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2

#ifndef LIB_POLYNOM_POLYNOM_H_
#define LIB_POLYNOM_POLYNOM_H_

#include <iostream>
#include "../lib_doublylinkedlist/doublylinkedlist.h"
#include "../lib_monom/monom.h"

class Polynom {
  DoublyLinkedList<Monom> polynom;

 public:
  bool isEmpty() const { return polynom.is_empty(); }
  size_t size() const;

  DoublyLinkedList<Monom>::Iterator begin() { return polynom.begin(); }
  DoublyLinkedList<Monom>::Iterator end() { return polynom.end(); }
  DoublyLinkedList<Monom>::ConstIterator begin() const {
    return polynom.begin();
  }
  DoublyLinkedList<Monom>::ConstIterator end() const { return polynom.end(); }

  Polynom();
  Polynom(const Polynom& other);
  Polynom(std::string expression);

  bool lexGreater(const Monom& a, const Monom& b);
  void addMonomSorted(const Monom& m);
  Polynom parse(const std::string& s);

  Polynom& operator=(const Polynom& other);
  Polynom operator+(const Monom& other);
  Polynom operator-(const Monom& other);
  Polynom operator*(const Monom& other);

  Polynom operator+(const Polynom& other);
  Polynom operator-(const Polynom& other);
  Polynom operator*(const Polynom& other);

  friend std::ostream& operator<<(std::ostream& ostr, const Polynom& p);
};

#endif  // LIB_POLYNOM_POLYNOM_H_