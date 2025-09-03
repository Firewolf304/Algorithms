#include <iostream>
#include <fmt/base.h>
#include <algorithm>
#include <filesystem>
#include <vector>

#include "monotonous_subarray.cpp"

/*
    Найти максимальный по длине строго монотонный подотрезок массива
    Формулировка:
    Дан массив чисел а_1 … а_n 
    Необходимо найти монотонный подотрезок (то есть строго убывающий или строго возрастающий) максимальной длины и вернуть пару индексов его начала и конца.
    Примеры:
    [2, 7, 5, 3] -> [1, 3]
    [1, 1] -> [1, 1] // or [0, 0]
*/

int main() {
    fmt::print("Hello world!\n");
    
    auto indexes = find_max_monotonous_subarray({2, 7, 5, 3});
    fmt::print("[ {}, {} ]", indexes.first, indexes.second);
    
    return 0;
}