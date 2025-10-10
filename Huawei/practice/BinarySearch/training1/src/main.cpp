#include <algorithm>
#include <filesystem>
#include <fmt/base.h>
#include <iostream>

// local libs
#include "../include/practice1_basicsearch.hpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);

  std::vector<int> massive = {1, 2, 3, 4, 5, 6, 7};
  int x = -1;
  std::cout << firewolf::binary_search::search(massive, x) << '\n';
  return 0;
}