// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2

#include <gtest/gtest.h>
#include "../lib_monom/monom.h"

TEST(MonomTest, Constructors) {
  Monom m1(2.5, 1, 2, 3);
  EXPECT_DOUBLE_EQ(m1.getCoefficient(), 2.5);
  EXPECT_EQ(m1.getXPower(), 1);
  EXPECT_EQ(m1.getYPower(), 2);
  EXPECT_EQ(m1.getZPower(), 3);

  Monom m2(3.0, 4, 'x');
  EXPECT_DOUBLE_EQ(m2.getCoefficient(), 3.0);
  EXPECT_EQ(m2.getXPower(), 4);
  EXPECT_EQ(m2.getYPower(), 0);
  EXPECT_EQ(m2.getZPower(), 0);

  Monom m3(1.5, 2, 3, 'x', 'y');
  EXPECT_DOUBLE_EQ(m3.getCoefficient(), 1.5);
  EXPECT_EQ(m3.getXPower(), 2);
  EXPECT_EQ(m3.getYPower(), 3);
  EXPECT_EQ(m3.getZPower(), 0);

  Monom m4(m1);
  EXPECT_EQ(m4.getXPower(), m1.getXPower());
  EXPECT_EQ(m4.getYPower(), m1.getYPower());

  Monom m5;
  EXPECT_DOUBLE_EQ(m5.getCoefficient(), 0.0);
  EXPECT_EQ(m5.getXPower(), 0);
}

TEST(MonomTest, ComparisonOperators) {
  Monom m1(5.0, 2, 1, 3);
  Monom m2(3.0, 2, 1, 3);
  Monom m3(5.0, 2, 1, 4);

  EXPECT_TRUE(m1 == m2);
  EXPECT_FALSE(m1 == m3);

  EXPECT_TRUE(m1 != m3);
  EXPECT_FALSE(m1 != m2);
}

TEST(MonomTest, ArithmeticOperations) {
  Monom m1(2.0, 2, 1, 0);  // 2x^2y
  Monom m2(3.0, 2, 1, 0);  // 3x^2y
  Monom m3(4.0, 1, 2, 0);  // 4xy^2

  Monom sum = m1 + m2;
  EXPECT_DOUBLE_EQ(sum.getCoefficient(), 5.0);
  EXPECT_EQ(sum.getXPower(), 2);
  EXPECT_EQ(sum.getYPower(), 1);

  Monom diff = m2 - m1;
  EXPECT_DOUBLE_EQ(diff.getCoefficient(), 1.0);

  EXPECT_THROW(m1 + m3, std::invalid_argument);

  Monom prod = m1 * m3;
  EXPECT_DOUBLE_EQ(prod.getCoefficient(), 8.0);  // 2*4
  EXPECT_EQ(prod.getXPower(), 3);                // 2+1
  EXPECT_EQ(prod.getYPower(), 3);                // 1+2

  Monom quot = m2 / m1;
  EXPECT_DOUBLE_EQ(quot.getCoefficient(), 1.5);  // 3/2
  EXPECT_EQ(quot.getXPower(), 0);                // 2-2
  EXPECT_EQ(quot.getYPower(), 0);                // 1-1

  Monom zero(0.0, 1, 1, 1);
  EXPECT_THROW(m1 / zero, std::invalid_argument);

  Monom neg = -m1;
  EXPECT_DOUBLE_EQ(neg.getCoefficient(), -2.0);
  EXPECT_EQ(neg.getXPower(), 2);
}

TEST(MonomTest, CompoundAssignment) {
  Monom m1(2.0, 2, 1, 0);
  Monom m2(3.0, 2, 1, 0);
  Monom m3(4.0, 1, 2, 0);

  // +=
  Monom m1_copy = m1;
  m1_copy += m2;
  EXPECT_DOUBLE_EQ(m1_copy.getCoefficient(), 5.0);

  // *=
  m1_copy = m1;
  m1_copy *= m3;
  EXPECT_DOUBLE_EQ(m1_copy.getCoefficient(), 8.0);
  EXPECT_EQ(m1_copy.getXPower(), 3);

  // /=
  m1_copy = m2;
  m1_copy /= m1;
  EXPECT_DOUBLE_EQ(m1_copy.getCoefficient(), 1.5);

  // -=
  m1_copy = m2;
  m1_copy -= m1;
  EXPECT_DOUBLE_EQ(m1_copy.getCoefficient(), 1.0);
}

TEST(MonomTest, Solve) {
  Monom m1(2.0, 2, 1, 3);  // 2 * x^2 * y^1 * z^3

  double result = m1.solve(3.0, 2.0, 1.0);
  // 2 * 9 * 2 * 1 = 36
  EXPECT_DOUBLE_EQ(result, 36.0);

  Monom m2(5.0, 2, 0, 0);  // 5x^2
  EXPECT_DOUBLE_EQ(m2.solve(0.0, 1.0, 1.0), 0.0);

  Monom m3(3.0, -2, 1, 0);  // 3 * x^(-2) * y
  // 3 * 2^(-2) * 4 = 3 * 0.25 * 4 = 3
  EXPECT_DOUBLE_EQ(m3.solve(2.0, 4.0, 1.0), 3.0);

  EXPECT_THROW(m3.solve(0.0, 1.0, 1.0), std::invalid_argument);
}

TEST(MonomTest, PowerCompare) {
  Monom m1(1.0, 2, 3, 4);
  Monom m2(5.0, 2, 3, 4);
  Monom m3(1.0, 2, 3, 5);

  EXPECT_TRUE(m1.powerCompare(m2));
  EXPECT_FALSE(m1.powerCompare(m3));
}

TEST(MonomTest, PowFunction) {
  EXPECT_DOUBLE_EQ(pow(2.0, 0), 1.0);
  EXPECT_DOUBLE_EQ(pow(2.0, 1), 2.0);
  EXPECT_DOUBLE_EQ(pow(2.0, 5), 32.0);
  EXPECT_DOUBLE_EQ(pow(2.0, 10), 1024.0);

  EXPECT_DOUBLE_EQ(pow(2.0, -1), 0.5);
  EXPECT_DOUBLE_EQ(pow(2.0, -3), 0.125);

  EXPECT_DOUBLE_EQ(pow(0.0, 5), 0.0);

  EXPECT_DOUBLE_EQ(pow(0.0, 0), 1.0);

  EXPECT_THROW(pow(0.0, -5), std::invalid_argument);
}