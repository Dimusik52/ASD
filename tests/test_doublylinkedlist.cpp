// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#include <gtest/gtest.h>
#include <iostream>
#include "../lib_doublylinkedlist/doublylinkedlist.h"

TEST(DoublyLinkedListTest, DefaultConstructor) {
  DoublyLinkedList<int> list;
  EXPECT_TRUE(list.is_empty());
  EXPECT_EQ(list.begin(), list.end());
}

TEST(DoublyLinkedListTest, CopyConstructor) {
  DoublyLinkedList<int> original;
  original.push_back(1);
  original.push_back(2);
  original.push_back(3);

  DoublyLinkedList<int> copy(original);

  std::vector<int> orig_values;
  for (int val : original) {
    orig_values.push_back(val);
  }

  std::vector<int> copy_values;
  for (int val : copy) {
    copy_values.push_back(val);
  }

  EXPECT_EQ(orig_values, copy_values);
  EXPECT_EQ(orig_values, std::vector<int>({1, 2, 3}));
}

TEST(DoublyLinkedListTest, CopyConstructorEmpty) {
  DoublyLinkedList<int> original;
  DoublyLinkedList<int> copy(original);

  EXPECT_TRUE(copy.is_empty());
}

TEST(DoublyLinkedListTest, PushFront) {
  DoublyLinkedList<int> list;
  list.push_front(3);
  list.push_front(2);
  list.push_front(1);

  EXPECT_FALSE(list.is_empty());

  std::vector<int> values;
  for (int val : list) {
    values.push_back(val);
  }
  EXPECT_EQ(values, std::vector<int>({1, 2, 3}));
}

TEST(DoublyLinkedListTest, PushBack) {
  DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  std::vector<int> values;
  for (int val : list) {
    values.push_back(val);
  }
  EXPECT_EQ(values, std::vector<int>({1, 2, 3}));
}

TEST(DoublyLinkedListTest, BidirectionalIteration) {
  DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.push_back(5);

  auto it = list.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);

  --it;
  EXPECT_EQ(*it, 4);
  --it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
}

TEST(DoublyLinkedListTest, PostfixDecrement) {
  DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  auto it = list.begin();
  ++it;
  ++it;  // на 3

  auto old_it = it--;
  EXPECT_EQ(*old_it, 3);
  EXPECT_EQ(*it, 2);
}

TEST(DoublyLinkedListTest, PopFront) {
  DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.pop_front();

  std::vector<int> values;
  for (int val : list) {
    values.push_back(val);
  }
  EXPECT_EQ(values, std::vector<int>({2, 3}));
}

TEST(DoublyLinkedListTest, PopBack) {
  DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.pop_back();

  std::vector<int> values;
  for (int val : list) {
    values.push_back(val);
  }
  EXPECT_EQ(values, std::vector<int>({1, 2}));
}

TEST(DoublyLinkedListTest, PopFrontAndPopBack) {
  DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);

  list.pop_front();  // [2, 3, 4]
  list.pop_back();   // [2, 3]

  std::vector<int> values;
  for (int val : list) {
    values.push_back(val);
  }
  EXPECT_EQ(values, std::vector<int>({2, 3}));
}

TEST(DoublyLinkedListTest, InsertAtPosition) {
  DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(3);

  list.insert(1, 2);  // вставляем между 1 и 3

  std::vector<int> values;
  for (int val : list) {
    values.push_back(val);
  }
  EXPECT_EQ(values, std::vector<int>({1, 2, 3}));
}

TEST(DoublyLinkedListTest, InsertAtFront) {
  DoublyLinkedList<int> list;
  list.push_back(2);
  list.push_back(3);

  list.insert(0, 1);  // в начало

  std::vector<int> values;
  for (int val : list) {
    values.push_back(val);
  }
  EXPECT_EQ(values, std::vector<int>({1, 2, 3}));
}

TEST(DoublyLinkedListTest, InsertAtEnd) {
  DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);

  list.insert(2, 3);  // в конец

  std::vector<int> values;
  for (int val : list) {
    values.push_back(val);
  }
  EXPECT_EQ(values, std::vector<int>({1, 2, 3}));
}

TEST(DoublyLinkedListTest, EraseMiddle) {
  DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.erase(1);  // удаляем 2

  std::vector<int> values;
  for (int val : list) {
    values.push_back(val);
  }
  EXPECT_EQ(values, std::vector<int>({1, 3}));
}

TEST(DoublyLinkedListTest, EraseFirst) {
  DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.erase((size_t) 0);  // удаляем 1

  std::vector<int> values;
  for (int val : list) {
    values.push_back(val);
  }
  EXPECT_EQ(values, std::vector<int>({2, 3}));
}

TEST(DoublyLinkedListTest, EraseLast) {
  DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.erase((size_t) 2);  // удаляем 3

  std::vector<int> values;
  for (int val : list) {
    values.push_back(val);
  }
  EXPECT_EQ(values, std::vector<int>({1, 2}));
}

TEST(DoublyLinkedListTest, ReverseIteration) {
  DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  std::vector<int> values;
  for (auto it = list.rbegin(); it != list.rend(); --it) {
    values.push_back(*it);
  }
  EXPECT_EQ(values, std::vector<int>({3, 2, 1}));
}

TEST(DoublyLinkedListTest, ManualReverseIteration) {
  DoublyLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  auto it = list.rbegin();
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
}

TEST(DoublyLinkedListTest, IteratorPlusEquals) {
  DoublyLinkedList<int> list;
  for (int i = 1; i <= 10; i++) {
    list.push_back(i);
  }

  auto it = list.begin();
  it += 3;
  EXPECT_EQ(*it, 4);

  it += 2;
  EXPECT_EQ(*it, 6);
}

TEST(DoublyLinkedListTest, IteratorMinusEquals) {
  DoublyLinkedList<int> list;
  for (int i = 1; i <= 10; i++) {
    list.push_back(i);
  }

  auto it = list.rbegin();
  it -= 3;
  EXPECT_EQ(*it, 7);

  it -= 2;
  EXPECT_EQ(*it, 5);
}

TEST(DoublyLinkedListTest, Exceptions) {
  DoublyLinkedList<int> list;

  EXPECT_THROW(list.pop_front(), std::logic_error);
  EXPECT_THROW(list.pop_back(), std::logic_error);
  EXPECT_THROW(list.erase((size_t) 0), std::logic_error);

  list.push_back(1);
  EXPECT_THROW(list.erase(5), std::logic_error);
}

TEST(DoublyLinkedListTest, ComplexOperations) {
  DoublyLinkedList<int> list;

  list.push_front(2);
  list.push_back(3);
  list.push_front(1);

  std::vector<int> values;
  for (int val : list) {
    values.push_back(val);
  }
  EXPECT_EQ(values, std::vector<int>({1, 2, 3}));

  list.pop_front();
  list.pop_back();

  values.clear();
  for (int val : list) {
    values.push_back(val);
  }
  EXPECT_EQ(values, std::vector<int>({2}));

  list.insert(0, 1);
  list.insert(2, 3);

  values.clear();
  for (int val : list) {
    values.push_back(val);
  }
  EXPECT_EQ(values, std::vector<int>({1, 2, 3}));

  list.erase(1);

  values.clear();
  for (int val : list) {
    values.push_back(val);
  }
  EXPECT_EQ(values, std::vector<int>({1, 3}));
}

TEST(DoublyLinkedListTest, EmptyListIteration) {
  DoublyLinkedList<int> list;

  int count = 0;
  for (auto it = list.begin(); it != list.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 0);

  count = 0;
  for (auto it = list.rbegin(); it != list.rend(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 0);
}

TEST(DoublyLinkedListTest, ReverseRangeBasedFor) {
  DoublyLinkedList<int> list;
  for (int i = 1; i <= 5; i++) {
    list.push_back(i);
  }

  std::vector<int> reversed_values;
  for (auto it = list.rbegin(); it != list.rend(); --it) {
    reversed_values.push_back(*it);
  }
  EXPECT_EQ(reversed_values, std::vector<int>({5, 4, 3, 2, 1}));

  std::vector<int> forward_values;
  for (auto it = list.begin(); it != list.end(); it++) {
    forward_values.push_back(*it);
  }
  EXPECT_EQ(forward_values, std::vector<int>({1, 2, 3, 4, 5}));
}

TEST(DoublyLinkedListTest, ReverseIteratorModifyValues) {
  DoublyLinkedList<int> list;
  for (int i = 1; i <= 5; i++) {
    list.push_back(i);
  }

  for (auto it = list.rbegin(); it != list.rend(); --it) {
    *it = (*it) * 2;
  }

  std::vector<int> expected = {2, 4, 6, 8, 10};
  std::vector<int> actual;
  for (auto it = list.begin(); it != list.end(); it++) {
    actual.push_back(*it);
  }
  EXPECT_EQ(actual, expected);
}