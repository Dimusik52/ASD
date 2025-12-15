// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#include <gtest/gtest.h>

#include "../lib_queuelist/queuelist.h"

TEST(QueueListTest, BasicOperations) {
  QueueList<int> queue;
  EXPECT_TRUE(queue.is_empty());

  queue.push(1);
  EXPECT_EQ(queue.head(), 1);
  EXPECT_EQ(queue.tail(), 1);

  queue.push(2);
  EXPECT_EQ(queue.head(), 1);
  EXPECT_EQ(queue.tail(), 2);

  queue.push(3);
  EXPECT_EQ(queue.head(), 1);
  EXPECT_EQ(queue.tail(), 3);

  queue.pop();
  EXPECT_EQ(queue.head(), 2);
  EXPECT_EQ(queue.tail(), 3);

  queue.pop();
  EXPECT_EQ(queue.head(), 3);
  EXPECT_EQ(queue.tail(), 3);

  queue.pop();
  EXPECT_TRUE(queue.is_empty());
}

TEST(QueueListTest, InitializerList) {
  QueueList<int> queue{1, 2, 3};
  EXPECT_EQ(queue.head(), 1);
  EXPECT_EQ(queue.tail(), 3);
}

TEST(QueueListTest, CopyConstructor) {
  QueueList<int> queue1{1, 2, 3};
  QueueList<int> queue2(queue1);

  EXPECT_EQ(queue2.head(), 1);
  EXPECT_EQ(queue2.tail(), 3);
}

TEST(QueueListTest, Clear) {
  QueueList<int> queue{1, 2, 3};
  queue.clear();
  EXPECT_TRUE(queue.is_empty());
  EXPECT_THROW(queue.head(), std::logic_error);
}