// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#ifndef LIB_MATHVECTOR_MATHVECTORX_H_
#define LIB_MATHVECTOR_MATHVECTORX_H_

#include <iostream>
#include "../lib_TVector/include/TVector.h"

template <typename T>
class MathVector : public TVector<T> {

 public:
  MathVector();
  explicit MathVector(size_t m);
  MathVector(const MathVector<T>&);
  MathVector(std::initializer_list<T> init_list);
  MathVector(const TVector<T>&);

  ~MathVector();

  MathVector<T> operator+(const MathVector<T>&) const;
  MathVector<T> operator-(const MathVector<T>&) const;
  MathVector<T> operator*(const T) const;
  MathVector<T>& operator+=(const MathVector<T>&);
  MathVector<T>& operator-=(const MathVector<T>&);
  MathVector<T>& operator*=(const T);
  T operator*(const MathVector<T>&) const;

  friend std::ostream& operator<<(std::ostream& os, const MathVector<T>& data) {
    os << "[";
    for (size_t i = 0; i < data.size(); ++i) {
      os << data[i];
      if (i < data.size() - 1) os << " ";
    }
    os << "]";
    return os;
  }
  friend std::istream& operator>>(std::istream& is, MathVector<T>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
      if (!(is >> data[i])) {
        throw std::runtime_error("Invalid input for vector element");
      }
    }
    return is;
  }

 private:
};

template <typename T>
MathVector<T>::MathVector() {}

template <typename T>
MathVector<T>::MathVector(size_t m) {
  this->resize(m, false);
  for (size_t i = 0; i < m; i++) {
    (*this)[i] = T();
  }
}

template <class T>
MathVector<T>::MathVector(const MathVector<T>& other) : TVector<T>(other) {

}

template <typename T>
MathVector<T>::MathVector(std::initializer_list<T> init_list) {
  this->reserve(init_list.size());
  for (const auto& element : init_list) {
    this->push_back(element);
  }
}

template <class T>
MathVector<T>::MathVector(const TVector<T>& other) : TVector<T>(other) {

}

template <typename T>
MathVector<T>::~MathVector() {

}

template <class T>
MathVector<T> MathVector<T>::operator+(const MathVector<T>& other) const {
  if (this->size() != other.size()) {
    throw std::logic_error(
        "MathVector.operator+: vectors must be the same size");
  }
  MathVector<T> result(this->size());
  for (size_t i = 0; i < this->size(); i++) {
    result[i] = (*this)[i] + other[i];
  }
  return result;
}

template <class T>
MathVector<T> MathVector<T>::operator-(const MathVector<T>& other) const {
  if (this->size() != other.size()) {
    throw std::logic_error(
        "MathVector.operator-: vectors Must be the same size");
  }
  MathVector<T> result(this->size());
  for (size_t i = 0; i < this->size(); i++) {
    result[i] = (*this)[i] - other[i];
  }
  return result;
}

template <class T>
MathVector<T> MathVector<T>::operator*(const T val) const {
  MathVector<T> result(this->size());
  for (size_t i = 0; i < this->size(); i++) {
    result[i] = (*this)[i] * val;
  }
  return result;
}

template <class T>
MathVector<T>& MathVector<T>::operator+=(const MathVector<T>& other) {
  if (this->size() != other.size()) {
    throw std::logic_error(
        "MathVector.operator+=: vectors Must be the same size");
  }
  for (size_t i = 0; i < this->size(); i++) {
    (*this)[i] += other[i];
  }
  return *this;
}

template <class T>
MathVector<T>& MathVector<T>::operator-=(const MathVector<T>& other) {
  if (this->size() != other.size()) {
    throw std::logic_error(
        "MathVector.operator-=: vectors Must be the same size");
  }
  for (size_t i = 0; i < this->size(); i++) {
    (*this)[i] -= other[i];
  }
  return *this;
}

template <class T>
MathVector<T>& MathVector<T>::operator*=(const T val) {
  for (size_t i = 0; i < this->size(); i++) {
    (*this)[i] *= val;
  }
  return *this;
}

template <class T>
T MathVector<T>::operator*(const MathVector<T>& other) const {
  if (this->size() != other.size()) {
    throw std::logic_error(
        "MathVector.operator*: vectors Must be the same size");
  }

  T result = T();
  for (size_t i = 0; i < this->size(); i++) {
    result += (*this)[i] * other[i];
  }
  return result;
}

#endif  // LIB_MATHVECTOR_MATHVECTORX_H_