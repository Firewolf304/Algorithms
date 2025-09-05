# Add Two Numbers

## ENG

You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example 1:
```
Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.
```
Example 2:
```
Input: l1 = [0], l2 = [0]
Output: [0]
```
Example 3:
```
Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]
```

Constraints:

The number of nodes in each linked list is in the range ```[1, 100]```.
```
0 <= Node.val <= 9
```
It is guaranteed that the list represents a number that does not have leading zeros.

## RUS
Вам даны два непустых связанных списка, представляющих два неотрицательных целых числа. Цифры хранятся в обратном порядке, и каждый из их узлов содержит одну цифру. Сложите два числа и верните сумму в виде связанного списка.

Вы можете предположить, что эти два числа не содержат никакого начального нуля, за исключением самого числа 0.

Пример 1:
```
Входные данные: l1 = [2,4,3], l2 = [5,6,4]
Выходные данные: [7,0,8]
Пояснение: 342 + 465 = 807.
```
Пример 2:
```
Входные данные: l1 = [0], l2 = [0]
Выходные данные: [0]
```
Пример 3:
```
Входные данные: l1 = [9,9,9,9,9,9,9,9], l2 = [9,9,9,9,9]
Выходные данные: [8,9,9,9,0,0,0,1]
```

Ограничения:

Количество узлов в каждом связанном списке находится в диапазоне ``[1, 100]``.
```
0 <= Node.val <= 9
```
Гарантируется, что список представляет собой число, не содержащее начальных нулей.