// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2
#include <gtest/gtest.h>

#include <sstream>

#include "../lib_rbtreetable/rbtreetable.h"

TEST(RBTableTest, DefaultConstructor) {
  RBTable<int, std::string> table;

  EXPECT_TRUE(table.isEmpty());
  EXPECT_EQ(table.size(), 0);
  EXPECT_FALSE(table.contains(1));
  EXPECT_EQ(table.find(1), nullptr);
}

TEST(RBTableTest, InsertAndFind) {
  RBTable<int, std::string> table;

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

  EXPECT_EQ(table.find(10), nullptr);
  EXPECT_FALSE(table.contains(10));
}

TEST(RBTableTest, InsertOverwrite) {
  RBTable<int, std::string> table;

  table.insert(5, "five");
  EXPECT_EQ(*table.find(5), "five");
  EXPECT_EQ(table.size(), 1);

  table.insert(5, "FIVE");
  EXPECT_EQ(*table.find(5), "FIVE");
  EXPECT_EQ(table.size(), 1);  // Размер не увеличился
}

TEST(RBTableTest, StringKeys) {
  RBTable<std::string, int> table;

  table.insert("banana", 1);
  table.insert("apple", 2);
  table.insert("cherry", 3);

  EXPECT_EQ(table.size(), 3);
  EXPECT_EQ(*table.find("apple"), 2);
  EXPECT_EQ(*table.find("banana"), 1);
  EXPECT_EQ(*table.find("cherry"), 3);
  EXPECT_TRUE(table.contains("banana"));
  EXPECT_FALSE(table.contains("grape"));
}

TEST(RBTableTest, DoubleKeys) {
  RBTable<double, std::string> table;

  table.insert(3.14, "pi");
  table.insert(2.71, "e");
  table.insert(1.62, "phi");

  EXPECT_EQ(table.size(), 3);
  EXPECT_EQ(*table.find(3.14), "pi");
  EXPECT_EQ(*table.find(2.71), "e");
  EXPECT_EQ(*table.find(1.62), "phi");
}

TEST(RBTableTest, Clear) {
  RBTable<int, std::string> table;

  table.insert(1, "one");
  table.insert(2, "two");
  table.insert(3, "three");

  EXPECT_EQ(table.size(), 3);
  EXPECT_TRUE(table.contains(2));

  table.clear();
  EXPECT_TRUE(table.isEmpty());
  EXPECT_EQ(table.size(), 0);
  EXPECT_FALSE(table.contains(1));
  EXPECT_EQ(table.find(1), nullptr);

  // После очистки можно снова вставлять
  table.insert(42, "answer");
  EXPECT_EQ(table.size(), 1);
  EXPECT_EQ(*table.find(42), "answer");
}

TEST(RBTableTest, CopyConstructor) {
  RBTable<int, std::string> table1;
  table1.insert(1, "one");
  table1.insert(2, "two");
  table1.insert(3, "three");

  RBTable<int, std::string> table2(table1);

  EXPECT_EQ(table2.size(), 3);
  EXPECT_TRUE(table2.contains(1));
  EXPECT_TRUE(table2.contains(2));
  EXPECT_TRUE(table2.contains(3));
  EXPECT_EQ(*table2.find(2), "two");

  // Изменение table2 не влияет на table1
  table2.insert(4, "four");
  EXPECT_EQ(table2.size(), 4);
  EXPECT_EQ(table1.size(), 3);
  EXPECT_FALSE(table1.contains(4));
}

TEST(RBTableTest, PrintSortedEmpty) {
  RBTable<int, std::string> table;
  std::stringstream ss;
  table.printSorted(ss);
  EXPECT_EQ(ss.str(), "Tree is empty!\n");
}

TEST(RBTableTest, PrintSortedNonEmpty) {
  RBTable<int, std::string> table;
  table.insert(3, "three");
  table.insert(1, "one");
  table.insert(2, "two");

  std::stringstream ss;
  table.printSorted(ss);
  EXPECT_EQ(ss.str(), "1:one 2:two 3:three \n");
}

TEST(RBTableTest, ToStringSorted) {
  RBTable<int, std::string> table;
  table.insert(3, "three");
  table.insert(1, "one");
  table.insert(2, "two");

  std::string result = table.toStringSorted();
  EXPECT_EQ(result, "1:one 2:two 3:three \n");
}

TEST(RBTableTest, PrintTreeDoesNotCrash) {
  RBTable<int, std::string> table;
  table.insert(5, "five");
  table.insert(3, "three");
  table.insert(7, "seven");

  std::stringstream ss;
  table.print(ss);
  EXPECT_FALSE(ss.str().empty());
}

TEST(RBTableTest, ManyInserts) {
  RBTable<int, std::string> table;

  for (int i = 1; i <= 100; i++) {
    table.insert(i, std::to_string(i));
  }

  EXPECT_EQ(table.size(), 100);

  for (int i = 1; i <= 100; i++) {
    EXPECT_TRUE(table.contains(i));
    EXPECT_EQ(*table.find(i), std::to_string(i));
  }
}

TEST(RBTableTest, ManyInsertsDescending) {
  RBTable<int, std::string> table;

  for (int i = 100; i >= 1; i--) {
    table.insert(i, std::to_string(i));
  }

  EXPECT_EQ(table.size(), 100);

  for (int i = 1; i <= 100; i++) {
    EXPECT_TRUE(table.contains(i));
  }
}

TEST(RBTableTest, ManyInsertsSameKey) {
  RBTable<int, std::string> table;

  for (int i = 0; i < 100; i++) {
    table.insert(42, "value_" + std::to_string(i));
  }

  EXPECT_EQ(table.size(), 1);              // Размер не вырос
  EXPECT_EQ(*table.find(42), "value_99");  // Последнее значение
}


TEST(RBTableTest, EmptyFind) {
  RBTable<int, std::string> table;
  EXPECT_EQ(table.find(42), nullptr);
  EXPECT_FALSE(table.contains(42));
}

TEST(RBTableTest, SingleElement) {
  RBTable<int, std::string> table;

  table.insert(42, "answer");
  EXPECT_EQ(table.size(), 1);
  EXPECT_FALSE(table.isEmpty());
  EXPECT_TRUE(table.contains(42));
  EXPECT_EQ(*table.find(42), "answer");
  EXPECT_FALSE(table.contains(43));

  table.clear();
  EXPECT_TRUE(table.isEmpty());
  EXPECT_EQ(table.size(), 0);
}