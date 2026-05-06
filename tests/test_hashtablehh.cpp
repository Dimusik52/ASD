// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#include <gtest/gtest.h>
#include "../lib_hashtablehh/hashtablehh.h"

TEST(HashTableHHTest, CreateEmptyTable) {
  HashTableHH<int> table;
  EXPECT_TRUE(table.isEmpty());
  EXPECT_EQ(0, table.size());
  EXPECT_EQ(nullptr, table.find("key"));
  EXPECT_FALSE(table.contains("key"));
}

TEST(HashTableHHTest, InsertAndFind) {
  HashTableHH<std::string> table(10);

  table.insert("key1", "value1");
  table.insert("key2", "value2");

  EXPECT_FALSE(table.isEmpty());
  EXPECT_EQ(2, table.size());

  auto* val1 = table.find("key1");
  auto* val2 = table.find("key2");

  ASSERT_NE(nullptr, val1);
  ASSERT_NE(nullptr, val2);
  EXPECT_EQ("value1", *val1);
  EXPECT_EQ("value2", *val2);
}

TEST(HashTableHHTest, InsertDuplicateKey) {
  HashTableHH<double> table;

  table.insert("test", 3.14);
  EXPECT_THROW(table.insert("test", 2.71), std::logic_error);
}

TEST(HashTableHHTest, EraseElement) {
  HashTableHH<int> table;

  table.insert("key1", 100);
  table.insert("key2", 200);

  EXPECT_TRUE(table.contains("key1"));
  EXPECT_EQ(2, table.size());

  table.erase("key1");

  EXPECT_FALSE(table.contains("key1"));
  EXPECT_TRUE(table.contains("key2"));
  EXPECT_EQ(1, table.size());
  EXPECT_EQ(nullptr, table.find("key1"));
}

TEST(HashTableHHTest, EraseThenFindWithCollision) {
  HashTableHH<int> table(5);

  table.insert("aaa", 111);
  table.insert("bbb", 222);
  table.insert("ccc", 333);

  table.erase("bbb");
  EXPECT_FALSE(table.contains("bbb"));

  EXPECT_TRUE(table.contains("aaa"));
  EXPECT_TRUE(table.contains("ccc"));
  EXPECT_EQ(111, *table.find("aaa"));
  EXPECT_EQ(333, *table.find("ccc"));

  table.insert("ddd", 444);
  EXPECT_TRUE(table.contains("ddd"));
  EXPECT_EQ(3, table.size());
}

TEST(HashTableHHTest, EraseNonExistentKey) {
  HashTableHH<int> table;
  EXPECT_THROW(table.erase("nonexistent"), std::logic_error);
}

TEST(HashTableHHTest, FullTable) {
  HashTableHH<int> table(3);

  table.insert("a", 1);
  table.insert("b", 2);
  table.insert("c", 3);

  EXPECT_EQ(3, table.size());
  EXPECT_TRUE(table.isFull());

  EXPECT_THROW(table.insert("d", 4), std::logic_error);
}

TEST(HashTableHHTest, ReuseDeletedSlot) {
  HashTableHH<std::string> table(5);

  table.insert("first", "value1");
  table.erase("first");

  table.insert("second", "value2");

  EXPECT_TRUE(table.contains("second"));
  EXPECT_FALSE(table.contains("first"));
  EXPECT_EQ("value2", *table.find("second"));
  EXPECT_EQ(1, table.size());
}

TEST(HashTableHHTest, CopyConstructor) {
  HashTableHH<int> table1;
  table1.insert("x", 10);
  table1.insert("y", 20);

  HashTableHH<int> table2(table1);

  EXPECT_TRUE(table2.contains("x"));
  EXPECT_TRUE(table2.contains("y"));
  EXPECT_EQ(10, *table2.find("x"));
  EXPECT_EQ(20, *table2.find("y"));

  table2.insert("z", 30);
  EXPECT_FALSE(table1.contains("z"));
  EXPECT_EQ(2, table1.size());
  EXPECT_EQ(3, table2.size());
}

TEST(HashTableHHTest, DoubleHashingResolvesCollisions) {
  HashTableHH<int> table(5);

  table.insert("abc", 1);  // 97+98+99=294, 294%5=4
  table.insert("cba", 2);  // 99+98+97=294, 294%5=4
  table.insert("acb", 3);  // 97+99+98=294, 294%5=4
  table.insert("bac", 4);  // 98+97+99=294, 294%5=4

  EXPECT_TRUE(table.contains("abc"));
  EXPECT_TRUE(table.contains("cba"));
  EXPECT_TRUE(table.contains("acb"));
  EXPECT_TRUE(table.contains("bac"));

  EXPECT_EQ(1, *table.find("abc"));
  EXPECT_EQ(2, *table.find("cba"));
  EXPECT_EQ(3, *table.find("acb"));
  EXPECT_EQ(4, *table.find("bac"));
}

TEST(HashTableHHTest, SearchPassesThroughDeleted) {
  HashTableHH<std::string> table(10);

  table.insert("first", "val1");
  table.insert("second", "val2");
  table.insert("third", "val3");

  table.erase("first");

  auto* val3 = table.find("third");
  ASSERT_NE(nullptr, val3);
  EXPECT_EQ("val3", *val3);
}