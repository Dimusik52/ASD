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

template <size_t N>
bool is_in(char ch, char (&chars)[N]) {
  bool result = false;
  for (const auto& c : chars) {
    if (c == ch) {
      result = true;
      break;
    }
  }
  return result;
}

void read_expression(std::string expression) {
  Stack<char> operations_stack(expression.size());
  Stack<char> brackets_stack(expression.size());
  char operations[5] = {'+', '-', '/', '*', '^'};
  char brackets_open[3] = {'(', '[', '{'};
  char brackets_close[3] = {')', ']', '}'};
  char numbers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

  char previous_char = ' ';

  for (const auto& c : expression) {
    if (c == ' ') continue;
    if (!is_in(previous_char, operations) &&
        (!is_in(previous_char, brackets_open) &&
         !is_in(previous_char, brackets_close))) { // prev = val
      if (is_in(c, operations)) {
        ;
      } else if (is_in(c, brackets_close)) {
        if (is_in(brackets_stack.top(), brackets_close))
          throw std::logic_error("Missing open bracket");
        brackets_stack.pop();
      } else if (is_in(c, numbers)) {
        ;
      } else {
        throw std::logic_error("Missing operation or close bracket");
      }
    } else if (is_in(previous_char, operations)) { // prev = op
      if (is_in(c, brackets_open)) {
        brackets_stack.push(c);
      } else if (!is_in(c, operations) &&
                 (!is_in(c, brackets_open) &&
                  !is_in(c, brackets_close)))
        ;
      else {
        throw std::logic_error("Missing value or open bracket");
      }
    } else if (is_in(previous_char, brackets_open)) { // prev =  (
      if (!is_in(c, operations) &&
          (!is_in(c, brackets_open) &&
           !is_in(c, brackets_close))) {
        ;
      } else {
        throw std::logic_error("Missing a value");
      }
    } else if (is_in(previous_char, brackets_close)) { // prev = )
      if (is_in(c, operations)) {
        ;
      } else if (is_in(c, brackets_close)) {
        if (brackets_stack.is_empty()) {
          throw std::logic_error("Missing a open bracket");
        } else {
          brackets_stack.pop();
        }
      } 
      else if (!is_in(c, operations)) {
        throw std::logic_error("Missing an operation");
      } 
    }
    previous_char = c;
  }
}

#endif  // LIB_ALGORITHMS_ALGORITHMS_H_