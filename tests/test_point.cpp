// Copyright (c) 2025 Dmitriy Pikhulya 3824B1PR2

#include <gtest/gtest.h>

#include "../lib_point/point.h"

TEST(TestPointLib, can_create_point) {
  // Arrange
  Point point(10, 2);

  // Act & Assert
  EXPECT_EQ(point.get_x(), 10);
  EXPECT_EQ(point.get_y(), 2);
}