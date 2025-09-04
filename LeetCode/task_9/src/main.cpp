#include <algorithm>
#include <filesystem>
#include <fmt/base.h>
#include <iostream>

// libs
#include "../include/dotenv-cpp.hpp"

// local libs
#include "../include/lib.hpp"

int main() {
  fmt::print("Filepath {}\n", std::filesystem::current_path().c_str());

  int x = 121;
  fmt::print("{} is palindrome = {}", x, isPalindrome(x));

  return 0;
}