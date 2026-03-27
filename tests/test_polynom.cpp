// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2

#include <gtest/gtest.h>
#include "../lib_polynom/polynom.h"

TEST(PolynomTest, Constructors) {
  Polynom p1;
  EXPECT_TRUE(p1.isEmpty());
  EXPECT_EQ(p1.size(), 0);

  Polynom p2("2x + 3");
  Polynom p3(p2);
  EXPECT_EQ(p3.size(), 2);

  Polynom p4("x^2 + 2x + 1");
  EXPECT_FALSE(p4.isEmpty());
  EXPECT_EQ(p4.size(), 3);
}

TEST(PolynomTest, OperationsWithMonom) {
  Polynom p("2x + 3");
  Monom m1(4.0, 1, 0, 0);  // 4x
  Monom m2(2.0, 0, 0, 0);  // 2

  Polynom sum = p + m1;
  std::stringstream ss;
  ss << sum;
  EXPECT_EQ(ss.str(), "6x + 3");

  Polynom diff = p - m1;
  ss.str("");
  ss << diff;
  EXPECT_EQ(ss.str(), "-2x + 3");

  Polynom prod = p * m2;
  ss.str("");
  ss << prod;
  EXPECT_EQ(ss.str(), "4x + 6");
}

TEST(PolynomTest, OperationsWithPolynom) {
  Polynom p1("2x + 3");
  Polynom p2("4x - 5");

  Polynom sum = p1 + p2;
  std::stringstream ss;
  ss << sum;
  EXPECT_EQ(ss.str(), "6x - 2");

  Polynom diff = p1 - p2;
  ss.str("");
  ss << diff;
  EXPECT_EQ(ss.str(), "-2x + 8");

  Polynom prod = p1 * p2;
  ss.str("");
  ss << prod;
  EXPECT_EQ(ss.str(), "8x^2 + 2x - 15");
}

TEST(PolynomTest, addMonomSortedAndNormalize) {
  Polynom p;

  p.addMonomSorted(Monom(2.0, 2, 1, 0));  // 2x^2y
  p.addMonomSorted(Monom(3.0, 1, 2, 0));  // 3xy^2
  p.addMonomSorted(Monom(4.0, 2, 1, 0));  // 4x^2y

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "6x^2y + 3xy^2");

  size_t oldSize = p.size();
  p.addMonomSorted(Monom(0.0, 1, 1, 1));
  EXPECT_EQ(p.size(), oldSize);
}

TEST(PolynomTest, LexGreater) {
  Polynom p;

  Monom m1(1.0, 3, 0, 0);  // x^3
  Monom m2(1.0, 2, 1, 0);  // x^2y
  Monom m3(1.0, 2, 0, 1);  // x^2z
  Monom m4(1.0, 1, 2, 0);  // xy^2

  EXPECT_TRUE(p.lexGreater(m1, m2));  // x^3 > x^2y
  EXPECT_TRUE(p.lexGreater(m2, m3));  // x^2y > x^2z (y > z)
  EXPECT_TRUE(p.lexGreater(m3, m4));  // x^2z > xy^2

  p.addMonomSorted(m4);
  p.addMonomSorted(m2);
  p.addMonomSorted(m3);
  p.addMonomSorted(m1);

  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "1x^3 + 1x^2y + 1x^2z + 1xy^2");
}

TEST(PolynomTest, ParseVariousFormats) {
  Polynom p1("2x + 3y - 5");
  std::stringstream ss;
  ss << p1;
  EXPECT_EQ(ss.str(), "2x + 3y - 5");

  Polynom p2("x^2 + 2x + 1");
  ss.str("");
  ss << p2;
  EXPECT_EQ(ss.str(), "1x^2 + 2x + 1");

  Polynom p3("2x^2y + 3xy^2 - 4xyz");
  ss.str("");
  ss << p3;
  EXPECT_EQ(ss.str(), "2x^2y + 3xy^2 - 4xyz");

  Polynom p4("-x^3 - 2x^2 + 3x - 4");
  ss.str("");
  ss << p4;
  EXPECT_EQ(ss.str(), "-1x^3 - 2x^2 + 3x - 4");

  Polynom p5("x + y + z");
  ss.str("");
  ss << p5;
  EXPECT_EQ(ss.str(), "1x + 1y + 1z");

  Polynom p6("42");
  ss.str("");
  ss << p6;
  EXPECT_EQ(ss.str(), "42");
}

TEST(PolynomTest, ParseErrors) {
  EXPECT_THROW(Polynom p("2x + @"), std::invalid_argument);

  EXPECT_THROW(Polynom p("x^"), std::invalid_argument);

  EXPECT_THROW(Polynom p("2..5x"), std::invalid_argument);
}

TEST(PolynomTest, EmptyPolynomOperations) {
  Polynom empty;
  Polynom p("2x + 3");

  Polynom sum1 = empty + Monom(5.0, 1, 0, 0);
  std::stringstream ss;
  ss << sum1;
  EXPECT_EQ(ss.str(), "5x");

  Polynom prod1 = empty * Monom(5.0, 1, 0, 0);
  EXPECT_TRUE(prod1.isEmpty());

  Polynom sum2 = empty + p;
  ss.str("");
  ss << sum2;
  EXPECT_EQ(ss.str(), "2x + 3");

  Polynom prod2 = empty * p;
  EXPECT_TRUE(prod2.isEmpty());
}

TEST(PolynomTest, SizeAndEmpty) {
  Polynom p1;
  EXPECT_TRUE(p1.isEmpty());
  EXPECT_EQ(p1.size(), 0);

  Polynom p2("x + y");
  EXPECT_FALSE(p2.isEmpty());
  EXPECT_EQ(p2.size(), 2);

  Polynom p3("0");
  EXPECT_TRUE(p3.isEmpty());
  EXPECT_EQ(p3.size(), 0);
}

TEST(PolynomTest, AssignmentAndCopy) {
  Polynom p1("2x^2 + 3x + 4");
  Polynom p2;

  p2 = p1;
  std::stringstream ss;
  ss << p2;
  EXPECT_EQ(ss.str(), "2x^2 + 3x + 4");

  p1 = p1 + Monom(1.0, 2, 0, 0);
  ss.str("");
  ss << p1;
  EXPECT_EQ(ss.str(), "3x^2 + 3x + 4");

  ss.str("");
  ss << p2;
  EXPECT_EQ(ss.str(), "2x^2 + 3x + 4");
}

TEST(PolynomTest, ZeroCoefficients) {
  Polynom p("0x^2 + 0x + 5");
  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "5");

  Polynom p2 = p + Monom(0.0, 1, 0, 0);
  ss.str("");
  ss << p2;
  EXPECT_EQ(ss.str(), "5");
}

TEST(PolynomTest, MultiplyByZero) {
  Polynom p("2x + 3");
  Monom zero(0.0, 1, 0, 0);

  Polynom result = p * zero;
  EXPECT_TRUE(result.isEmpty());
}

TEST(PolynomTest, OutputEmpty) {
  Polynom p;
  std::stringstream ss;
  ss << p;
  EXPECT_EQ(ss.str(), "0");
}