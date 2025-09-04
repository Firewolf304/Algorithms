#include "../include/lib.hpp"

#include <iostream>

bool isPalindrome1(int x) {
  std::string a = std::to_string(x);
  std::string b = a;
  std::reverse(b.begin(), b.end());
  return a == b;
}

bool isPalindrome2(int x) {
  std::string a = std::to_string((double)x);
  auto start = a.begin();
  auto end = a.rbegin();
  for (; start != a.end() && end != a.rend(); start++, end++) {
    if (*start != *end) {
      return false;
    }
  }
  return true;
}

// 1221 => 10^4; 1221%10 = 1
bool isPalindrome(int x) {
  if (x < 0) {
    return false;
  }
  long reverse = 0;
  auto copy = x;
  while (x > 0) {
    reverse = (reverse * 10) + (x % 10);
    x /= 10;
  }
  return reverse == copy;
}