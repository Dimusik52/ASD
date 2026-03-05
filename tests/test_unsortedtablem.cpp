// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2

#include <gtest/gtest.h>
#include "../lib_unsortedtablem/unsortedtablem.h"

TEST(UnsortedTableMTest, InsertAndFind) {
  UnsortedTableM<int, std::string> table;

  table.insert(1, "one");
  table.insert(2, "two");
  table.insert(3, "three");

  auto* val = table.find(2);
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, "two");

  EXPECT_EQ(table.find(4), nullptr);
}

TEST(UnsortedTableMTest, UpdateExistingKey) {
  UnsortedTableM<int, std::string> table;

  table.insert(1, "one");
  table.insert(1, "ONE");

  auto* val = table.find(1);
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, "ONE");
}

TEST(UnsortedTableMTest, Erase) {
  UnsortedTableM<int, std::string> table;

  table.insert(1, "one");
  table.insert(2, "two");

  table.erase(1);

  EXPECT_EQ(table.find(1), nullptr);
  EXPECT_NE(table.find(2), nullptr);

  table.erase(999);
}

TEST(UnsortedTableMTest, IsEmpty) {
  UnsortedTableM<int, std::string> table;

  EXPECT_TRUE(table.isEmpty());

  table.insert(1, "one");
  EXPECT_FALSE(table.isEmpty());

  table.erase(1);
  EXPECT_TRUE(table.isEmpty());
}

TEST(UnsortedTableMTest, ModifyThroughPointer) {
  UnsortedTableM<int, std::string> table;
  table.insert(1, "one");

  auto* val = table.find(1);
  ASSERT_NE(val, nullptr);

  *val = "modified";

  auto* check = table.find(1);
  EXPECT_EQ(*check, "modified");
}

TEST(UnsortedTableMTest, Contains) {
  UnsortedTableM<int, std::string> table;

  table.insert(1, "one");

  EXPECT_TRUE(table.contains(1));
  EXPECT_FALSE(table.contains(2));
}