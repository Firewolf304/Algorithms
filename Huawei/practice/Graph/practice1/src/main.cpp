#include <algorithm>
#include <filesystem>
#include <iostream>
#include <ranges>
#include <unordered_map>
#include <vector>

/*
3

3 3
1 2
1 3
3 2

2 2
1 2
2 2

2 2
1 2
2 1
*/
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t = -1;
  char nuller = '\n';
  /*typedef std::vector<std::pair<int, int>> trow;
  std::vector<trow> db;
  std::cin >> t;
  for (auto i : std::views::iota(0, t)) {
    // std::cin >> nuller;
    int n = -1, m = -1;
    std::cin >> n >> m;
    db.emplace_back(trow{});
    for (auto i : std::views::iota(0, m)) {
      int u = -1, v = -1;
      std::cin >> u >> v;
      if (u >= 1 && u <= n && v >= 1 && v <= n) {
        db.rbegin()->emplace_back(std::make_pair(u, v));
      }
    }
  }*/
  typedef std::unordered_map<int, std::vector<int>> trow;
  std::vector<trow> db;
  std::cin >> t;
  for (auto i : std::views::iota(0, t)) {
    // std::cin >> nuller;
    int n = -1, m = -1;
    std::cin >> n >> m;
    db.emplace_back(trow{});
    for (auto i : std::views::iota(0, m)) {
      int u = -1, v = -1;
      std::cin >> u >> v;
      if (u >= 1 && u <= n && v >= 1 && v <= n) {
        auto &beg = db.back();
        beg[u].emplace_back(v);
      }
    }
  }

  for (auto i : db) {
    bool error = false;
    for (auto j : i) {
      int u = j.first;
      auto v = j.second;
      auto petlya = std::find(v.begin(), v.end(), u);
      if (petlya != v.end()) { // петля на ноду
        error = true;
        break;
      }

      // если нашли внутри ноды существующие ноды, то в найденной ноде найти
      // проверяемую
      for (auto k : v) {
        /*auto gran = std::find_if(v.begin(), v.end(), [&i, &u](auto val) {
          return (i.contains(val)) ? std::find(i[val].begin(), i[val].end(),
                                               u) != i[val].end()
                                   : false;
        });*/
        if (i.find(k) != i.end() &&
            std::find(i.at(k).begin(), i.at(k).end(), u) !=
                i.at(k).end()) { // кратное ребро
          error = true;
          break;
        }
      }
      if (error)
        break;
    }
    if (error) {
      std::cout << "NO\n";
    } else {
      std::cout << "YES\n";
    }
  }

  return 0;
}