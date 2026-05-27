// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2
#include <gtest/gtest.h>

#include <sstream>

#include "../lib_avltreetable/avltreetable.h"

TEST(AVLTableTest, DefaultConstructor) {
  AVLTable<int, std::string> table;

  EXPECT_TRUE(table.isEmpty());
  EXPECT_EQ(table.size(), 0);
  EXPECT_FALSE(table.contains(1));
  EXPECT_EQ(table.find(1), nullptr);
}

TEST(AVLTableTest, InsertAndFind) {
  AVLTable<int, std::string> table;

  table.insert(5, "five");
  table.insert(3, "three");
  table.insert(7, "seven");

  EXPECT_FALSE(table.isEmpty());
  EXPECT_EQ(table.size(), 3);

  auto* val = table.find(5);
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, "five");

  EXPECT_EQ(table.find(10), nullptr);
  EXPECT_FALSE(table.contains(10));
}

TEST(AVLTableTest, InsertOverwrite) {
  AVLTable<int, std::string> table;

  table.insert(5, "five");
  EXPECT_EQ(*table.find(5), "five");
  EXPECT_EQ(table.size(), 1);

  table.insert(5, "FIVE");
  EXPECT_EQ(*table.find(5), "FIVE");
  EXPECT_EQ(table.size(), 1);
}

TEST(AVLTableTest, Erase) {
  AVLTable<int, std::string> table;

  table.insert(5, "five");
  table.insert(3, "three");
  table.insert(7, "seven");

  table.erase(3);
  EXPECT_EQ(table.size(), 2);
  EXPECT_FALSE(table.contains(3));
  EXPECT_TRUE(table.contains(5));
  EXPECT_TRUE(table.contains(7));

  table.erase(999);
  EXPECT_EQ(table.size(), 2);
}

TEST(AVLTableTest, CopyConstructor) {
  AVLTable<int, std::string> table1;
  table1.insert(1, "one");
  table1.insert(2, "two");

  AVLTable<int, std::string> table2(table1);

  EXPECT_EQ(table2.size(), 2);
  EXPECT_TRUE(table2.contains(1));
  EXPECT_TRUE(table2.contains(2));

  table2.insert(3, "three");
  EXPECT_EQ(table2.size(), 3);
  EXPECT_EQ(table1.size(), 2);
}

TEST(AVLTableTest, Clear) {
  AVLTable<int, std::string> table;

  table.insert(1, "one");
  table.insert(2, "two");
  table.insert(3, "three");

  EXPECT_EQ(table.size(), 3);

  table.clear();
  EXPECT_TRUE(table.isEmpty());
  EXPECT_EQ(table.size(), 0);
  EXPECT_FALSE(table.contains(1));
}

TEST(AVLTableTest, PrintSorted) {
  AVLTable<int, std::string> table;
  table.insert(5, "five");
  table.insert(3, "three");
  table.insert(7, "seven");
  table.insert(1, "one");

  std::stringstream ss;
  table.printSorted(ss);
  EXPECT_EQ(ss.str(), "1:one 3:three 5:five 7:seven \n");
}

TEST(AVLTableTest, ToStringSorted) {
  AVLTable<int, std::string> table;
  table.insert(5, "five");
  table.insert(3, "three");
  table.insert(7, "seven");

  EXPECT_EQ(table.toStringSorted(), "3:three 5:five 7:seven \n");
}

TEST(AVLTableTest, PrintEmptyTree) {
  AVLTable<int, std::string> table;
  std::stringstream ss;

  table.printSorted(ss);
  EXPECT_EQ(ss.str(), "Tree is empty!\n");
}

TEST(AVLTableTest, ClearThenInsert) {
  AVLTable<int, std::string> table;

  table.insert(1, "one");
  table.insert(2, "two");
  table.clear();

  EXPECT_TRUE(table.isEmpty());
  EXPECT_EQ(table.size(), 0);

  table.insert(42, "answer");
  EXPECT_EQ(table.size(), 1);
  EXPECT_EQ(*table.find(42), "answer");
}