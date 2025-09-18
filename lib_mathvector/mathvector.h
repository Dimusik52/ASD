
#ifndef LIB_MATHVECTOR_MATHVECTORX_H_
#define LIB_MATHVECTOR_MATHVECTORX_H_

#include <iostream>
#include "../lib_TVector/TVector.h"

template <typename T>
class MathVector : private TVector<T> {
 private:
  size_t _m;
  TVector<T> data;

 public:
  MathVector();
  MathVector(size_t m);
  ~MathVector();

  MathVector<T> operator*(T& val);
  T operator*(MathVector<T>& vec);

  friend std::ostream& operator<<(std::ostream& os, const MathVector<T>& data) {
    return os;
  }
  friend std::istream& operator>>(std::istream& is, const MathVector<T>& data) {
    return is;
  }

 private:
};

template <typename T>
MathVector<T>::MathVector() : TVector<T>() {
  ;
}

template <typename T>
MathVector<T>::~MathVector() {
  ;
}
template <typename T>
MathVector<T>::MathVector(size_t m) : _m(m) {
  ;
}

template <typename T>
MathVector<T> MathVector<T>::operator*(T& val) {
  MathVector<T> result(size);
  //for (size_t i = 0; i < _size; ++i) {
  //  result[i] = (*this)[i] * val;
  //}
  //return result;
  return *this;
}
template <typename T>
T MathVector<T>::operator*(MathVector<T>& vec) {
  //T result = T();
  //for (int i = 0; i < _size; i++) {
  //  result += (*this)[i] * vec[i];
  //}
  //return result;
  return T();
}

//template <typename T>
//std::ostream& operator<<(std::ostream& os, const MathVector<T>& data) {
//  return os;
//}
//
//template <typename T>
//std::istream& operator>>(std::istream& os, const MathVector<T>& data) {
//  return is;
//}

#endif  // LIB_MATHVECTOR_MATHVECTORX_H_