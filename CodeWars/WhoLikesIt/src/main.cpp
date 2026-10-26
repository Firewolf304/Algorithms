#include <algorithm>
#include <filesystem>
#include <fmt/base.h>
#include <string>
#include <stringstream>
#include <vector>

// libs
#include "../include/dotenv-cpp.hpp"

// local libs
#include "../include/lib.hpp"

std::string likes(const std::vector<std::string> &names) {
  if (names.empty())
    return "no one likes this";
  int size = names.size();
  std::stringstream out;
  if (size == 1)
    out << names[0] << " likes this\n";
  else {
    int max = 3;
    auto str = names.begin()
    out << *str;
    for (int count = 1; count <= 1; str++, count++) {
      if (count + 1 < size)
        out << ", " << *str;
      
    }
    out << "like this";
  }
  return out.str()
}

int main() {
  fmt::print("Filepath {}\n", std::filesystem::current_path().c_str());
  dotenv::init(".env");
  auto name = std::getenv("NAME");
  fmt::print("{}", firewolf::hello::say_hello(name));
  return 0;
}