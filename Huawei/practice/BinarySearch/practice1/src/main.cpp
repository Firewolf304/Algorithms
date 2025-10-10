#include <cmath>
#include <iostream>
#include <vector>

template <typename type>
std::string search2(std::vector<type> vector, type value) {
  int length = vector.size();
  int left = 0;
  int right = length - 1;

  while (left <= right && left >= 0 && right < length) {
    auto mid = left + (right - left) / 2;

    if (vector[mid] == value) {
      return "YES";
    } else if (vector[left] == value) {
      return "YES";
    } else if (vector[right] == value) {
      return "YES";
    }

    if (vector[mid] < value) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return "NO";
}

template <typename type>
std::string search(const std::vector<type> &vector, type value) {
  int length = vector.size();
  int left = 0;
  int right = length;
  int mid;
  while (left < right) {
    mid = (right + left) / 2;

    if (vector[mid] <= value) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  right--;
  if (vector[right] == value)
    return "YES";

  return "NO";
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = -1, k = -1;

  std::cin >> n >> k;
  std::vector<int> massive(n, 0);

  for (int i = 0; i < n; i++) {
    int a;
    std::cin >> massive[i];
  }

  for (int i = 0; i < k; i++) {
    int a;
    std::cin >> a;
    if (a > 1000000000 && a < -1000000000)
      continue;
    std::cout << search<int>(massive, a) << "\n";
  }

  return 0;
}