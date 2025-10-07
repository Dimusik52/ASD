// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#ifndef LIB_MATRIX_MATRIX_H_
#define LIB_MATRIX_MATRIX_H_

#include <iostream>

#include "../lib_mathvector/mathvector.h"

template <typename T>
class Matrix : public MathVector<MathVector<T>> {
 private:
  size_t _rows;
  size_t _cols;

 public:
  Matrix();
  Matrix(size_t, size_t);
  Matrix(const MathVector<MathVector<T>>&);
  Matrix(const Matrix&);

  ~Matrix();

  int get_rows() const;
  int get_cols() const;

  T& at(int, int);
  MathVector<T>& operator[](int);
  const MathVector<T>& operator[](int) const;

  Matrix<T> operator+(const Matrix& other);
  Matrix<T> operator-(const Matrix& other);

  Matrix<T> operator*(const T val);
  MathVector<T> operator*(const MathVector<T>& vec);

  Matrix<T> operator*(const Matrix<T>& other);

  friend MathVector<T> operator*(const MathVector<T>& vector,
                          const Matrix<T>& matrix) {
    if (vector.size() != matrix.size()) {
      throw std::invalid_argument("Vector size must equal matrix row count");
    }

    MathVector<T> result(matrix[0].size());
    for (int i = 0; i < result.size(); ++i) {
      result[i] = T(0);
    }

    for (int j = 0; j < matrix[0].size(); ++j) {
      for (int i = 0; i < vector.size(); ++i) {
        result[j] += vector[i] * matrix[i][j];
      }
    }

    return result;
  }

  Matrix<T> transpose();
  Matrix<T>& operator=(const Matrix<T>& other);

  friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
    if (matrix.is_empty()) {
      os << "Empty matrix";
      return os;
    }

    for (int i = 0; i < matrix.size(); ++i) {
      os << "[ ";
      for (int j = 0; j < matrix[i].size(); ++j) {
        os << matrix[i][j];
        if (j < matrix[i].size() - 1) {
          os << " ";
        }
      }
      os << " ]";
      if (i < matrix.size() - 1) {
        os << "\n";
      }
    }
    return os;
  }
  friend std::istream& operator>>(std::istream& is, Matrix<T>& matrix) {
    for (int i = 0; i < matrix.size(); ++i) {
      for (int j = 0; j < matrix[i].size(); ++j) {
        is >> matrix[i][j];
      }
    }
    return is;
  }

 private:
};

template <typename T>
Matrix<T>::Matrix() : _rows(0), _cols(0) {}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) : _rows(rows), _cols(cols) {
  for (size_t i = 0; i < rows; i++) {
    this->push_back(MathVector<T>(cols));
  }
}

template <typename T>
Matrix<T>::Matrix(const MathVector<MathVector<T>>& vectors)
    : MathVector<MathVector<T>>(vectors) {
  if (!this->is_empty()) {
    size_t expected_size = (*this)[0].size();
    for (size_t i = 1; i < this->size(); ++i) {
      if ((*this)[i].size() != expected_size) {
        throw std::invalid_argument("All vectors must have the same size");
      }
    }
    _rows = this->size();
    _cols = expected_size;
  } else {
    _rows = 0;
    _cols = 0;
  }
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other) : MathVector<MathVector<T>>(other) {
  _rows = other._rows;
  _cols = other._cols;
}

template <typename T>
Matrix<T>::~Matrix() {
  ;
}

template <class T>
int Matrix<T>::get_rows() const {
  return _rows;
}

template <class T>
int Matrix<T>::get_cols() const {
  return _cols;
}

template <class T>
T& Matrix<T>::at(int row, int col) {
  if (row < 0 || row >= _rows || col < 0 || col >= _cols) {
    throw std::out_of_range("Matrix.at: Index out of range");
  }
  return (*this)[row][col];
}

template <class T>
MathVector<T>& Matrix<T>::operator[](int row) {
  return TVector<MathVector<T>>::operator[](
      row);
}

template <class T>
const MathVector<T>& Matrix<T>::operator[](int row) const {
  return TVector<MathVector<T>>::operator[](
      row);
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) {
  if (_rows != other._rows || _cols != other._cols) {
    throw std::logic_error(
        "Matrix.operator+: Matrices must have same dimensions");
  }

  Matrix<T> result(_rows, _cols);
  for (int i = 0; i < _rows; i++) {
    result[i] = (*this)[i] + other[i];
  }
  return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) {
  if (_rows != other._rows || _cols != other._cols) {
    throw std::logic_error(
        "Matrix.operator-: Matrices must have same dimensions");
  }

  Matrix<T> result(_rows, _cols);
  for (int i = 0; i < _rows; i++) {
    result[i] = (*this)[i] - other[i];
  }
  return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T val) {
  Matrix<T> result(_rows, _cols);
  for (int i = 0; i < _rows; i++) {
    result[i] = (*this)[i] * val;
  }
  return result;
}

template <typename T>
MathVector<T> Matrix<T>::operator*(const MathVector<T>& vec) {
  if (_cols != vec.size()) {
    throw std::logic_error(
        "Matrix.operator*: Incompatible dimensions for matrix-vector "
        "multiplication");
  }

  MathVector<T> result(_rows);
  for (int i = 0; i < _rows; i++) {
    T sum = T();
    for (int j = 0; j < _cols; j++) {
      sum += (*this)[i][j] * vec[j];
    }
    result[i] = sum;
  }
  return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(
    const Matrix<T>& other) {
  if (_cols != other._rows) {
    throw std::logic_error(
        "Matrix::operator*: Incompatible dimensions for multiplication");
  }

  Matrix<T> result(_rows, other._cols);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < other._cols; j++) {
      T sum = T();
      for (int k = 0; k < _cols; k++) {
        sum += (*this)[i][k] * other[k][j];
      }
      result[i][j] = sum;
    }
  }
  return result;
}


template <class T>
Matrix<T> Matrix<T>::transpose() {
  Matrix<T> result(_cols, _rows);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      result[j][i] = (*this)[i][j];
    }
  }
  return result;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
  if (this != &other) {
    MathVector<MathVector<T>>::operator=(other);
    _rows = other._rows;
    _cols = other._cols;
  }
  return *this;
}

#endif  // LIB_MATRIX_MATRIX_H_