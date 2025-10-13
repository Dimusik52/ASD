// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#include <gtest/gtest.h>

#include "../lib_stack/stack.h"
#include "../lib_TVector/include/TVector.h"

TEST(StackTest, DefaultConstructor) {
  Stack<int> s;
  EXPECT_EQ(s.is_empty(), true);
  EXPECT_EQ(s.is_full(), true);
}

TEST(StackTest, SizeConstructor) {
  Stack<int> s(10);
  EXPECT_EQ(s.is_empty(), true);
  EXPECT_EQ(s.is_full(), false);
  ASSERT_ANY_THROW(s.top());
}

TEST(StackTest, TVectorConstructor) {
  TVector<int> vec({2, 7, 45, -7});
  Stack<int> s(vec);
  EXPECT_EQ(s.is_empty(), false);
  EXPECT_EQ(s.is_full(), true);
  EXPECT_EQ(s.top(), -7);
}

TEST(StackTest, InitListConstructor) {
  Stack<int> s({2, 7, 45, -88});
  EXPECT_EQ(s.is_empty(), false);
  EXPECT_EQ(s.is_full(), true);
  EXPECT_EQ(s.top(), -88);
}

TEST(StackTest, CopyConstructor) {
  Stack<int> s1({9, 0, 0, 6});
  Stack<int> s2(s1);
  EXPECT_EQ(s2.is_empty(), false);
  EXPECT_EQ(s2.is_full(), true);
  EXPECT_EQ(s2.top(), 6);

  s1.pop();
  EXPECT_EQ(s2.top(), 6);
}

TEST(StackTest, PushFromFullExeption) {
  Stack<int> s({9, 0, 0, 6});
  ASSERT_ANY_THROW(s.push(7));
}

TEST(StackTest, PushFromEmpty) {
  Stack<int> s({2, 4});
  s.pop();
  s.pop();
  EXPECT_EQ(s.is_empty(), true);
  s.push(10);
  EXPECT_EQ(s.top(), 10);
}

TEST(StackTest, Push) {
  Stack<int> s(10);
  s.push(-12);
  EXPECT_EQ(s.is_empty(), false);
  EXPECT_EQ(s.is_full(), false);
  EXPECT_EQ(s.top(), -12);
}

TEST(StackTest, PopFromEmpty) {
  Stack<int> s;
  ASSERT_ANY_THROW(s.pop());
}

TEST(StackTest, Pop) {
  Stack<int> s({4, 7, 8});
  s.pop();
  EXPECT_EQ(s.top(), 7);

  s.pop();
  EXPECT_EQ(s.top(), 4);

  s.pop();
  EXPECT_EQ(s.is_empty(), true);
  ASSERT_ANY_THROW(s.top());
}

TEST(StackTest, Clear) {
  Stack<int> s({4, 7, 8});
  s.clear();
  EXPECT_EQ(s.is_empty(), true);
  EXPECT_EQ(s.is_full(), false);
}

TEST(StackTest, TopExeption) {
  Stack<int> s({2});
  EXPECT_EQ(s.top(), 2);
  s.pop();
  ASSERT_ANY_THROW(s.top());
}

TEST(StackTest, Top) {
  Stack<int> s(5);
  s.push(2);
  EXPECT_EQ(s.top(), 2);
  s.push(8);
  EXPECT_EQ(s.top(), 8);
  s.push(14);
  EXPECT_EQ(s.top(), 14);
}

TEST(StackTest, IsEmpty) {
  Stack<int> s;
  EXPECT_EQ(s.is_empty(), true);
}

TEST(StackTest, IsNotEmpty) {
  Stack<int> s({1, 4});
  EXPECT_EQ(s.is_empty(), false);
  s.pop();
  EXPECT_EQ(s.is_empty(), false);
  s.pop();
  EXPECT_EQ(s.is_empty(), true);
}

TEST(StackTest, IsFull) {
  Stack<int> s({-8, 8});
  EXPECT_EQ(s.is_full(), true);
  s.pop();
  EXPECT_EQ(s.is_full(), false);
  s.pop();
  EXPECT_EQ(s.is_full(), false);
}

TEST(StackTest, IsNotFull) {
  Stack<int> s({1, 4, 88});
  EXPECT_EQ(s.is_full(), true);
  s.pop();
  EXPECT_EQ(s.is_full(), false);
  s.pop();
  EXPECT_EQ(s.is_full(), false);
}