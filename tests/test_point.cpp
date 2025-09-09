#include <gtest/gtest.h>

#include "../lib_point/point.h"

TEST(TestPointLib, can_create_point) {
  // Arrange
  Point point(10, 2);

  // Act & Assert
  EXPECT_EQ(point.get_x(), 10);
  EXPECT_EQ(point.get_y(), 2);
}