// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2
#include <gtest/gtest.h>

#include <sstream>

#include "../lib_bsttable/bsttable.h"

TEST(BSTreeTableTest, DefaultConstructor) {
  BSTreeTable<int, std::string> table;

  EXPECT_TRUE(table.isEmpty());
  EXPECT_EQ(table.size(), 0);
  EXPECT_FALSE(table.contains(1));
  EXPECT_EQ(table.find(1), nullptr);
}

TEST(BSTreeTableTest, InsertAndFind) {
  BSTreeTable<int, std::string> table;

  table.insert(5, "five");
  table.insert(3, "three");
  table.insert(7, "seven");

  EXPECT_FALSE(table.isEmpty());
  EXPECT_EQ(table.size(), 3);

  auto* val = table.find(5);
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, "five");

  val = table.find(3);
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, "three");

  val = table.find(7);
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, "seven");

  // Несуществующий ключ
  EXPECT_EQ(table.find(10), nullptr);
  EXPECT_FALSE(table.contains(10));
}

TEST(BSTreeTableTest, InsertOverwrite) {
  BSTreeTable<int, std::string> table;

  table.insert(5, "five");
  EXPECT_EQ(*table.find(5), "five");
  EXPECT_EQ(table.size(), 1);

  table.insert(5, "FIVE");
  EXPECT_EQ(*table.find(5), "FIVE");
  EXPECT_EQ(table.size(), 1);
}

TEST(BSTreeTableTest, EraseLeafNode) {
  BSTreeTable<int, std::string> table;

  table.insert(5, "five");
  table.insert(3, "three");
  table.insert(7, "seven");

  // Удаляем лист (3)
  table.erase(3);
  EXPECT_EQ(table.size(), 2);
  EXPECT_FALSE(table.contains(3));
  EXPECT_TRUE(table.contains(5));
  EXPECT_TRUE(table.contains(7));

  // Удаляем лист (7)
  table.erase(7);
  EXPECT_EQ(table.size(), 1);
  EXPECT_FALSE(table.contains(7));
  EXPECT_TRUE(table.contains(5));
}

TEST(BSTreeTableTest, EraseNodeWithOneChild) {
  BSTreeTable<int, std::string> table;

  table.insert(5, "five");
  table.insert(3, "three");
  table.insert(2, "two");  // 3 -> left = 2
  // Дерево: 5 -> left = 3, 3 -> left = 2

  table.erase(3);  // Удаляем узел с одним левым ребенком
  EXPECT_EQ(table.size(), 2);
  EXPECT_FALSE(table.contains(3));
  EXPECT_TRUE(table.contains(5));
  EXPECT_TRUE(table.contains(2));
}

TEST(BSTreeTableTest, EraseNodeWithTwoChildren) {
  BSTreeTable<int, std::string> table;

  table.insert(5, "five");
  table.insert(3, "three");
  table.insert(7, "seven");
  table.insert(2, "two");
  table.insert(4, "four");
  table.insert(6, "six");
  table.insert(8, "eight");

  // Удаляем корень с двумя детьми
  table.erase(5);
  EXPECT_EQ(table.size(), 6);
  EXPECT_FALSE(table.contains(5));

  // Дерево должно остаться валидным
  EXPECT_TRUE(table.contains(3));
  EXPECT_TRUE(table.contains(7));
  EXPECT_TRUE(table.contains(2));
  EXPECT_TRUE(table.contains(4));
  EXPECT_TRUE(table.contains(6));
  EXPECT_TRUE(table.contains(8));
}

TEST(BSTreeTableTest, EraseRootWithNoChildren) {
  BSTreeTable<int, std::string> table;

  table.insert(42, "answer");
  EXPECT_EQ(table.size(), 1);

  table.erase(42);
  EXPECT_TRUE(table.isEmpty());
  EXPECT_EQ(table.size(), 0);
  EXPECT_EQ(table.find(42), nullptr);
}

TEST(BSTreeTableTest, EraseRootWithOneChild) {
  BSTreeTable<int, std::string> table;

  table.insert(5, "five");
  table.insert(3, "three");

  table.erase(5);  // удаляем корень, правый ребенок
  EXPECT_EQ(table.size(), 1);
  EXPECT_TRUE(table.contains(3));
  EXPECT_FALSE(table.contains(5));
}

TEST(BSTreeTableTest, EraseNonExistentKey) {
  BSTreeTable<int, std::string> table;

  table.insert(10, "ten");
  table.insert(20, "twenty");

  table.erase(999);  // несуществующий ключ
  EXPECT_EQ(table.size(), 2);
  EXPECT_TRUE(table.contains(10));
  EXPECT_TRUE(table.contains(20));
}

TEST(BSTreeTableTest, EraseFromEmptyTable) {
  BSTreeTable<int, std::string> table;

  table.erase(1);
  EXPECT_TRUE(table.isEmpty());
  EXPECT_EQ(table.size(), 0);
}

TEST(BSTreeTableTest, CopyConstructor) {
  BSTreeTable<int, std::string> table1;
  table1.insert(1, "one");
  table1.insert(2, "two");
  table1.insert(3, "three");

  BSTreeTable<int, std::string> table2(table1);

  EXPECT_EQ(table2.size(), 3);
  EXPECT_TRUE(table2.contains(1));
  EXPECT_TRUE(table2.contains(2));
  EXPECT_TRUE(table2.contains(3));
  EXPECT_EQ(*table2.find(2), "two");

  // Изменение table2 не должно влиять на table1
  table2.insert(4, "four");
  EXPECT_EQ(table2.size(), 4);
  EXPECT_EQ(table1.size(), 3);
}

TEST(BSTreeTableTest, AssignmentOperator) {
  BSTreeTable<int, std::string> table1;
  table1.insert(1, "one");
  table1.insert(2, "two");

  BSTreeTable<int, std::string> table2;
  table2.insert(100, "hundred");

  table2 = table1;

  EXPECT_EQ(table2.size(), 2);
  EXPECT_TRUE(table2.contains(1));
  EXPECT_TRUE(table2.contains(2));
  EXPECT_FALSE(table2.contains(100));

  // Самоприсваивание
  table2 = table2;
  EXPECT_EQ(table2.size(), 2);
}

TEST(BSTreeTableTest, Clear) {
  BSTreeTable<int, std::string> table;

  table.insert(1, "one");
  table.insert(2, "two");
  table.insert(3, "three");
  table.insert(4, "four");

  EXPECT_EQ(table.size(), 4);

  table.clear();
  EXPECT_TRUE(table.isEmpty());
  EXPECT_EQ(table.size(), 0);
  EXPECT_FALSE(table.contains(1));

  // После clear можно вставлять заново
  table.insert(42, "answer");
  EXPECT_EQ(table.size(), 1);
  EXPECT_EQ(*table.find(42), "answer");
}

TEST(BSTreeTableTest, ComplexScenario) {
  BSTreeTable<int, std::string> table;

  // Вставка
  for (int i = 1; i <= 10; i++) {
    table.insert(i, "number_" + std::to_string(i));
  }
  EXPECT_EQ(table.size(), 10);

  // Проверка всех элементов
  for (int i = 1; i <= 10; i++) {
    EXPECT_TRUE(table.contains(i));
    EXPECT_EQ(*table.find(i), "number_" + std::to_string(i));
  }

  // Удаление четных
  for (int i = 2; i <= 10; i += 2) {
    table.erase(i);
  }
  EXPECT_EQ(table.size(), 5);  // остались 1,3,5,7,9

  // Проверка
  EXPECT_TRUE(table.contains(1));
  EXPECT_FALSE(table.contains(2));
  EXPECT_TRUE(table.contains(3));
  EXPECT_FALSE(table.contains(4));
  EXPECT_TRUE(table.contains(5));
  EXPECT_FALSE(table.contains(6));
  EXPECT_TRUE(table.contains(7));
  EXPECT_FALSE(table.contains(8));
  EXPECT_TRUE(table.contains(9));
  EXPECT_FALSE(table.contains(10));

  // Очистка
  table.clear();
  EXPECT_TRUE(table.isEmpty());
}

TEST(BSTreeTableTest, UpdateAfterErase) {
  BSTreeTable<int, std::string> table;

  table.insert(1, "one");
  table.insert(2, "two");
  table.erase(1);

  // После удаления можно вставить снова
  table.insert(1, "ONE");
  EXPECT_TRUE(table.contains(1));
  EXPECT_EQ(*table.find(1), "ONE");
  EXPECT_EQ(table.size(), 2);
}

TEST(BSTreeTableTest, PrintSortedEmptyTree) {
  BSTreeTable<int, std::string> table;
  std::stringstream ss;

  table.printSorted(ss);
  EXPECT_EQ(ss.str(), "Tree is empty!\n");
}

TEST(BSTreeTableTest, PrintSortedSingleElement) {
  BSTreeTable<int, std::string> table;
  table.insert(42, "answer");

  std::stringstream ss;
  table.printSorted(ss);
  EXPECT_EQ(ss.str(), "42:answer \n");
}

TEST(BSTreeTableTest, PrintSortedMultipleElements) {
  BSTreeTable<int, std::string> table;
  table.insert(5, "five");
  table.insert(3, "three");
  table.insert(7, "seven");
  table.insert(1, "one");
  table.insert(4, "four");

  std::stringstream ss;
  table.printSorted(ss);
  EXPECT_EQ(ss.str(), "1:one 3:three 4:four 5:five 7:seven \n");
}

TEST(BSTreeTableTest, PrintSortedAfterDeletion) {
  BSTreeTable<int, std::string> table;
  table.insert(5, "five");
  table.insert(3, "three");
  table.insert(7, "seven");
  table.insert(1, "one");
  table.insert(4, "four");

  table.erase(3);

  std::stringstream ss;
  table.printSorted(ss);
  EXPECT_EQ(ss.str(), "1:one 4:four 5:five 7:seven \n");
}

TEST(BSTreeTableTest, ToStringSorted) {
  BSTreeTable<int, std::string> table;
  table.insert(5, "five");
  table.insert(3, "three");
  table.insert(7, "seven");

  EXPECT_EQ(table.toStringSorted(), "3:three 5:five 7:seven \n");
}