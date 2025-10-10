#include "../include/practice1_basicsearch.hpp"
#include <format>
#include <string>

int firewolf::binary_search::search(const std::vector<int> &massive,
                                    int value) {
  auto length = massive.size();
  auto left = 0;
  auto right = length - 1;
  while (left <= right && right < length && left >= 0) {
    int mid = left + (right - left) / 2;
    if (massive[mid] == value)
      return mid;
    else if (massive[left] == value)
      return left;
    else if (massive[right] == value)
      return right;

    if (massive[mid] < value) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return -1;
}