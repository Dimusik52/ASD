// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#ifndef LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_
#define LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_

#include <iostream>

#include "../lib_matrix/matrix.h"

template <typename T>
class TriangleMatrix : public Matrix<T> {
 private:
  size_t _dimension;

 public:
  explicit TriangleMatrix(size_t dimension = 0);
  TriangleMatrix(size_t dimension, const T* data, size_t data_size);
  TriangleMatrix(const TriangleMatrix<T>& other) = default;
  ~TriangleMatrix() = default;

  inline size_t get_dimension() const { return _dimension; }

  T& at(size_t row, size_t col);
  const T& at(size_t row, size_t col) const;

  TriangleMatrix<T>& operator+=(const TriangleMatrix<T>& other);
  TriangleMatrix<T>& operator-=(const TriangleMatrix<T>& other);
  TriangleMatrix<T>& operator*=(T val);

  TriangleMatrix<T> operator+(const TriangleMatrix<T>& other) const;
  TriangleMatrix<T> operator-(const TriangleMatrix<T>& other) const;
  TriangleMatrix<T> operator*(T val) const;
  TriangleMatrix<T> operator*(const TriangleMatrix<T>& other) const;

  TriangleMatrix<T>& operator=(const TriangleMatrix<T>& other);

  bool operator==(const TriangleMatrix<T>& other) const;
  bool operator!=(const TriangleMatrix<T>& other) const;

  friend std::ostream& operator<<(std::ostream& os, const TriangleMatrix<T>& matrix) {
    for (size_t i = 0; i < matrix._dimension; i++) {
      for (size_t j = 0; j < matrix._dimension; j++) {
        if (j < i) {
          os << "0";
        } else {
          os << matrix.at(i, j);
        }
        if (j < matrix._dimension - 1) {
          os << " ";
        }
      }
      if (i < matrix._dimension - 1) {
        os << "\n";
      }
    }
    return os;
  }

  friend std::istream& operator>>(std::istream& is, TriangleMatrix<T>& matrix) {
    for (size_t i = 0; i < matrix._dimension; i++) {
      for (size_t j = i; j < matrix._dimension; j++) {
        T value;
        is >> value;
        matrix.at(i, j) = value;
      }

      for (size_t j = 0; j < i; j++) {
        T dummy;
        is >> dummy;
      }
    }
    return is;
  }
};

template <typename T>
TriangleMatrix<T>::TriangleMatrix(size_t dimension)
    : Matrix<T>(dimension, dimension), _dimension(dimension) {
  for (size_t i = 0; i < dimension; i++) {
    (*this)[i] = MathVector<T>(dimension - i);
  }
}

template <typename T>
TriangleMatrix<T>::TriangleMatrix(size_t dimension, const T* data,
                                  size_t data_size)
    : Matrix<T>(dimension, dimension), _dimension(dimension) {
  if (!data) {
    throw std::invalid_argument("Data pointer cannot be null");
  }

  size_t required_size = dimension * (dimension + 1) / 2;
  if (data_size < required_size) {
    throw std::invalid_argument("Data array too small");
  }

  for (size_t i = 0; i < dimension; i++) {
    (*this)[i] = MathVector<T>(dimension - i);
    for (size_t j = i; j < dimension; j++) {
      size_t linear_index = i * dimension + j - (i * (i + 1) / 2);
      (*this)[i][j - i] = data[linear_index];
    }
  }
}

template <typename T>
T& TriangleMatrix<T>::at(size_t row, size_t col) {
  if (row >= _dimension || col >= _dimension) {
    throw std::out_of_range("Index out of range");
  }
  if (col < row) {
    throw std::logic_error("Access to zero element in upper triangular matrix");
  }
  return (*this)[row][col - row];
}

template <typename T>
const T& TriangleMatrix<T>::at(size_t row, size_t col) const {
  if (row >= _dimension || col >= _dimension) {
    throw std::out_of_range("Index out of range");
  }
  if (col < row) {
    static const T zero = T();
    return zero;
  }
  return (*this)[row][col - row];
}

template <typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator+=(
    const TriangleMatrix<T>& other) {
  if (_dimension != other._dimension) {
    throw std::logic_error("Triangle matrices must have equal dimensions");
  }
  Matrix<T>::operator+=(other);
  return *this;
}

template <typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator-=(
    const TriangleMatrix<T>& other) {
  if (_dimension != other._dimension) {
    throw std::logic_error("Triangle matrices must have equal dimensions");
  }
  Matrix<T>::operator-=(other);
  return *this;
}

template <typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator*=(T val) {
  Matrix<T>::operator*=(val);
  return *this;
}

template <typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator+(
    const TriangleMatrix<T>& other) const {
  TriangleMatrix<T> result = *this;
  result += other;
  return result;
}

template <typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator-(
    const TriangleMatrix<T>& other) const {
  TriangleMatrix<T> result = *this;
  result -= other;
  return result;
}

template <typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(T val) const {
  TriangleMatrix<T> result = *this;
  result *= val;
  return result;
}

template <typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(
    const TriangleMatrix<T>& other) const {
  if (_dimension != other._dimension) {
    throw std::logic_error("Triangle matrices must have same dimension");
  }

  TriangleMatrix<T> result(_dimension);

  for (size_t i = 0; i < _dimension; i++) {
    for (size_t j = i; j < _dimension; j++) {
      T sum = T();
      for (size_t k = i; k <= j; k++) {
        sum += this->at(i, k) * other.at(k, j);
      }
      result.at(i, j) = sum;
    }
  }

  return result;
}

template <typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator=(
    const TriangleMatrix<T>& other) {
  if (this != &other) {
    Matrix<T>::operator=(other);
    _dimension = other._dimension;
  }
  return *this;
}

template <typename T>
bool TriangleMatrix<T>::operator==(const TriangleMatrix<T>& other) const {
  if (_dimension != other._dimension) {
    return false;
  }
  return Matrix<T>::operator==(other);
}

template <typename T>
bool TriangleMatrix<T>::operator!=(const TriangleMatrix<T>& other) const {
  return !(*this == other);
}

#endif  // !LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_
