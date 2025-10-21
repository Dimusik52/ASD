// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#include <gtest/gtest.h>

#include "../lib_queue/queue.h"

TEST(QueueTest, DefaultConstructor) {
  Queue<int> q;
  EXPECT_TRUE(q.is_empty());
  EXPECT_FALSE(q.is_full());
}

TEST(QueueTest, ConstructorWithSize) {
  Queue<int> q(5);
  EXPECT_TRUE(q.is_empty());
  EXPECT_FALSE(q.is_full());

  Queue<int> q_zero(0);
  EXPECT_TRUE(q_zero.is_empty());
}

TEST(QueueTest, ConstructorWithInitializerList) {
  Queue<int> q({1, 2, 3, 4, 5});
  EXPECT_FALSE(q.is_empty());
  EXPECT_EQ(q.head(), 1);
  EXPECT_EQ(q.tail(), 5);
}

TEST(QueueTest, CopyConstructor) {
  Queue<int> original({1, 2, 3});
  Queue<int> copy(original);

  EXPECT_EQ(original.head(), copy.head());
  EXPECT_EQ(original.tail(), copy.tail());
  EXPECT_FALSE(copy.is_empty());
}

TEST(QueueTest, PushOperation) {
  Queue<int> q(3);

  q.push(1);
  EXPECT_FALSE(q.is_empty());
  EXPECT_EQ(q.head(), 1);
  EXPECT_EQ(q.tail(), 1);

  q.push(2);
  EXPECT_EQ(q.head(), 1);
  EXPECT_EQ(q.tail(), 2);

  q.push(3);
  EXPECT_EQ(q.head(), 1);
  EXPECT_EQ(q.tail(), 3);
  EXPECT_TRUE(q.is_full());
}

TEST(QueueTest, PopOperation) {
  Queue<int> q({1, 2, 3, 4, 5});

  EXPECT_EQ(q.head(), 1);
  q.pop();
  EXPECT_EQ(q.head(), 2);

  q.pop();
  EXPECT_EQ(q.head(), 3);

  q.pop();
  EXPECT_EQ(q.head(), 4);

  q.pop();
  EXPECT_EQ(q.head(), 5);

  q.pop();
  EXPECT_TRUE(q.is_empty());
}

TEST(QueueTest, HeadAndTail) {
  Queue<int> q({10, 20, 30});

  EXPECT_EQ(q.head(), 10);
  EXPECT_EQ(q.tail(), 30);

  q.pop();
  EXPECT_EQ(q.head(), 20);
  EXPECT_EQ(q.tail(), 30);

  q.push(40);
  EXPECT_EQ(q.head(), 20);
  EXPECT_EQ(q.tail(), 40);
}

TEST(QueueTest, IsEmpty) {
  Queue<int> q;
  EXPECT_TRUE(q.is_empty());

  q.push(1);
  EXPECT_FALSE(q.is_empty());

  q.pop();
  EXPECT_TRUE(q.is_empty());
}

TEST(QueueTest, IsFull) {
  Queue<int> q(3);

  EXPECT_FALSE(q.is_full());
  q.push(1);
  EXPECT_FALSE(q.is_full());
  q.push(2);
  EXPECT_FALSE(q.is_full());
  q.push(3);
  EXPECT_TRUE(q.is_full());

  q.pop();
  EXPECT_FALSE(q.is_full());
}

TEST(QueueTest, Clear) {
  Queue<int> q = {1, 2, 3, 4, 5};

  EXPECT_FALSE(q.is_empty());
  q.clear();
  EXPECT_TRUE(q.is_empty());

  q.push(10);
  EXPECT_EQ(q.head(), 10);
  EXPECT_EQ(q.tail(), 10);
}