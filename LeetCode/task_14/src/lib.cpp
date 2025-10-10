#include "../include/lib.hpp"

std::string longestCommonPrefix(std::vector<std::string> &strs) {
  for (int i = 0; i <) {
  }
  /*std::unordered_map<char, int> mapper;
  for (auto i : strs) {
    for (auto j = i.begin(); j != i.end(); ++j) {
      if (mapper.contains(*j)) {
        mapper[*j]++;
      } else {
        mapper[*j] = 1;
      }
    }
  }
  auto i = mapper.begin();
  std::string result = "";
  std::vector<std::pair<char, int>> elems(mapper.begin(), mapper.end());
  int size = strs.size();
  std::erase_if(elems, [&size](auto &a) { return a.second != size; });
  for (auto i = elems.rbegin(); i != elems.rend(); i++) {
    result.push_back(i->first);
  }*/

  return result;
}