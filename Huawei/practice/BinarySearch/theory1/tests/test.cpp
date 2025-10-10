#include <algorithm>
#include <cstddef>
#include <gtest/gtest.h>
#include <utility>
#include <vector>

#include "../src/practice1_basicsearch.cpp"

GTEST_TEST(Theory_basicse_BasicVectorCheck_Test_method1,
           BasicVectorCheck_method1) {
  std::vector<int> massive = {1, 2, 3, 4, 5, 6};
  int x = 6;
  auto result = firewolf::binary_search::search(massive, x);
  ASSERT_EQ(result, 5);
  x = 5;
  result = firewolf::binary_search::search(massive, x);
  ASSERT_EQ(result, 4);
  x = 4;
  result = firewolf::binary_search::search(massive, x);
  ASSERT_EQ(result, 3);
  x = 3;
  result = firewolf::binary_search::search(massive, x);
  ASSERT_EQ(result, 2);
  x = 2;
  result = firewolf::binary_search::search(massive, x);
  ASSERT_EQ(result, 1);
  x = 1;
  result = firewolf::binary_search::search(massive, x);
  ASSERT_EQ(result, 0);
  x = -1;
  result = firewolf::binary_search::search(massive, x);
  ASSERT_EQ(result, -1);
}

GTEST_TEST(Theory1_basicse_BasicVectorCheck_Testv2_method1,
           BasicVectorCheckv2_method2) {
  std::vector<int> massive = {1, 2, 3, 4, 5, 6, 7};
  int x = 7;
  auto result = firewolf::binary_search::search(massive, x);
  ASSERT_EQ(result, 6);
  x = 6;
  result = firewolf::binary_search::search(massive, x);
  ASSERT_EQ(result, 5);
  x = 5;
  result = firewolf::binary_search::search(massive, x);
  ASSERT_EQ(result, 4);
  x = 4;
  result = firewolf::binary_search::search(massive, x);
  ASSERT_EQ(result, 3);
  x = 3;
  result = firewolf::binary_search::search(massive, x);
  ASSERT_EQ(result, 2);
  x = 2;
  result = firewolf::binary_search::search(massive, x);
  ASSERT_EQ(result, 1);
  x = 1;
  result = firewolf::binary_search::search(massive, x);
  ASSERT_EQ(result, 0);
  x = -1;
  result = firewolf::binary_search::search(massive, x);
  ASSERT_EQ(result, -1);
}

GTEST_TEST(Theory1_basicse_BasicVectorCheck_Test_method2,
           BasicVectorCheck_method2) {
  std::vector<int> massive = {1, 2, 3, 4, 5, 6};
  int x = 6;
  auto result = firewolf::binary_search::search2<int>(massive, x);
  ASSERT_EQ(result, 5);
  x = 5;
  result = firewolf::binary_search::search2<int>(massive, x);
  ASSERT_EQ(result, 4);
  x = 4;
  result = firewolf::binary_search::search2<int>(massive, x);
  ASSERT_EQ(result, 3);
  x = 3;
  result = firewolf::binary_search::search2<int>(massive, x);
  ASSERT_EQ(result, 2);
  x = 2;
  result = firewolf::binary_search::search2<int>(massive, x);
  ASSERT_EQ(result, 1);
  x = 1;
  result = firewolf::binary_search::search2<int>(massive, x);
  ASSERT_EQ(result, 0);
  x = -1;
  result = firewolf::binary_search::search2<int>(massive, x);
  ASSERT_EQ(result, -1);
}

GTEST_TEST(Theory1_basicse_BasicVectorCheck_Testv2_method2,
           BasicVectorCheckv2_method2) {
  std::vector<int> massive = {1, 2, 3, 4, 5, 6, 7};
  int x = 7;
  auto result = firewolf::binary_search::search2<int>(massive, x);
  ASSERT_EQ(result, 6);
  x = 6;
  result = firewolf::binary_search::search2<int>(massive, x);
  ASSERT_EQ(result, 5);
  x = 5;
  result = firewolf::binary_search::search2<int>(massive, x);
  ASSERT_EQ(result, 4);
  x = 4;
  result = firewolf::binary_search::search2<int>(massive, x);
  ASSERT_EQ(result, 3);
  x = 3;
  result = firewolf::binary_search::search2<int>(massive, x);
  ASSERT_EQ(result, 2);
  x = 2;
  result = firewolf::binary_search::search2<int>(massive, x);
  ASSERT_EQ(result, 1);
  x = 1;
  result = firewolf::binary_search::search2<int>(massive, x);
  ASSERT_EQ(result, 0);
  x = -1;
  result = firewolf::binary_search::search2<int>(massive, x);
  ASSERT_EQ(result, -1);
}

GTEST_TEST(Theory1_basicse_BasicVectorCheck_Testv2_method2,
           BasicVectorCheckv3_method2) {
  std::vector<unsigned long long> massive = {100000001, 100000002, 100000003,
                                             100000004, 100000005, 100000006,
                                             100000007, 100000008};
  unsigned long long x = 100000001;
  auto result =
      firewolf::binary_search::search2<unsigned long long>(massive, x);
  ASSERT_EQ(result, 0);
  x = 100000002;
  result = firewolf::binary_search::search2<unsigned long long>(massive, x);
  ASSERT_EQ(result, 1);
  x = 100000003;
  result = firewolf::binary_search::search2<unsigned long long>(massive, x);
  ASSERT_EQ(result, 2);
  x = 100000004;
  result = firewolf::binary_search::search2<unsigned long long>(massive, x);
  ASSERT_EQ(result, 3);
  x = 100000005;
  result = firewolf::binary_search::search2<unsigned long long>(massive, x);
  ASSERT_EQ(result, 4);
  x = 100000006;
  result = firewolf::binary_search::search2<unsigned long long>(massive, x);
  ASSERT_EQ(result, 5);
  x = 100000007;
  result = firewolf::binary_search::search2<unsigned long long>(massive, x);
  ASSERT_EQ(result, 6);
  x = 100000008;
  result = firewolf::binary_search::search2<unsigned long long>(massive, x);
  ASSERT_EQ(result, 7);
}

GTEST_TEST(Theory1_basicse_BasicVectorCheck_Testv2_method2,
           BasicVectorCheckv4_method2) {
  std::vector<int> massive = {-3, -2, 10000000};
  int x = -3;
  auto result = firewolf::binary_search::search2<int>(massive, x);
  ASSERT_EQ(result, 0);
  x = -2;
  result = firewolf::binary_search::search2<int>(massive, x);
  ASSERT_EQ(result, 1);
  x = 10000000;
  result = firewolf::binary_search::search2<int>(massive, x);
  ASSERT_EQ(result, 2);
  x = -22;
  result = firewolf::binary_search::search2<int>(massive, x);
  ASSERT_EQ(result, -1);
}

// ============= Тесты =============