// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#ifndef LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_
#define LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_

#include <iostream>

#include "../lib_matrix/matrix.h"

template <typename T>
class TriangleMatrix;
template <typename T>
std::ostream& operator<<(std::ostream& os, const TriangleMatrix<T>& matrix);
template <typename T>
std::istream& operator>>(std::istream& is, const TriangleMatrix<T>& matrix);

template <typename T>
class TriangleMatrix : public Matrix<T> {
 private:
  size_t _rows;
  size_t _cols;
  bool _is_upper;

 public:
  TriangleMatrix();
  TriangleMatrix(size_t rows, size_t cols, bool is_upper = true);
  explicit TriangleMatrix(Matrix<T>& matrix, bool is_upper = true);
  TriangleMatrix(std::initializer_list<T> init_list, bool is_upper = true);
  ~TriangleMatrix();

  bool is_upper() const { return _is_upper; }
  size_t get_rows() const { return _rows; }
  size_t get_cols() const { return _cols; }

  TriangleMatrix<T> operator+(TriangleMatrix<T>& tr_matrix);
  TriangleMatrix<T> operator-(TriangleMatrix<T>& tr_matrix);
  TriangleMatrix<T> operator*(TriangleMatrix<T>& tr_matrix);

  friend std::ostream& operator<< <T>(std::ostream& os,
                                  const TriangleMatrix<T>& matrix);
  friend std::istream& operator>> <T>(std::istream& is,
                                  const TriangleMatrix<T>& matrix);

  void make_triangular(bool fill_with_zeros = true);

 private:
  void initialize_triangular(bool is_upper);
};

template <typename T>
TriangleMatrix<T>::TriangleMatrix() : _rows(0), _cols(0), _is_upper(true) {
  ;
}
template <typename T>
TriangleMatrix<T>::TriangleMatrix(size_t rows, size_t cols,
                                  bool is_upper = true)
    : _rows(rows), _cols(cols), _is_upper(is_upper) {
  Matrix<T>::resize(rows, false);
  for (size_t i = 0; i < rows; i++) {
    (*this)[i] = MathVector<T>(cols);
  }
  initialize_triangular(is_upper);
}

template <typename T>
TriangleMatrix<T>::TriangleMatrix(Matrix<T>& matrix, bool is_upper = true)
    : Matrix<T>(matrix),
      _rows(matrix.get_rows()),
      _cols(matrix.get_cols()),
      _is_upper(is_upper) {
  make_triangular(false);
}

template <typename T>
TriangleMatrix<T>::TriangleMatrix(std::initializer_list<T> init_list,
                                  bool is_upper = true)
    : _is_upper(is_upper) {
  _rows = init_list.size();
  _cols = (_rows > 0) ? init_list.begin()->size() : 0;

  for (const auto& row : init_list) {
    if (row.size() != _cols) {
      throw std::logic_error(
          "All rows must have the same size in initializer list");
    }
  }
  Matrix<T>::resize(_rows, false);
  size_t i = 0;

  for (const auto& row_list : init_list) {
    (*this)[i] = MathVector<T>(_cols);
    size_t j = 0;
    for (const auto& element : row_list) {
      (*this)[i][j] = element;
      j++;
    }
    i++;
  }
  make_triangular();
}

template <typename T>
TriangleMatrix<T>::~TriangleMatrix() {
  ;
}

template <typename T>
void TriangleMatrix<T>::initialize_triangular(bool is_upper) {
  if (is_upper) {
    for (size_t i = 0; i < _rows; i++) {
      for (size_t j = 0; j < i && j < _cols; j++) {
        (*this)[i][j] = T(0);
      }
    }
  } else {
    for (size_t i = 0; i < _rows; i++) {
      for (size_t j = i + 1; j < _cols; j++) {
        (*this)[i][j] = T(0);
      }
    }
  }
}

template <typename T>
void TriangleMatrix<T>::make_triangular(bool fill_with_zeros) {
  if (fill_with_zeros) {
    initialize_triangular(_is_upper);
  }
}

template <typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator+(TriangleMatrix<T>& tr_matrix) {
  if (_rows != tr_matrix._rows || _cols != tr_matrix._cols ||
      _is_upper != tr_matrix._is_upper) {
    throw std::logic_error("TriangleMatrix.operator+: Incopatible matrices!");
  }
  TriangleMatrix<T> result(_rows, _cols, _is_upper);

  if (_is_upper) {
    for (size_t i = 0; i < _rows; i++) {
      for (size_t j = i; j < _cols; j++) {
        result[i][j] = (*this)[i][j] + tr_matrix[i][j];
      }
    }
  } else {
    for (size_t i = 0; i < _rows; i++) {
      for (size_t j = 0; j <= i && j < _cols; j++) {
        result[i][j] = (*this)[i][j] + tr_matrix[i][j];
      }
    }
  }

  return result;
}

template <typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator-(TriangleMatrix<T>& tr_matrix) {
  if (_rows != tr_matrix._rows || _cols != tr_matrix._cols ||
      _is_upper != tr_matrix._is_upper) {
    throw std::logic_error("TriangleMatrix.operator-: Incopatible matrices!");
  }
  TriangleMatrix<T> result(_rows, _cols, _is_upper);

  if (_is_upper) {
    for (size_t i = 0; i < _rows; i++) {
      for (size_t j = i; j < _cols; j++) {
        result[i][j] = (*this)[i][j] - tr_matrix[i][j];
      }
    }
  } else {
    for (size_t i = 0; i < _rows; i++) {
      for (size_t j = 0; j <= i && j < _cols; j++) {
        result[i][j] = (*this)[i][j] - tr_matrix[i][j];
      }
    }
  }

  return result;
}

template <typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(TriangleMatrix<T>& tr_matrix) {
  if (_cols != tr_matrix._rows) {
    throw std::logic_error(
        "TriangleMatrix.operator*: Incompatible dimensions!");
  }

  TriangleMatrix<T> result(_rows, tr_matrix._cols,
                           _is_upper && tr_matrix._is_upper);

  for (size_t i = 0; i < _rows; i++) {
    for (size_t j = 0; j < tr_matrix._cols; j++) {
      T sum = T(0);

      size_t k_start, k_end;

      if (_is_upper && tr_matrix._is_upper) {
        k_start = std::max(i, size_t(0));
        k_end = std::min(_cols, j + 1);
      } else if (!_is_upper && !tr_matrix._is_upper) {
        k_start = j;
        k_end = std::min(i + 1, _cols);
      } else if (_is_upper && !tr_matrix._is_upper) {
        k_start = std::max(i, j);
        k_end = _cols;
      } else {

        k_start = 0;
        k_end = std::min(i + 1, j + 1);
      }

      for (size_t k = k_start; k < k_end; k++) {
        sum += (*this)[i][k] * tr_matrix[k][j];
      }

      result[i][j] = sum;
    }
  }

  return result;
}

template <typename T>
std::ostream& operator<< <T>(std::ostream& os, const TriangleMatrix<T>& matrix) {
  for (size_t i = 0; i < matrix._rows; ++i) {
    os << "[ ";
    for (size_t j = 0; j < matrix._cols; ++j) {
      os << matrix[i][j];
      if (j < matrix._cols - 1) {
        os << ", ";
      }
    }
    os << " ]";
    if (i < matrix._rows - 1) {
      os << "\n";
    }
  }
  return os;
}

template <typename T>
std::istream& operator>>
    <T>(std::istream& is, const TriangleMatrix<T>& matrix) {
  for (size_t i = 0; i < matrix._rows; ++i) {
    for (size_t j = 0; j < matrix._cols; ++j) {
      T value;
      is >> value;

      if (matrix._is_upper) {
        if (j < i && value != T(0)) {
          std::cout
              << "Warning: Element at (" << i << "," << j
              << ") should be 0 for upper triangular matrix. Setting to 0.\n";
          matrix[i][j] = T(0);
        } else {
          matrix[i][j] = value;
        }
      } else {
        if (j > i && value != T(0)) {
          std::cout
              << "Warning: Element at (" << i << "," << j
              << ") should be 0 for lower triangular matrix. Setting to 0.\n";
          matrix[i][j] = T(0);
        } else {
          matrix[i][j] = value;
        }
      }
    }
  }
  return is;
}

#endif  // !LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_
