#include <algorithm>
#include <filesystem>
#include <fmt/base.h>
#include <iostream>

// local libs
#include "../include/lib.hpp"

int main() {
  fmt::print("Filepath {}\n", std::filesystem::current_path().c_str());
  ListNode l12(3);
  ListNode l11(4, &l12);
  ListNode l1(2, &l11);

  ListNode l22(4);
  ListNode l21(6, &l22);
  ListNode l2(5, &l21);
  auto d = addTwoNumbers(&l1, &l2);
  fmt::print("[");
  for (ListNode *a = d; a != nullptr; a = a->next) {
    fmt::print("{},", a->val);
  }
  fmt::print("]");
  return 0;
}