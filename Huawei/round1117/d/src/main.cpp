#include <algorithm>
#include <filesystem>
#include <iostream>
#include <map>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t = -1;
  std::cin >> t;

  for (auto i = 0; i < t; i++) {
    int S, = -1, q = -1;
    std::cin >> S >> q;
    std::map<int, int> maps;
    for (auto x = 1, y = S; x <= S && y >= 1; x++, y++) {
      if (x * y != S)
        continue;
      maps.emplace(x, y);
    }

    for (auto a = 0; a < q; a++) {
      
    }
  }

  return 0;
}