// Copyright (c) 2026 Dmitriy Pikhulya 3824B1PR2

#include <gtest/gtest.h>
#include "../lib_sortedtablem/sortedtablem.h"

//TEST(SortedTableMTest, InsertMaintainsOrder) {
//  SortedTableM<int, std::string> table;
//
//  table.insert(5, "five");
//  table.insert(1, "one");
//  table.insert(3, "three");
//  table.insert(2, "two");
//  table.insert(4, "four");
//
//  testing::internal::CaptureStdout();
//  table.print(std::cout);
//  std::string output = testing::internal::GetCapturedStdout();
//
//  EXPECT_NE(output.find("1 -> one"), std::string::npos);
//  EXPECT_NE(output.find("2 -> two"), std::string::npos);
//  EXPECT_NE(output.find("3 -> three"), std::string::npos);
//  EXPECT_NE(output.find("4 -> four"), std::string::npos);
//  EXPECT_NE(output.find("5 -> five"), std::string::npos);
//}
//
//TEST(SortedTableMTest, Find) {
//  SortedTableM<int, std::string> table;
//  table.insert(3, "three");
//  table.insert(1, "one");
//  table.insert(2, "two");
//
//  auto* val = table.find(2);
//  ASSERT_NE(val, nullptr);
//  EXPECT_EQ(*val, "two");
//
//  EXPECT_EQ(table.find(4), nullptr);
//}
//
//TEST(SortedTableMTest, Update) {
//  SortedTableM<int, std::string> table;
//  table.insert(1, "one");
//  table.insert(1, "ONE");
//
//  auto* val = table.find(1);
//  ASSERT_NE(val, nullptr);
//  EXPECT_EQ(*val, "ONE");
//}
//
//TEST(SortedTableMTest, Erase) {
//  SortedTableM<int, std::string> table;
//  table.insert(2, "two");
//  table.insert(1, "one");
//  table.insert(3, "three");
//
//  table.erase(2);
//
//  EXPECT_EQ(table.find(2), nullptr);
//  EXPECT_NE(table.find(1), nullptr);
//  EXPECT_NE(table.find(3), nullptr);
//
//  testing::internal::CaptureStdout();
//  table.print(std::cout);
//  std::string output = testing::internal::GetCapturedStdout();
//
//  EXPECT_NE(output.find("1 -> one"), std::string::npos);
//  EXPECT_NE(output.find("3 -> three"), std::string::npos);
//}
//
//TEST(SortedTableMTest, Contains) {
//  SortedTableM<int, std::string> table;
//  table.insert(1, "one");
//  table.insert(2, "two");
//
//  EXPECT_TRUE(table.contains(1));
//  EXPECT_TRUE(table.contains(2));
//  EXPECT_FALSE(table.contains(3));
//}