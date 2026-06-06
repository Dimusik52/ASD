// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2
#include <gtest/gtest.h>

#include <algorithm>
#include <random>
#include <set>
#include <sstream>
#include <vector>

#include "../lib_rbtree/rbtree.h"

TEST(RBTreeTest, DefaultConstructor) {
  RBTree<int, std::string> tree;

  EXPECT_TRUE(tree.isEmpty());
  EXPECT_EQ(tree.size(), 0);
  EXPECT_FALSE(tree.contains(1));
  EXPECT_EQ(tree.find(1), nullptr);
}

TEST(RBTreeTest, InsertAndFind) {
  RBTree<int, std::string> tree;

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

TEST(RBTreeTest, InsertOverwrite) {
  RBTree<int, std::string> tree;

  tree.insert(5, "five");
  EXPECT_EQ(*tree.find(5), "five");
  EXPECT_EQ(tree.size(), 1);

  tree.insert(5, "FIVE");
  EXPECT_EQ(*tree.find(5), "FIVE");
  EXPECT_EQ(tree.size(), 1);
}

TEST(RBTreeTest, RootIsBlack) {
  RBTree<int, std::string> tree;

  tree.insert(10, "ten");
  EXPECT_TRUE(tree.isRBTree());  // Проверяет в том числе корень черный

  tree.insert(20, "twenty");
  tree.insert(30, "thirty");
  EXPECT_TRUE(tree.isRBTree());
}

TEST(RBTreeTest, NoTwoRedsInRow) {
  RBTree<int, std::string> tree;

  // Вставка последовательности, которая может вызвать нарушение
  for (int i = 1; i <= 100; i++) {
    tree.insert(i, std::to_string(i));
    EXPECT_TRUE(tree.isRBTree());  // После каждой вставки проверяем правила
  }
}

TEST(RBTreeTest, BlackHeightConsistency) {
  RBTree<int, std::string> tree;

  for (int i = 1; i <= 50; i++) {
    tree.insert(i, std::to_string(i));
    EXPECT_TRUE(tree.isRBTree());
  }

  // Проверяем, что черная высота одинакова для всех путей
  EXPECT_TRUE(tree.isRBTree());
}

/*
LL случай (правый поворот):
    Вставка в левое поддерево левого ребенка

    [G]                  (P)
   /   \                /   \
 (P)   [U]            (C)   [G]
 /                           \
(C)                           [U]
*/
TEST(RBTreeTest, LL_Rotation) {
  RBTree<int, std::string> tree;

  // LL случай: вставка в левое поддерево левого ребенка
  // Дерево до балансировки:
  //       [30]
  //       /
  //     (20)
  //     /
  //   (10)   <- нарушение (два красных подряд)

  tree.insert(30, "30");
  tree.insert(20, "20");
  tree.insert(10, "10");

  // Ожидаемая структура после LL поворота и перекраски:
  //       [20]          (20 стал черным корнем)
  //       /  \
  //     (10) (30)       (10 и 30 - красные)

  EXPECT_TRUE(tree.isRBTree());
  EXPECT_EQ(tree.size(), 3);
  EXPECT_TRUE(tree.contains(30));
  EXPECT_TRUE(tree.contains(20));
  EXPECT_TRUE(tree.contains(10));
}

/*
RR случай (левый поворот):
    Вставка в правое поддерево правого ребенка

    [G]                  (P)
   /   \                /   \
 [U]   (P)            [G]   (C)
        \            /
        (C)        [U]
*/
TEST(RBTreeTest, RR_Rotation) {
  RBTree<int, std::string> tree;

  // RR случай: вставка в правое поддерево правого ребенка
  // Дерево до балансировки:
  //     [10]
  //       \
  //       (20)
  //         \
  //         (30)   <- нарушение

  tree.insert(10, "10");
  tree.insert(20, "20");
  tree.insert(30, "30");

  // Ожидаемая структура после RR поворота:
  //       [20]
  //       /  \
  //     (10) (30)

  EXPECT_TRUE(tree.isRBTree());
  EXPECT_EQ(tree.size(), 3);
  EXPECT_TRUE(tree.contains(10));
  EXPECT_TRUE(tree.contains(20));
  EXPECT_TRUE(tree.contains(30));
}

/*
LR случай (левый + правый поворот):
    Вставка в правое поддерево левого ребенка

         [G]                  (C)
        /   \                /   \
      (P)   [U]            (P)   [G]
        \                        \
        (C)                      [U]
*/
TEST(RBTreeTest, LR_Rotation) {
  RBTree<int, std::string> tree;

  // LR случай: вставка в правое поддерево левого ребенка
  // Дерево до балансировки:
  //       [30]
  //       /
  //     (10)
  //       \
  //       (20)   <- нарушение

  tree.insert(30, "30");
  tree.insert(10, "10");
  tree.insert(20, "20");

  // Ожидаемая структура после LR поворота:
  //       [20]
  //       /  \
  //     (10) (30)

  EXPECT_TRUE(tree.isRBTree());
  EXPECT_EQ(tree.size(), 3);
  EXPECT_TRUE(tree.contains(30));
  EXPECT_TRUE(tree.contains(10));
  EXPECT_TRUE(tree.contains(20));
}

/*
RL случай (правый + левый поворот):
    Вставка в левое поддерево правого ребенка

       [G]                  (C)
      /   \                /   \
    [U]   (P)            [G]   (P)
          /                    /
        (C)                  [U]
*/
TEST(RBTreeTest, RL_Rotation) {
  RBTree<int, std::string> tree;

  // RL случай: вставка в левое поддерево правого ребенка
  // Дерево до балансировки:
  //     [10]
  //       \
  //       (30)
  //       /
  //     (20)   <- нарушение

  tree.insert(10, "10");
  tree.insert(30, "30");
  tree.insert(20, "20");

  // Ожидаемая структура после RL поворота:
  //       [20]
  //       /  \
  //     (10) (30)

  EXPECT_TRUE(tree.isRBTree());
  EXPECT_EQ(tree.size(), 3);
  EXPECT_TRUE(tree.contains(10));
  EXPECT_TRUE(tree.contains(30));
  EXPECT_TRUE(tree.contains(20));
}

/*
Случай с красным дядей:
         [G]                  (G)
        /   \                /   \
      (P)   (U)            [P]   [U]
      /                    /
    (C)                  (C)

    Затем проверяем G (теперь красный) с его родителем
*/
TEST(RBTreeTest, RedUncleRecoloring) {
  RBTree<int, std::string> tree;

  // Создаем дерево, где при вставке возникнет случай с красным дядей
  //       [50]
  //       /  \
  //     (30) (70)
  //     /
  //   (20)   <- вставляем 20, узел 30 - красный, дядя 70 - красный

  tree.insert(50, "50");
  tree.insert(30, "30");
  tree.insert(70, "70");
  tree.insert(20, "20");

  // После перекраски:
  //       (50) -> затем перекрасится в черный если корень
  //       /  \
  //     [30] [70]
  //     /
  //   (20)

  EXPECT_TRUE(tree.isRBTree());
  EXPECT_EQ(tree.size(), 4);

  // Проверяем, что дети 50 (который мог стать красным) стали черными
  EXPECT_TRUE(tree.isRBTree());
}

TEST(RBTreeTest, MultipleRotationsAndRecolors) {
  RBTree<int, std::string> tree;

  // Вставка последовательности, вызывающей множество поворотов и перекрасок
  tree.insert(50, "50");
  tree.insert(30, "30");
  tree.insert(70, "70");
  tree.insert(20, "20");
  tree.insert(40, "40");
  tree.insert(60, "60");
  tree.insert(80, "80");
  tree.insert(10, "10");

  EXPECT_TRUE(tree.isRBTree());
  EXPECT_EQ(tree.size(), 8);

  // Проверяем наличие всех элементов
  for (int i : {10, 20, 30, 40, 50, 60, 70, 80}) {
    EXPECT_TRUE(tree.contains(i));
  }
}

TEST(RBTreeTest, PrintSortedEmptyTree) {
  RBTree<int, std::string> tree;
  std::stringstream ss;
  tree.printSorted(ss);
  EXPECT_EQ(ss.str(), "Tree is empty!\n");
}

TEST(RBTreeTest, PrintSortedNonEmpty) {
  RBTree<int, std::string> tree;
  tree.insert(3, "three");
  tree.insert(1, "one");
  tree.insert(2, "two");

  std::stringstream ss;
  tree.printSorted(ss);
  EXPECT_EQ(ss.str(), "1:one 2:two 3:three \n");
}

TEST(RBTreeTest, PrintTreeDoesNotCrash) {
  RBTree<int, std::string> tree;
  tree.insert(5, "five");
  tree.insert(3, "three");
  tree.insert(7, "seven");

  std::stringstream ss;
  tree.printTree(ss);
  EXPECT_FALSE(ss.str().empty());
}

TEST(RBTreeTest, CopyConstructor) {
  RBTree<int, std::string> tree1;
  tree1.insert(1, "one");
  tree1.insert(2, "two");
  tree1.insert(3, "three");

  RBTree<int, std::string> tree2(tree1);

  EXPECT_EQ(tree2.size(), 3);
  EXPECT_TRUE(tree2.contains(1));
  EXPECT_TRUE(tree2.contains(2));
  EXPECT_TRUE(tree2.contains(3));
  EXPECT_EQ(*tree2.find(2), "two");
  EXPECT_TRUE(tree2.isRBTree());

  // Изменение tree2 не должно влиять на tree1
  tree2.insert(4, "four");
  EXPECT_EQ(tree2.size(), 4);
  EXPECT_EQ(tree1.size(), 3);
  EXPECT_TRUE(tree1.isRBTree());
  EXPECT_TRUE(tree2.isRBTree());
}

TEST(RBTreeTest, Clear) {
  RBTree<int, std::string> tree;

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
  EXPECT_TRUE(tree.isRBTree());
}


TEST(RBTreeTest, BlackHeightConsistencyAfterManyInserts) {
  RBTree<int, std::string> tree;

  for (int i = 1; i <= 200; i++) {
    tree.insert(i, std::to_string(i));
    EXPECT_TRUE(tree.isRBTree());
  }

  // Получаем черную высоту корня
  int rootBH = tree.getTreeBlackHeight();

  // Функция для проверки черной высоты всех путей уже внутри isRBTree,
  // но можем добавить дополнительную проверку
  EXPECT_GT(rootBH, 0);
  EXPECT_LT(rootBH, 15);
}

// Тест на чередование красных/черных после поворотов
TEST(RBTreeTest, ColorAlternationAfterRotations) {
  RBTree<int, std::string> tree;

  // Эта последовательность вызывает RR, затем LL, затем перекраски
  tree.insert(10, "10");
  tree.insert(20, "20");
  tree.insert(30, "30");  // RR
  tree.insert(25, "25");  // RL
  tree.insert(5, "5");
  tree.insert(3, "3");  // LL
  tree.insert(7, "7");
  tree.insert(8, "8");  // LR

  /*
  ДО (после перекрасок):            ПОСЛЕ LR поворота:
         [25]B                        [25]B
         /   \                        /   \
      (20)R (30)R                   (20)R (30)R
      /                            /
    [10]B                        [10]B
    /  \                         /  \
  (3)R (5)B? <- стал черным?    (3)R (7)B?
        / \                         /  \
      (7)R (?)                    (5)R (8)R
        \
        (8)R <- нарушение!
  */

  /*
           [25]B
          /    \
       (20)R   (30)R
       /         
     [10]B
     /   \
   (3)R  (7)B
        /  \
      (5)R (8)R
  */

  EXPECT_TRUE(tree.isRBTree());
}

TEST(RBTreeTest, DuplicateKeysUpdateValue) {
  RBTree<int, std::string> tree;

  tree.insert(42, "first");
  EXPECT_EQ(*tree.find(42), "first");
  EXPECT_EQ(tree.size(), 1);

  tree.insert(42, "second");
  EXPECT_EQ(*tree.find(42), "second");
  EXPECT_EQ(tree.size(), 1);  // Размер не увеличился

  EXPECT_TRUE(tree.isRBTree());
}

TEST(RBTreeTest, ColorAlternationAfterRotations1) {
  RBTree<int, std::string> tree;

  tree.insert(50, "50");
  tree.insert(30, "30");
  tree.insert(80, "80");
  tree.insert(10, "10");
  tree.insert(40, "40");
  tree.insert(70, "70");
  tree.insert(90, "90");
  tree.insert(5, "5");
  tree.insert(20, "20");
  tree.insert(7, "7");

  tree.printTree();

  EXPECT_TRUE(tree.isRBTree());
}