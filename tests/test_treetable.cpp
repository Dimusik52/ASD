// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#include <gtest/gtest.h>

#include "../lib_treetable/treetable.h"

TEST(TreeTableTest, EmptyTable) {
  TreeTable<int, std::string> table;

  EXPECT_TRUE(table.isEmpty());
  EXPECT_EQ(table.size(), 0);
  EXPECT_EQ(table.find(10), nullptr);
  EXPECT_FALSE(table.contains(10));
}

TEST(TreeTableTest, InsertAndFind) {
  TreeTable<int, std::string> table;

  table.insert(1, "one");
  table.insert(2, "two");
  table.insert(3, "three");

  EXPECT_FALSE(table.isEmpty());
  EXPECT_EQ(table.size(), 3);

  auto* val = table.find(2);
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, "two");

  EXPECT_TRUE(table.contains(1));
  EXPECT_TRUE(table.contains(3));
  EXPECT_FALSE(table.contains(5));
}

TEST(TreeTableTest, UpdateExistingKey) {
  TreeTable<int, std::string> table;

  table.insert(1, "one");
  table.insert(1, "ONE");

  EXPECT_EQ(table.size(), 1);

  auto* val = table.find(1);
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, "ONE");
}

TEST(TreeTableTest, EraseLeaf) {
  TreeTable<int, std::string> table;

  table.insert(1, "A");
  table.insert(2, "B");
  table.insert(3, "C");

  table.erase(3);

  EXPECT_EQ(table.size(), 2);
  EXPECT_FALSE(table.contains(3));
  EXPECT_TRUE(table.contains(1));
  EXPECT_TRUE(table.contains(2));
}

TEST(TreeTableTest, EraseRoot) {
  TreeTable<int, std::string> table;

  table.insert(1, "A");
  table.insert(2, "B");
  table.insert(3, "C");

  table.erase(1);

  EXPECT_EQ(table.size(), 2);
  EXPECT_FALSE(table.contains(1));
}

TEST(TreeTableTest, EraseNonExistentKey) {
  TreeTable<int, std::string> table;

  table.insert(1, "A");
  table.insert(2, "B");

  table.erase(999);

  EXPECT_EQ(table.size(), 2);
  EXPECT_TRUE(table.contains(1));
  EXPECT_TRUE(table.contains(2));
}

TEST(TreeTableTest, CopyConstructor) {
  TreeTable<int, std::string> original;

  original.insert(1, "one");
  original.insert(2, "two");
  original.insert(3, "three");

  TreeTable<int, std::string> copy(original);

  EXPECT_EQ(copy.size(), original.size());
  EXPECT_TRUE(copy.contains(1));
  EXPECT_TRUE(copy.contains(2));
  EXPECT_TRUE(copy.contains(3));

  original.erase(1);
  EXPECT_TRUE(copy.contains(1));
  EXPECT_FALSE(original.contains(1));
}

TEST(TreeTableTest, AssignmentOperator) {
  TreeTable<int, std::string> original;
  original.insert(1, "one");
  original.insert(2, "two");

  TreeTable<int, std::string> copy;
  copy = original;

  EXPECT_EQ(copy.size(), 2);
  EXPECT_TRUE(copy.contains(1));
  EXPECT_TRUE(copy.contains(2));

  copy = copy;
  EXPECT_EQ(copy.size(), 2);
}

TEST(TreeTableTest, ClearTable) {
  TreeTable<int, std::string> table;

  table.insert(1, "A");
  table.insert(2, "B");
  table.insert(3, "C");

  EXPECT_EQ(table.size(), 3);

  table.clear();

  EXPECT_TRUE(table.isEmpty());
  EXPECT_EQ(table.size(), 0);
  EXPECT_EQ(table.find(1), nullptr);
}

TEST(TreeTableTest, ComplexSequence) {
  TreeTable<int, std::string> table;

  // Вставка
  table.insert(5, "five");
  table.insert(3, "three");
  table.insert(7, "seven");
  table.insert(1, "one");

  EXPECT_EQ(table.size(), 4);

  // Обновление
  table.insert(3, "THREE");
  auto* val = table.find(3);
  EXPECT_EQ(*val, "THREE");

  // Удаление
  table.erase(7);
  EXPECT_FALSE(table.contains(7));
  EXPECT_EQ(table.size(), 3);

  // Очистка и повторное заполнение
  table.clear();
  EXPECT_TRUE(table.isEmpty());

  table.insert(100, "hundred");
  EXPECT_EQ(table.size(), 1);
  EXPECT_TRUE(table.contains(100));
}