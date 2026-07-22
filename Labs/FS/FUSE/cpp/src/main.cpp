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
  auto name = std::getenv("NAME");
  fmt::print("{}", firewolf::hello::say_hello(name));
  return 0;
}