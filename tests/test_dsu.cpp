// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#include <gtest/gtest.h>
#include <stdexcept>
#include "../lib_dsu/dsu.h"


TEST(DSUTest, ConstructorAndSize) {
  DSU<int> dsu(10);
  EXPECT_EQ(dsu.size(), 10);

  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(dsu.find(i), i);
  }
}

TEST(DSUTest, SimpleUnion) {
  DSU<int> dsu(5);

  dsu.union_sets(0, 1);
  EXPECT_TRUE(dsu.connected(0, 1));
  EXPECT_EQ(dsu.find(0), dsu.find(1));

  dsu.union_sets(2, 3);
  EXPECT_TRUE(dsu.connected(2, 3));
  EXPECT_FALSE(dsu.connected(0, 2));
}

TEST(DSUTest, Transitivity) {
  DSU<int> dsu(6);

  dsu.union_sets(0, 1);
  dsu.union_sets(1, 2);
  dsu.union_sets(3, 4);
  dsu.union_sets(4, 5);

  EXPECT_TRUE(dsu.connected(0, 2));
  EXPECT_TRUE(dsu.connected(3, 5));
  EXPECT_FALSE(dsu.connected(0, 3));
  EXPECT_FALSE(dsu.connected(2, 4));

  dsu.union_sets(2, 4);
  EXPECT_TRUE(dsu.connected(0, 5));
  EXPECT_TRUE(dsu.connected(1, 3));
}

TEST(DSUTest, FindMethodsConsistency) {
  DSU<int> dsu(10);

  dsu.union_sets(0, 1);
  dsu.union_sets(1, 2);
  dsu.union_sets(3, 4);
  dsu.union_sets(4, 5);
  dsu.union_sets(0, 3);

  for (int i = 0; i < 6; ++i) {
    EXPECT_EQ(dsu.find(i), dsu.find_rec(i));
  }
}

TEST(DSUTest, UnionWithSelf) {
  DSU<int> dsu(5);

  dsu.union_sets(2, 2);
  EXPECT_EQ(dsu.find(2), 2);

  dsu.union_sets(2, 3);
  EXPECT_TRUE(dsu.connected(2, 3));
}

TEST(DSUTest, Exceptions) {
  DSU<int> dsu(5);

  EXPECT_THROW(dsu.find(-1), std::out_of_range);
  EXPECT_THROW(dsu.find_rec(-1), std::out_of_range);
  EXPECT_THROW(dsu.union_sets(-1, 2), std::out_of_range);

  EXPECT_THROW(dsu.find(10), std::out_of_range);
  EXPECT_THROW(dsu.union_sets(1, 10), std::out_of_range);

  EXPECT_THROW(DSU<int>(0), std::invalid_argument);
}

// Тест 7: Копирование DSU
TEST(DSUTest, CopyConstructor) {
  DSU<int> dsu1(5);
  dsu1.union_sets(0, 1);
  dsu1.union_sets(2, 3);

  DSU<int> dsu2 = dsu1;

  EXPECT_TRUE(dsu2.connected(0, 1));
  EXPECT_TRUE(dsu2.connected(2, 3));
  EXPECT_FALSE(dsu2.connected(0, 2));

  dsu2.union_sets(1, 2);
  EXPECT_TRUE(dsu2.connected(0, 3));
  EXPECT_FALSE(dsu1.connected(0, 3));
}

// Тест 8: Оператор присваивания
TEST(DSUTest, AssignmentOperator) {
  DSU<int> dsu1(5);
  dsu1.union_sets(0, 1);
  dsu1.union_sets(2, 3);

  DSU<int> dsu2(3);
  dsu2 = dsu1;

  EXPECT_EQ(dsu2.size(), 5);
  EXPECT_TRUE(dsu2.connected(0, 1));
  EXPECT_TRUE(dsu2.connected(2, 3));

  dsu2 = dsu2;
  EXPECT_TRUE(dsu2.connected(0, 1));
}

TEST(DSUTest, RankOptimization) {
  DSU<int> dsu(10);

  // Создаем два дерева высотой 2
  dsu.union_sets(0, 1);  // Ранги: 0(1) ← 1(0)
  dsu.union_sets(1, 2);  // 0(1) ← 1(0), 2(0)

  dsu.union_sets(3, 4);  // 3(1) ← 4(0)
  dsu.union_sets(4, 5);  // 3(1) ← 4(0), 5(0)

  // Объединяем деревья с одинаковым рангом
  dsu.union_sets(2, 5);

  // Теперь все элементы 0-5 должны быть в одном множестве
  EXPECT_TRUE(dsu.connected(0, 3));
  EXPECT_TRUE(dsu.connected(1, 4));
  EXPECT_TRUE(dsu.connected(2, 5));
}

TEST(DSUTest, MultipleUnions) {
  DSU<int> dsu(10);

  dsu.union_sets(0, 9);
  dsu.union_sets(1, 8);
  dsu.union_sets(2, 7);
  dsu.union_sets(3, 6);
  dsu.union_sets(4, 5);

  EXPECT_TRUE(dsu.connected(0, 9));
  EXPECT_TRUE(dsu.connected(1, 8));
  EXPECT_TRUE(dsu.connected(2, 7));
  EXPECT_TRUE(dsu.connected(3, 6));
  EXPECT_TRUE(dsu.connected(4, 5));

  dsu.union_sets(9, 8);  // {0,1,8,9}
  dsu.union_sets(7, 6);  // {2,3,6,7}
  dsu.union_sets(5, 0);  // {0,1,4,5,8,9}


  EXPECT_TRUE(dsu.connected(0, 1));  // Оба в группе A
  EXPECT_TRUE(dsu.connected(2, 3));  // Оба в группе B


  EXPECT_FALSE(dsu.connected(0, 2));  // 0 в A, 2 в B
  EXPECT_FALSE(dsu.connected(1, 3));  // 1 в A, 3 в B
  EXPECT_FALSE(dsu.connected(4, 6));  // 4 в A, 6 в B
  EXPECT_FALSE(dsu.connected(5, 7));  // 5 в A, 7 в B
  EXPECT_FALSE(dsu.connected(8, 2));  // 8 в A, 2 в B
  EXPECT_FALSE(dsu.connected(9, 3));  // 9 в A, 3 в B
}

TEST(DSUTest, DifferentTypes) {
  DSU<int> dsu_int(10);
  DSU<size_t> dsu_size_t(10);
  DSU<long> dsu_long(10);

  dsu_int.union_sets(0, 1);
  dsu_size_t.union_sets(0, 1);
  dsu_long.union_sets(0, 1);

  EXPECT_TRUE(dsu_int.connected(0, 1));
  EXPECT_TRUE(dsu_size_t.connected(0, 1));
  EXPECT_TRUE(dsu_long.connected(0, 1));
}