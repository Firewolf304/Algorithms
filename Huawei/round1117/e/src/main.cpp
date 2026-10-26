#include <algorithm>
#include <filesystem>
#include <fmt/base.h>
#include <iostream>

int main() {
  fmt::print("Filepath {}\n", std::filesystem::current_path().c_str());
  return 0;
}