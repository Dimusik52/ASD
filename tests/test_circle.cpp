// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#include <gtest/gtest.h>

#include "../lib_point/point.h"
#include "../lib_circle/circle.h"

TEST(TestCircleLib, is_outside) {
  Circle c1 = Circle(2, 3, 5);
  Circle c2 = Circle(15, 3, 3);
  EXPECT_EQ(calculate_pos(c1, c2), Position::OUTSIDE);
}

TEST(TestCircleLib, is_intersects) {
  Circle c1 = Circle(1, 2, 5);
  Circle c2 = Circle(9, 2, 4);
  EXPECT_EQ(calculate_pos(c9, c10), Position::INTERSECTS);
}

TEST(TestCircleLib, is_equals) {
  // Arrange
  Point point(10, 2);

  // Act & Assert
  EXPECT_EQ(point.get_x(), 10);
  EXPECT_EQ(point.get_y(), 2);
}

TEST(TestCircleLib, is_touch) {
  Circle c1 = Circle(4, 7, 5);
  Circle c2 = Circle(12, 7, 3);
  EXPECT_EQ(calculate_pos(c5, c6), Position::TOUCH);
}

TEST(TestCircleLib, is_inside) {
  Circle c1 = Circle(3, 5, 10);
  Circle c2 = Circle(4, 5, 2);
  EXPECT_EQ(calculate_pos(c17, c18), Position::INSIDE);
}