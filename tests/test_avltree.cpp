// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2
#include <gtest/gtest.h>

#include <algorithm>
#include <random>
#include <set>
#include <sstream>
#include <vector>

#include "../lib_avltree/avltree.h"

TEST(AVLTreeTest, DefaultConstructor) {
  AVLTree<int, std::string> tree;

  EXPECT_TRUE(tree.isEmpty());
  EXPECT_EQ(tree.size(), 0);
  EXPECT_FALSE(tree.contains(1));
  EXPECT_EQ(tree.find(1), nullptr);
}

TEST(AVLTreeTest, InsertAndFind) {
  AVLTree<int, std::string> tree;

  tree.insert(5, "five");
  tree.insert(3, "three");
  tree.insert(7, "seven");

  EXPECT_FALSE(tree.isEmpty());
  EXPECT_EQ(tree.size(), 3);

  auto* val = tree.find(5);
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, "five");

  val = tree.find(3);
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, "three");

  val = tree.find(7);
  ASSERT_NE(val, nullptr);
  EXPECT_EQ(*val, "seven");

  EXPECT_EQ(tree.find(10), nullptr);
  EXPECT_FALSE(tree.contains(10));
}

TEST(AVLTreeTest, InsertOverwrite) {
  AVLTree<int, std::string> tree;

  tree.insert(5, "five");
  EXPECT_EQ(*tree.find(5), "five");
  EXPECT_EQ(tree.size(), 1);

  tree.insert(5, "FIVE");
  EXPECT_EQ(*tree.find(5), "FIVE");
  EXPECT_EQ(tree.size(), 1);
}

// Повороты

TEST(AVLTreeTest, LL_Rotation) {
  AVLTree<int, std::string> tree;

  // LL случай: вставка в левое поддерево левого ребенка
  // Дерево до балансировки:
  //      30
  //     /
  //    20
  //   /
  //  10

  tree.insert(30, "30");
  tree.insert(20, "20");
  tree.insert(10, "10");  // Должен вызвать правый поворот вокруг 30

  // Ожидаемая структура после LL поворота:
  //      20
  //     /  \
    //   10    30

  EXPECT_EQ(tree.size(), 3);
  EXPECT_TRUE(tree.contains(30));
  EXPECT_TRUE(tree.contains(20));
  EXPECT_TRUE(tree.contains(10));

  // Проверка, что дерево сбалансировано
  EXPECT_TRUE(tree.isBalanced());

  // Проверка высоты (20 - корень, высота 2)
  EXPECT_EQ(tree.getTreeHeight(), 2);
}

TEST(AVLTreeTest, RR_Rotation) {
  AVLTree<int, std::string> tree;

  // RR случай: вставка в правое поддерево правого ребенка
  // Дерево до балансировки:
  //    10
  //      \
  //       20
  //         \
  //          30

  tree.insert(10, "10");
  tree.insert(20, "20");
  tree.insert(30, "30");  // Должен вызвать левый поворот вокруг 10

  // Ожидаемая структура после RR поворота:
  //      20
  //     /  \
  //   10    30

  EXPECT_EQ(tree.size(), 3);
  EXPECT_TRUE(tree.contains(10));
  EXPECT_TRUE(tree.contains(20));
  EXPECT_TRUE(tree.contains(30));

  // Проверка, что дерево сбалансировано
  EXPECT_TRUE(tree.isBalanced());

  // Проверка высоты (20 - корень, высота 2)
  EXPECT_EQ(tree.getTreeHeight(), 2);
}

TEST(AVLTreeTest, LR_Rotation) {
  AVLTree<int, std::string> tree;

  // LR случай: вставка в правое поддерево левого ребенка
  // Дерево до балансировки:
  //      30
  //     /
  //    10
  //      \
  //       20

  tree.insert(30, "30");
  tree.insert(10, "10");
  tree.insert(
      20,
      "20");  // Должен вызвать левый поворот вокруг 10, затем правый вокруг 30

  // Ожидаемая структура после LR поворота:
  //      20
  //     /  \
  //   10    30

  EXPECT_EQ(tree.size(), 3);
  EXPECT_TRUE(tree.contains(30));
  EXPECT_TRUE(tree.contains(10));
  EXPECT_TRUE(tree.contains(20));

  // Проверка, что дерево сбалансировано
  EXPECT_TRUE(tree.isBalanced());

  // Проверка высоты (20 - корень, высота 2)
  EXPECT_EQ(tree.getTreeHeight(), 2);
}

TEST(AVLTreeTest, RL_Rotation) {
  AVLTree<int, std::string> tree;

  // RL случай: вставка в левое поддерево правого ребенка
  // Дерево до балансировки:
  //    10
  //      \
  //       30
  //      /
  //     20

  tree.insert(10, "10");
  tree.insert(30, "30");
  tree.insert(
      20,
      "20");  // Должен вызвать правый поворот вокруг 30, затем левый вокруг 10

  // Ожидаемая структура после RL поворота:
  //      20
  //     /  \
  //   10    30

  EXPECT_EQ(tree.size(), 3);
  EXPECT_TRUE(tree.contains(10));
  EXPECT_TRUE(tree.contains(30));
  EXPECT_TRUE(tree.contains(20));

  // Проверка, что дерево сбалансировано
  EXPECT_TRUE(tree.isBalanced());

  // Проверка высоты (20 - корень, высота 2)
  EXPECT_EQ(tree.getTreeHeight(), 2);
}

// Дополнительный тест для проверки нескольких поворотов подряд
TEST(AVLTreeTest, MultipleRotations) {
  AVLTree<int, std::string> tree;

  // Вставка последовательности, вызывающей множество поворотов
  tree.insert(50, "50");
  tree.insert(30, "30");
  tree.insert(70, "70");
  tree.insert(20, "20");
  tree.insert(40, "40");
  tree.insert(60, "60");
  tree.insert(80, "80");
  tree.insert(10, "10");  // Должен вызвать LL поворот

  EXPECT_TRUE(tree.isBalanced());

  // После вставки 10, дерево должно остаться сбалансированным
  EXPECT_TRUE(tree.contains(50));
  EXPECT_TRUE(tree.contains(30));
  EXPECT_TRUE(tree.contains(70));
  EXPECT_TRUE(tree.contains(20));
  EXPECT_TRUE(tree.contains(40));
  EXPECT_TRUE(tree.contains(60));
  EXPECT_TRUE(tree.contains(80));
  EXPECT_TRUE(tree.contains(10));

  // Высота сбалансированного дерева из 8 элементов должна быть 3 или 4
  int height = tree.getTreeHeight();
  EXPECT_LE(height, 4);
  EXPECT_GE(height, 3);
}

TEST(AVLTreeTest, RemainBalancedAfterManyInserts) {
  AVLTree<int, std::string> tree;

  for (int i = 1; i <= 100; i++) {
    tree.insert(i, std::to_string(i));
    EXPECT_TRUE(tree.isBalanced());
  }

  EXPECT_EQ(tree.size(), 100);
  EXPECT_LE(tree.getTreeHeight(), 8);  // log2(100) ≈ 7
}

TEST(AVLTreeTest, RemainBalancedAfterDeletions) {
  AVLTree<int, std::string> tree;

  for (int i = 1; i <= 50; i++) {
    tree.insert(i, std::to_string(i));
  }

  for (int i = 1; i <= 50; i++) {
    tree.erase(i);
    EXPECT_TRUE(tree.isBalanced());
  }

  EXPECT_TRUE(tree.isEmpty());
}

// =============

TEST(AVLTreeTest, EraseLeafNode) {
  AVLTree<int, std::string> tree;

  tree.insert(5, "five");
  tree.insert(3, "three");
  tree.insert(7, "seven");

  tree.erase(3);
  EXPECT_EQ(tree.size(), 2);
  EXPECT_FALSE(tree.contains(3));
  EXPECT_TRUE(tree.contains(5));
  EXPECT_TRUE(tree.contains(7));
  EXPECT_TRUE(tree.isBalanced());

  tree.erase(7);
  EXPECT_EQ(tree.size(), 1);
  EXPECT_FALSE(tree.contains(7));
  EXPECT_TRUE(tree.contains(5));
  EXPECT_TRUE(tree.isBalanced());
}

TEST(AVLTreeTest, EraseNodeWithOneChild) {
  AVLTree<int, std::string> tree;

  tree.insert(5, "five");
  tree.insert(3, "three");
  tree.insert(2, "two");

  tree.erase(3);
  EXPECT_EQ(tree.size(), 2);
  EXPECT_FALSE(tree.contains(3));
  EXPECT_TRUE(tree.contains(5));
  EXPECT_TRUE(tree.contains(2));
  EXPECT_TRUE(tree.isBalanced());
}

TEST(AVLTreeTest, EraseNodeWithTwoChildren) {
  AVLTree<int, std::string> tree;

  tree.insert(5, "five");
  tree.insert(3, "three");
  tree.insert(7, "seven");
  tree.insert(2, "two");
  tree.insert(4, "four");
  tree.insert(6, "six");
  tree.insert(8, "eight");

  tree.erase(5);
  EXPECT_EQ(tree.size(), 6);
  EXPECT_FALSE(tree.contains(5));

  EXPECT_TRUE(tree.contains(3));
  EXPECT_TRUE(tree.contains(7));
  EXPECT_TRUE(tree.contains(2));
  EXPECT_TRUE(tree.contains(4));
  EXPECT_TRUE(tree.contains(6));
  EXPECT_TRUE(tree.contains(8));

  EXPECT_TRUE(tree.isBalanced());
}

TEST(AVLTreeTest, EraseRootWithNoChildren) {
  AVLTree<int, std::string> tree;

  tree.insert(42, "answer");
  EXPECT_EQ(tree.size(), 1);

  tree.erase(42);
  EXPECT_TRUE(tree.isEmpty());
  EXPECT_EQ(tree.size(), 0);
  EXPECT_EQ(tree.find(42), nullptr);
}

TEST(AVLTreeTest, EraseRootWithOneChild) {
  AVLTree<int, std::string> tree;

  tree.insert(5, "five");
  tree.insert(3, "three");

  tree.erase(5);
  EXPECT_EQ(tree.size(), 1);
  EXPECT_TRUE(tree.contains(3));
  EXPECT_FALSE(tree.contains(5));
  EXPECT_TRUE(tree.isBalanced());
}

TEST(AVLTreeTest, EraseNonExistentKey) {
  AVLTree<int, std::string> tree;

  tree.insert(10, "ten");
  tree.insert(20, "twenty");

  tree.erase(999);
  EXPECT_EQ(tree.size(), 2);
  EXPECT_TRUE(tree.contains(10));
  EXPECT_TRUE(tree.contains(20));
  EXPECT_TRUE(tree.isBalanced());
}

TEST(AVLTreeTest, EraseFromEmptyTree) {
  AVLTree<int, std::string> tree;

  tree.erase(1);
  EXPECT_TRUE(tree.isEmpty());
  EXPECT_EQ(tree.size(), 0);
}

TEST(AVLTreeTest, BalanceAfterEraseCausingLL) {
  AVLTree<int, std::string> tree;

  tree.insert(50, "50");
  tree.insert(30, "30");
  tree.insert(70, "70");
  tree.insert(20, "20");
  tree.insert(40, "40");
  tree.insert(10, "10");

  tree.erase(70);
  tree.erase(40);

  EXPECT_TRUE(tree.contains(50));
  EXPECT_TRUE(tree.contains(30));
  EXPECT_TRUE(tree.contains(20));
  EXPECT_TRUE(tree.contains(10));
  EXPECT_TRUE(tree.isBalanced());
}

TEST(AVLTreeTest, BalanceAfterEraseCausingRR) {
  AVLTree<int, std::string> tree;

  tree.insert(50, "50");
  tree.insert(30, "30");
  tree.insert(70, "70");
  tree.insert(60, "60");
  tree.insert(80, "80");
  tree.insert(90, "90");

  tree.erase(30);
  tree.erase(60);

  EXPECT_TRUE(tree.contains(50));
  EXPECT_TRUE(tree.contains(70));
  EXPECT_TRUE(tree.contains(80));
  EXPECT_TRUE(tree.contains(90));
  EXPECT_TRUE(tree.isBalanced());
}

TEST(AVLTreeTest, CopyConstructor) {
  AVLTree<int, std::string> tree1;
  tree1.insert(1, "one");
  tree1.insert(2, "two");
  tree1.insert(3, "three");

  AVLTree<int, std::string> tree2(tree1);

  EXPECT_EQ(tree2.size(), 3);
  EXPECT_TRUE(tree2.contains(1));
  EXPECT_TRUE(tree2.contains(2));
  EXPECT_TRUE(tree2.contains(3));
  EXPECT_EQ(*tree2.find(2), "two");

  tree2.insert(4, "four");
  EXPECT_EQ(tree2.size(), 4);
  EXPECT_EQ(tree1.size(), 3);
}

TEST(AVLTreeTest, Clear) {
  AVLTree<int, std::string> tree;

  tree.insert(1, "one");
  tree.insert(2, "two");
  tree.insert(3, "three");

  EXPECT_EQ(tree.size(), 3);

  tree.clear();
  EXPECT_TRUE(tree.isEmpty());
  EXPECT_EQ(tree.size(), 0);
  EXPECT_FALSE(tree.contains(1));

  tree.insert(42, "answer");
  EXPECT_EQ(tree.size(), 1);
  EXPECT_EQ(*tree.find(42), "answer");
}

TEST(AVLTreeTest, LargeSequentialInsert) {
  AVLTree<int, std::string> tree;

  for (int i = 1; i <= 1000; i++) {
    tree.insert(i, std::to_string(i));
  }

  EXPECT_EQ(tree.size(), 1000);

  for (int i = 1; i <= 1000; i++) {
    EXPECT_TRUE(tree.contains(i));
    EXPECT_EQ(*tree.find(i), std::to_string(i));
  }
}

TEST(AVLTreeTest, LargeDescendingInsert) {
  AVLTree<int, std::string> tree;

  for (int i = 1000; i >= 1; i--) {
    tree.insert(i, std::to_string(i));
  }

  EXPECT_EQ(tree.size(), 1000);

  for (int i = 1; i <= 1000; i++) {
    EXPECT_TRUE(tree.contains(i));
  }
}

TEST(AVLTreeTest, LargeRandomInsert) {
  AVLTree<int, std::string> tree;
  std::set<int> keys;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 10000);

  for (int i = 0; i < 1000; i++) {
    int key = dis(gen);
    keys.insert(key);
    tree.insert(key, "val_" + std::to_string(key));
  }

  EXPECT_EQ(tree.size(), keys.size());

  for (int key : keys) {
    EXPECT_TRUE(tree.contains(key));
  }
}

TEST(AVLTreeTest, RandomInsertAndErase) {
  AVLTree<int, std::string> tree;
  std::set<int> keys;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 5000);

  for (int i = 0; i < 500; i++) {
    int key = dis(gen);
    if (keys.find(key) == keys.end()) {
      keys.insert(key);
      tree.insert(key, "val_" + std::to_string(key));
    } else {
      keys.erase(key);
      tree.erase(key);
    }
  }

  for (int key : keys) {
    EXPECT_TRUE(tree.contains(key));
  }
}

TEST(AVLTreeTest, PrintSortedEmptyTree) {
  AVLTree<int, std::string> tree;
  std::stringstream ss;
  tree.printSorted(ss);
  EXPECT_EQ(ss.str(), "Tree is empty!\n");
}

TEST(AVLTreeTest, PrintSortedNonEmpty) {
  AVLTree<int, std::string> tree;
  tree.insert(3, "three");
  tree.insert(1, "one");
  tree.insert(2, "two");

  std::stringstream ss;
  tree.printSorted(ss);
  EXPECT_EQ(ss.str(), "1:one 2:two 3:three \n");
}

TEST(AVLTreeTest, DoubleRotation) { 
  AVLTree<int, std::string> tree;
  tree.insert(50, "50");
  tree.insert(40, "40");
  tree.insert(52, "52");
  tree.insert(30, "30");
  tree.insert(45, "45");
  tree.insert(51, "51");
  tree.insert(53, "53");
  tree.insert(20, "20");
  tree.insert(35, "35");
  tree.insert(44, "44");
  tree.insert(46, "46");
  tree.insert(10, "10");

  /*
            45 (h=4)
          /    \
        40      50 (h=3)
       /  \    /  \
      30  44  46  52 (h=2)
     /  \         /  \
    20  35       51  53 (h=1)
   /
  10
  
  */

  /*
          45
        /    \
       40     50
      / \    / \
     30 44  46 52
    / \        / \
   20 35      51 53

  */

  EXPECT_TRUE(tree.isBalanced());
  EXPECT_EQ(tree.getTreeHeight(), 4);
}

TEST(AVLTreeTest, DoubleRotationWithDelete) {
  AVLTree<int, std::string> tree;
  tree.insert(50, "50");
  tree.insert(40, "40");
  tree.insert(60, "60");
  tree.insert(30, "30");
  tree.insert(45, "45");
  tree.insert(55, "55");
  tree.insert(70, "70");
  tree.insert(20, "20");
  tree.insert(54, "54");
  tree.insert(56, "56");
  tree.insert(75, "57");
  tree.insert(90, "90");
  tree.insert(100, "100");
  /*
           50
         /    \
       40      60
      /  \    /  \
     30  45  55   70
    /        / \  / \
   20       54 56 75 90
                      \
                      100
  */
  tree.erase(45);
  /*
           50
         /    \
       40      60
      /       /  \
     30      55   70
    /       / \  / \
   20      54 56 75 90
                     \
                     100

  */

  /*
           60 (h=4)
         /    \
       50      75 (h=3)
      /  \    /  \
     30  55  70  90 (h=2)
    /  \  / \      \
   20  40 54 56    100 (h=1)
  */

  /*
  
    Удаление 45
    |
    LL поворот (40) 
    |
    RL поворот (50)
    |
    Сбалансированное дерево (корень 60)
  */

  EXPECT_TRUE(tree.isBalanced());
  EXPECT_EQ(tree.getTreeHeight(), 4);
}