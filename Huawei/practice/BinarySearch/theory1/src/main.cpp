#include <algorithm>
#include <filesystem>
#include <fmt/base.h>
#include <iostream>

// local libs
#include "../include/practice1_basicsearch.hpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);

  std::vector<unsigned long long> massive = {100000001, 100000002, 100000003,
                                             100000004, 100030000, 100000006,
                                             100000007, 100000008};
  unsigned long long x = 100030000;
  int result = firewolf::binary_search::search<unsigned long long>(massive, x);
  std::cout << result << "\n";
  return 0;
}