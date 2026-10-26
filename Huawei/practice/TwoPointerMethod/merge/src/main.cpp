#include <cmath>
#include <iostream>
#include <vector>

int main() {
  // std::ios_base::sync_with_stdio(false);
  // std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  int a_size, b_size;
  std::cin >> a_size >> b_size;
  std::vector<int> a, b;
  for (int i = 0; i < a_size; i++) {
    int str = -1;
    std::cin >> str;
    a.emplace_back(str);
  }

  for (int i = 0; i < b_size; i++) {
    int str = -1;
    std::cin >> str;
    b.emplace_back(str);
  }

  return 0;
}