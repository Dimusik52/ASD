// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#include <gtest/gtest.h>
#include <iostream>
#include "../lib_algorithms/algorithms.h"
#include "../lib_matrix/matrix.h"

TEST(TestAlgorithmsLib_matrix_getlocalmin, LocalMin) {
  Matrix<int> matrix(3, 3);
  std::string input = "5 5 5\n5 1 5\n5 5 5\n";
  std::istringstream input_stream(input);
  input_stream >> matrix;

  int result = matrix_get_local_min(matrix);
  EXPECT_TRUE(result == 1 || result == 5);
}

TEST(TestAlgorithmsLib_matrix_getlocalmin, MultipleLocalMin) {
  Matrix<int> matrix(3, 3);
  std::string input = "3 1 2\n5 8 4\n7 6 9\n";
  std::istringstream input_stream(input);
  input_stream >> matrix;
  int result = matrix_get_local_min(matrix);
  EXPECT_TRUE(result == 1 || result == 6);
}

TEST(TestAlgorithmsLib_matrix_getlocalmin, SingleElement) {
  Matrix<int> matrix(1, 1);
  std::string input = "42\n";
  std::istringstream input_stream(input);
  input_stream >> matrix;

  EXPECT_EQ(matrix_get_local_min(matrix), 42);
}

TEST(TestAlgorithmsLib_matrix_getlocalmin, SmallMatrix2x2) {
  Matrix<int> matrix(2, 2);
  std::string input = "1 3\n2 4\n";
  std::istringstream input_stream(input);
  input_stream >> matrix;

  EXPECT_EQ(matrix_get_local_min(matrix), 1);
}

TEST(TestAlgorithmsLib_matrix_getlocalmin, AllElementsEqual) {
  Matrix<int> matrix(3, 3);
  std::string input = "5 5 5\n5 5 5\n5 5 5\n";
  std::istringstream input_stream(input);
  input_stream >> matrix;

  EXPECT_EQ(matrix_get_local_min(matrix), 5);
}

TEST(MatrixLocalMin, MultipleMins) {
  Matrix<int> matrix(5, 5);
  std::string input = "9 9 9 9 9\n9 3 2 4 9\n9 2 1 3 9\n9 5 2 4 9\n9 9 9 9 9\n";
  std::istringstream input_stream(input);
  input_stream >> matrix;
  int result = matrix_get_local_min(matrix);
  EXPECT_TRUE(result == 1 || result == 6);
}

TEST(CheckBracketsTest, EmptyString) { EXPECT_TRUE(check_brackets("")); }

TEST(CheckBracketsTest, SingleOpeningBracket) {
  EXPECT_FALSE(check_brackets("("));
  EXPECT_FALSE(check_brackets("{"));
  EXPECT_FALSE(check_brackets("["));
}

TEST(CheckBracketsTest, SingleClosingBracket) {
  EXPECT_FALSE(check_brackets(")"));
  EXPECT_FALSE(check_brackets("}"));
  EXPECT_FALSE(check_brackets("]"));
}

TEST(CheckBracketsTest, SimpleBalancedBrackets) {
  EXPECT_TRUE(check_brackets("()"));
  EXPECT_TRUE(check_brackets("{}"));
  EXPECT_TRUE(check_brackets("[]"));
}

TEST(CheckBracketsTest, MixedBalancedBrackets) {
  EXPECT_TRUE(check_brackets("()[]{}"));
  EXPECT_TRUE(check_brackets("({[]})"));
  EXPECT_TRUE(check_brackets("[{()}]"));
}

TEST(CheckBracketsTest, NestedBalancedBrackets) {
  EXPECT_TRUE(check_brackets("({[]})"));
  EXPECT_TRUE(check_brackets("[({})]"));
  EXPECT_TRUE(check_brackets("{([])}"));
}

TEST(CheckBracketsTest, SequentialBalancedBrackets) {
  EXPECT_TRUE(check_brackets("(){}[]"));
  EXPECT_TRUE(check_brackets("([]){}"));
  EXPECT_TRUE(check_brackets("{()}[{}]"));
}

TEST(CheckBracketsTest, UnbalancedMoreOpening) {
  EXPECT_FALSE(check_brackets("({"));
  EXPECT_FALSE(check_brackets("[{("));
  EXPECT_FALSE(check_brackets("({["));
}

TEST(CheckBracketsTest, UnbalancedMoreClosing) {
  EXPECT_FALSE(check_brackets(")}"));
  EXPECT_FALSE(check_brackets("])}"));
  EXPECT_FALSE(check_brackets("())"));
}

TEST(CheckBracketsTest, WrongOrderBrackets) {
  EXPECT_FALSE(check_brackets(")("));
  EXPECT_FALSE(check_brackets("}{"));
  EXPECT_FALSE(check_brackets("]["));
  EXPECT_FALSE(check_brackets("([)]"));
  EXPECT_FALSE(check_brackets("{(})"));
}

TEST(CheckBracketsTest, MixedWrongOrder) {
  EXPECT_FALSE(check_brackets("(]"));
  EXPECT_FALSE(check_brackets("[}"));
  EXPECT_FALSE(check_brackets("{)"));
  EXPECT_FALSE(check_brackets("([)]"));
  EXPECT_FALSE(check_brackets("{[}]"));
}

TEST(CheckBracketsTest, StringWithOtherCharacters) {
  EXPECT_TRUE(check_brackets("(abc)"));
  EXPECT_TRUE(check_brackets("a{b[c]d}e"));
  EXPECT_TRUE(check_brackets("hello (world) {test} [array]"));

  EXPECT_FALSE(check_brackets("(abc"));
  EXPECT_FALSE(check_brackets("abc]"));
  EXPECT_FALSE(check_brackets("a{b(c)d"));
}

TEST(CheckBracketsTest, EdgeCases) {
  EXPECT_TRUE(check_brackets("()"));
  EXPECT_TRUE(check_brackets("{}"));
  EXPECT_TRUE(check_brackets("[]"));
  EXPECT_FALSE(check_brackets("(}"));
  EXPECT_FALSE(check_brackets("[)"));
  EXPECT_FALSE(check_brackets("{)"));
}

TEST(CheckBracketsTest, OnlyOneTypeOfBracket) {
  EXPECT_TRUE(check_brackets("((()))"));
  EXPECT_TRUE(check_brackets("{{{}}}"));
  EXPECT_TRUE(check_brackets("[[[]]]"));

  EXPECT_FALSE(check_brackets("((())"));
  EXPECT_FALSE(check_brackets("{{}}}"));
  EXPECT_FALSE(check_brackets("[[[]]"));
}

TEST(CheckBracketsTest, RealExamples) {
  EXPECT_TRUE(check_brackets("f(x) = [(x + 1) * {x - 2}]"));
}