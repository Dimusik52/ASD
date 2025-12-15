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

//TEST(TestAlgorithmsLib_matrix_getlocalmin, MultipleLocalMin) {
//  Matrix<int> matrix(3, 3);
//  std::string input = "3 1 2\n5 8 4\n7 6 9\n";
//  std::istringstream input_stream(input);
//  input_stream >> matrix;
//  int result = matrix_get_local_min(matrix);
//  EXPECT_TRUE(result == 1 || result == 6);
//}

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

TEST(CheckLoopsTest, TurtleRabbitNoLoop) { 
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  EXPECT_FALSE(is_looped(list));
}

TEST(CheckLoopsTest, TurtleRabbitLoop) { 
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  
  auto last = list.begin();
  auto temp = list.begin();
  while (++temp != list.end()) {
    ++last;
  }

  auto second = list.begin();
  ++second;

  auto original_next = last.get_node()->next;

  last.get_node()->next =
      second.get_node();
  
  EXPECT_TRUE(is_looped(list));
  last.get_node()->next = original_next;
}

TEST(CheckLoopsTest, TurtleRabbitLoopSingle) {
  List<int> list;
  list.push_back(1);

  auto only = list.begin();
  only.get_node()->next = only.get_node();

  EXPECT_TRUE(is_looped(list));

  only.get_node()->next = nullptr;
}

TEST(IsLoopedReverseTest, EmptyList) {
  List<int> list;
  bool result = is_looped_reverse(list);
  EXPECT_FALSE(result);
}

TEST(FindLoopTest, EmptyList) {
  List<int> list;

  auto result = find_loop(list);
  EXPECT_EQ(result, nullptr);
}

TEST(FindLoopTest, NoLoop) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  auto result = find_loop(list);
  EXPECT_EQ(result, nullptr);
}

TEST(FindLoopTest, SingleElementNoLoop) {
  List<int> list;
  list.push_back(42);

  auto result = find_loop(list);
  EXPECT_EQ(result, nullptr);
}

TEST(FindLoopTest, SingleElementLoop) {
  List<int> list;
  list.push_back(42);

  auto it = list.begin();
  auto node = it.get_node();
  if (node) {
    node->next = node;  // создаем цикл

    auto result = find_loop(list);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result, node);

    // Восстанавливаем
    node->next = nullptr;
  }
}

TEST(FindLoopTest, TwoElementLoop) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);

  // Создаем цикл: 1 → 2 → 1
  auto it1 = list.begin();
  auto it2 = list.begin();
  ++it2;

  auto node1 = it1.get_node();
  auto node2 = it2.get_node();

  if (node1 && node2) {
    node2->next = node1;  // создаем цикл

    auto result = find_loop(list);
    EXPECT_NE(result, nullptr);

    // Восстанавливаем
    node2->next = nullptr;
  }
}

TEST(FindLoopTest, LoopInMiddle) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.push_back(5);

  // Создаем цикл: 3 → 4 → 5 → 3
  auto it = list.begin();
  auto node1 = it.get_node();  // 1
  ++it;
  node1 = it.get_node();  // 2
  ++it;
  auto node3 = it.get_node();  // 3
  ++it;
  auto node4 = it.get_node();  // 4
  ++it;
  auto node5 = it.get_node();  // 5

  if (node5) {
    node5->next = node3;  // 5 → 3, создаем цикл

    auto result = find_loop(list);
    EXPECT_NE(result, nullptr);

    // Восстанавливаем
    node5->next = nullptr;
  }
}

TEST(FindLoopTest, FullCycle) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Создаем цикл: 1 → 2 → 3 → 1
  auto it = list.begin();
  auto node1 = it.get_node();
  ++it;
  auto node2 = it.get_node();
  ++it;
  auto node3 = it.get_node();

  if (node3) {
    node3->next = node1;  // 3 → 1

    auto result = find_loop(list);
    EXPECT_NE(result, nullptr);

    // Восстанавливаем
    node3->next = nullptr;
  }
}

TEST(FindLoopTest, IteratorStillWorks) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  auto result = find_loop(list);
  EXPECT_EQ(result, nullptr);

  std::vector<int> values;
  for (int val : list) {
    values.push_back(val);
  }
  EXPECT_EQ(values, std::vector<int>({1, 2, 3}));
}


TEST(FindLoopTest, LoopInMiddleLarge) {
  List<int> list;
  for (int i = 1; i <= 10; i++) {
    list.push_back(i);
  }

  auto it_start = list.begin();
  auto it_cycle_start = list.begin();
  auto it_end = list.begin();

  it_cycle_start += 4;
  it_end += 9;

  auto* node_cycle_start = it_cycle_start.get_node();
  auto* node_end = it_end.get_node();

  if (node_end && node_cycle_start) {
    auto original_next = node_end->next;  // сохраняем оригинальную связь
    node_end->next = node_cycle_start;  // создаем цикл: 10 → 5

    auto result = find_loop(list);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(
        result,
        node_cycle_start);  // начало цикла должно быть узел со значением 5
    EXPECT_EQ(result->value, 5);

    // Восстанавливаем
    node_end->next = original_next;
  }
}


TEST(DSUTask, CountIslands) {
  std::vector<std::vector<int>> grid = {{0, 1, 0, 0, 1},
                                        {0, 1, 1, 0, 1},
                                        {1, 1, 0, 1, 1},
                                        {0, 0, 0, 0, 1},
                                        {1, 0, 1, 1, 1}};
  std::vector<std::vector<int>> grid1 = {{1, 0, 1, 0, 1},
                                         {0, 1, 0, 1, 0},
                                         {1, 0, 1, 0, 1},
                                         {0, 1, 0, 1, 0},
                                         {1, 0, 1, 0, 1}};
  std::vector<std::vector<int>> grid2 = {{0, 0, 1, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {1, 1, 1, 1, 1},
                                         {0, 0, 1, 0, 0},
                                         {0, 0, 1, 0, 0}};
  std::vector<std::vector<int>> grid3 = {{1, 1, 0, 1, 1},
                                         {1, 1, 0, 1, 1},
                                         {0, 0, 0, 0, 0},
                                         {1, 1, 0, 1, 1},
                                         {1, 1, 0, 1, 1}};

  EXPECT_EQ(count_islands(grid), 3);
  EXPECT_EQ(count_islands(grid1), 13);
  EXPECT_EQ(count_islands(grid2), 1);
  EXPECT_EQ(count_islands(grid3), 4);
}