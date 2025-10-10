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
  dotenv::init(".env");
  std::vector<std::string> input = {"dog", "racecar", "car"};
  fmt::print("{}", longestCommonPrefix(input));
  return 0;
}