#pragma once
template <typename type>
int firewolf::binary_search::search2(const std::vector<type> &vector,
                                     type value) {
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
    return right;

  return -1;
}

template <typename type>
int firewolf::binary_search::search(const std::vector<type> &massive,
                                    type value) {
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
