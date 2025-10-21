// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#ifndef LIB_ALGORITHMS_ALGORITHMS_H_
#define LIB_ALGORITHMS_ALGORITHMS_H_

#include <iostream>
#include "../lib_matrix/matrix.h"
#include "../lib_stack/stack.h"

template <typename T>
int matrix_get_local_min(Matrix<T> matrix) {
  std::srand(time(0));
  int random_pos_1 = std::rand() % matrix.get_rows();
  int random_pos_2 = std::rand() % matrix.get_rows();
  int result = matrix[random_pos_1][random_pos_2];
  bool continue_flag = true;
  while (continue_flag) {
    continue_flag = false;
    int min_i = random_pos_1;
    int min_j = random_pos_2;
    int min_val;
    if (random_pos_1 > 0) {
      if (matrix[random_pos_1 - 1][random_pos_2] < result) {
        min_val = matrix[random_pos_1 - 1][random_pos_2];
        continue_flag = true;
        min_i = random_pos_1 - 1;
        min_j = random_pos_2;
      }
    }
    if (random_pos_2 < matrix.get_rows() - 1) {
      if (matrix[random_pos_1][random_pos_2 + 1] < result) {
        min_val = matrix[random_pos_1][random_pos_2 + 1];
        continue_flag = true;
        min_i = random_pos_1;
        min_j = random_pos_2 + 1;
      }
    }
    if (random_pos_1 < matrix.get_cols() - 1) {
      if (matrix[random_pos_1 + 1][random_pos_2] < result) {
        min_val = matrix[random_pos_1 + 1][random_pos_2];
        continue_flag = true;
        min_i = random_pos_1 + 1;
        min_j = random_pos_2;
      }
    }
    if (random_pos_2 > 0) {
      if (matrix[random_pos_1][random_pos_2 - 1] < result) {
        min_val = matrix[random_pos_1][random_pos_2 - 1];
        continue_flag = true;
        min_i = random_pos_1;
        min_j = random_pos_2 - 1;
      }
    }
    if (continue_flag) {
      result = min_val;
      random_pos_1 = min_i;
      random_pos_2 = min_j;
    }
  }

  return result;
}

bool check_brackets(std::string str) {
  Stack<char> brackets(str.size());
  for (const auto& c : str) {
    if (c == '(' || c == '[' || c == '{') {
      brackets.push(c);
    } else if (c == ')' || c == ']' || c == '}') {
      if (brackets.is_empty()) {
        return false;
      }
      char top = brackets.top();
      if ((c == ')' && top != '(') || (c == ']' && top != '[') ||
          (c == '}' && top != '{')) {
        return false;
      }
      brackets.pop();
    }
  }
  if (brackets.is_empty()) {
    return true;
  }
  return false;
}

#endif  // LIB_ALGORITHMS_ALGORITHMS_H_