#include <algorithm>
#include <cstddef>
#include <gtest/gtest.h>
#include <utility>
#include <vector>

#include "../src/practice1_basicsearch.cpp"

GTEST_TEST(Practive2_basicse_BasicVectorCheck_Test, BasicVectorCheck) {
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

GTEST_TEST(Practive2_basicse_BasicVectorCheck_Testv2, BasicVectorCheckv2) {
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

// ============= Тесты =============