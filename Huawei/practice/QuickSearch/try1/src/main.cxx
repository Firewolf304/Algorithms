#include <algorithm>
#include <filesystem>
#include <fmt/base.h>
#include <iostream>
#include <vector>

// libs
#include "../include/dotenv-cpp.hpp"

// local libs

int partition(std::vector<int> &array, int low, int high) {
  auto pivot = array[low + (high - low) / 2];
  auto i = low;
  auto j = high;

  while (i <= j) {
    while (array[i] < pivot) {
      i++;
    }
    while (array[j] > pivot) {
      j--;
    }
    if (i > j)
      break;
    std::swap(array[i], array[j]); // IOT instruction: INF cycle
    i++;
    j--;
  }
  return i;
}

void quickSort(std::vector<int> &array, int low, int high) {
  if (low < high) {
    auto p = partition(array, low, high);
    quickSort(array, low, p - 1);
    quickSort(array, p, high);
  }
}

int main() {
  fmt::print("Filepath {}\n", std::filesystem::current_path().c_str());
  std::vector<int> array = {1000, 1, 4, 5, 0, -1, 99};

  quickSort(array, 0, static_cast<int>(array.size()) - 1);

  for (auto var : array) {
    fmt::print("{} ", var);
  }
  fmt::print("\n");
}