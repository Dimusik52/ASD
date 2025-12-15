// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#include <gtest/gtest.h>

#include "../lib_stacklist/stacklist.h"

TEST(StackListTest, DefaultConstructor) {
  StackList<int> stack;
  EXPECT_TRUE(stack.is_empty());
  EXPECT_FALSE(stack.is_full());
}

TEST(StackListTest, InitializerListConstructor) {
  StackList<int> stack{1, 2, 3, 4, 5};
  EXPECT_FALSE(stack.is_empty());
  EXPECT_EQ(stack.top(), 5);
}

TEST(StackListTest, CopyConstructor) {
  StackList<int> original{1, 2, 3};
  StackList<int> copy(original);

  EXPECT_FALSE(copy.is_empty());
  EXPECT_EQ(copy.top(), 3);

  original.pop();
  EXPECT_EQ(copy.top(), 3);
}

TEST(StackListTest, ListConstructor) {
  List<int> list;
  list.push_back(10);
  list.push_back(20);
  list.push_back(30);

  StackList<int> stack(list);
  EXPECT_FALSE(stack.is_empty());
  EXPECT_EQ(stack.top(), 30);
}

TEST(StackListTest, PushAndTop) {
  StackList<int> stack;

  stack.push(10);
  EXPECT_EQ(stack.top(), 10);

  stack.push(20);
  EXPECT_EQ(stack.top(), 20);

  stack.push(30);
  EXPECT_EQ(stack.top(), 30);
}

TEST(StackListTest, Pop) {
  StackList<int> stack{1, 2, 3};

  EXPECT_EQ(stack.top(), 3);
  stack.pop();
  EXPECT_EQ(stack.top(), 2);
  stack.pop();
  EXPECT_EQ(stack.top(), 1);
  stack.pop();
  EXPECT_TRUE(stack.is_empty());
}

TEST(StackListTest, PopEmptyStack) {
  StackList<int> stack;
  EXPECT_THROW(stack.pop(), std::logic_error);
}

TEST(StackListTest, TopEmptyStack) {
  StackList<int> stack;
  EXPECT_THROW(stack.top(), std::logic_error);
}

TEST(StackListTest, IsEmpty) {
  StackList<int> stack;
  EXPECT_TRUE(stack.is_empty());

  stack.push(1);
  EXPECT_FALSE(stack.is_empty());

  stack.pop();
  EXPECT_TRUE(stack.is_empty());
}

TEST(StackListTest, IsFull) {
  StackList<int> stack;
  EXPECT_FALSE(stack.is_full());

  for (int i = 0; i < 1000; ++i) {
    stack.push(i);
    EXPECT_FALSE(stack.is_full());
  }
}

TEST(StackListTest, Clear) {
  StackList<int> stack{1, 2, 3, 4, 5};
  EXPECT_FALSE(stack.is_empty());

  stack.clear();
  EXPECT_TRUE(stack.is_empty());
  EXPECT_THROW(stack.top(), std::logic_error);
}