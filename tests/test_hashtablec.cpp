// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#include <gtest/gtest.h>
#include "../lib_hashtablec/hashtablec.h"

TEST(HashTableCTest, CreateEmptyTable) {
  HashTableC<int> table;
  EXPECT_TRUE(table.isEmpty());
  EXPECT_EQ(nullptr, table.find("key"));
  EXPECT_FALSE(table.contains("key"));
}

TEST(HashTableCTest, CopyConstructor) {
  HashTableC<std::string> table1;
  table1.insert("key1", "value1");
  table1.insert("key2", "value2");

  HashTableC<std::string> table2(table1);

  EXPECT_TRUE(table2.contains("key1"));
  EXPECT_TRUE(table2.contains("key2"));
  EXPECT_EQ("value1", *table2.find("key1"));
  EXPECT_EQ("value2", *table2.find("key2"));

  table2.insert("key3", "value3");
  EXPECT_FALSE(table1.contains("key3"));
}

TEST(HashTableCTest, InsertAndFind) {
  HashTableC<std::string> table(10);

  table.insert("key1", "value1");
  table.insert("key2", "value2");

  auto* val1 = table.find("key1");
  auto* val2 = table.find("key2");

  ASSERT_NE(nullptr, val1);
  ASSERT_NE(nullptr, val2);
  EXPECT_EQ("value1", *val1);
  EXPECT_EQ("value2", *val2);
  EXPECT_FALSE(table.isEmpty());
}

TEST(HashTableCTest, InsertDuplicateKey) {
  HashTableC<double> table;

  table.insert("test", 3.14);
  EXPECT_THROW(table.insert("test", 2.71), std::logic_error);
}

TEST(HashTableCTest, EraseElement) {
  HashTableC<int> table;

  table.insert("key", 100);
  EXPECT_TRUE(table.contains("key"));

  table.erase("key");
  EXPECT_FALSE(table.contains("key"));
  EXPECT_EQ(nullptr, table.find("key"));
}

TEST(HashTableCTest, EraseNonExistentKey) {
  HashTableC<int> table;
  EXPECT_THROW(table.erase("nonexistent"), std::logic_error);
}

TEST(HashTableCTest, HandleCollisions) {
  HashTableC<std::string> table(5);

  // hash = сумма ASCII кодов % 5
  table.insert("abc", "value1");  // a=97, b=98, c=99, sum=294
  table.insert("cba", "value2");  // c=99, b=98, a=97, sum=294
  table.insert("acb", "value3");  // a=97, c=99, b=98, sum=294

  EXPECT_TRUE(table.contains("abc"));
  EXPECT_TRUE(table.contains("cba"));
  EXPECT_TRUE(table.contains("acb"));

  auto* val1 = table.find("abc");
  auto* val2 = table.find("cba");
  auto* val3 = table.find("acb");

  ASSERT_NE(nullptr, val1);
  ASSERT_NE(nullptr, val2);
  ASSERT_NE(nullptr, val3);
  EXPECT_EQ("value1", *val1);
  EXPECT_EQ("value2", *val2);
  EXPECT_EQ("value3", *val3);
}

TEST(HashTableCTest, CollisionsWithErase) {
  HashTableC<int> table(3);

  table.insert("aaa", 111);  // 97*3=291 % 3 = 0
  table.insert("bbb", 222);  // 98*3=294 % 3 = 0
  table.insert("ccc", 333);  // 99*3=297 % 3 = 0

  table.erase("bbb");

  EXPECT_FALSE(table.contains("bbb"));
  EXPECT_TRUE(table.contains("aaa"));
  EXPECT_TRUE(table.contains("ccc"));

  auto* val1 = table.find("aaa");
  auto* val3 = table.find("ccc");

  ASSERT_NE(nullptr, val1);
  ASSERT_NE(nullptr, val3);
  EXPECT_EQ(111, *val1);
  EXPECT_EQ(333, *val3);
}