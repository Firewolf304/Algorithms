#include <algorithm>
#include <fmt/base.h>
#include <iostream>
#include <unordered_map>

int lengthOfLongestSubstring(std::string s) {
  std::unordered_map<char, int> count;
  count.reserve(256);
  int size = s.size();
  int last = 0;
  int result = 0;
  for (int i = 0; i < size; ++i) {
    auto it = count.find(s[i]);                    // поиск существующих
    if (it != count.end() && it->second >= last) { // ищем ластовую точку совпадения
      last = it->second + 1;                       // запись ласт точки
    }
    count[s[i]] = i;
    result = std::max(result, i - last + 1);
  }
  return result;
}

int lengthOfLongestSubstring_slow(std::string s) {
  std::unordered_map<char, int> count;
  count.reserve(256);
  int size = s.size();
  int max = 0;
  long int ss = 0;
  for (int i = 0; i < size; ++i) {
    if (count.contains(s[i])) {
      if (i - count[s[i]] == 1) {
        count.clear();
        ss = 0;
      } else {
        for (int l = count[s[i]]; l >= 0; --l)
          if (count.contains(s[l]))
            if (count[s[l]] == l) {
              count.erase(s[l]);
              ss--;
            }
      }
    }
    count[s[i]] = i;
    ss++;

    if (max < ss) {
      max = ss;
    }
  }
  return max;
}


int main() {
  fmt::print("Filepath {}\n", std::filesystem::current_path().c_str());
  
  auto d = lengthOfLongestSubstring(std::string("loddktdji"));
  fmt::print("{}", d);
  return 0;
}
