#include "../include/lib.hpp"
#include <format>
#include <string>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
// 2 4 3 == 3 4 2
// 5 6 4 == 4 6 5
// 7 0 8 += 8 0 7

// 9 9 9 9 9 9 9 9
// 9 9 9 9 9
// 8 9 9 9 9 0 0 0 1
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
  bool inc = false;
  ListNode result(0);
  ListNode *element = &result;
  for (auto a = l1, b = l2; a != nullptr || b != nullptr || inc;
       a = ((a != nullptr) ? a->next : nullptr),
            b = ((b != nullptr) ? b->next : nullptr)) {
    int sum = ((a != nullptr) ? a->val : 0) + ((b != nullptr) ? b->val : 0) +
              (inc ? 1 : 0);
    inc = false;
    if (sum > 9) {
      sum %= 10;
      inc = true;
    }
    element->next = new ListNode();
    element = element->next;
    element->val = sum;
  }
  return result.next;
}