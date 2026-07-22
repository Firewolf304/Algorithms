#include <algorithm>
#include <cstddef>
#include <gtest/gtest.h>
#include <utility>
#include <vector>

#include "../src/lib.cpp"

GTEST_TEST(Lib, SayHello) {
  std::string name = "Test";
  std::string expected = "Hello, Test!";
  // std::string result = firewolf::hello::say_hello(name);
  ASSERT_EQ(result, expected);
}

// ============= Тесты =============