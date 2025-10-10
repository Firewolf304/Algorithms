#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstddef>

#include "../src/lib.cpp"

GTEST_TEST(Lib, SayHello) {
    std::string name = "Test";
    std::string expected = "Hello, Test!";
    std::string result = firewolf::hello::say_hello(name);
    ASSERT_EQ(result, expected);
}

// ============= Тесты =============