#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstddef>

#include "../src/monotonous_subarray.cpp"

static bool IsStrictlyIncreasing(const std::vector<int>& a, size_t l, size_t r) {
    for (size_t i = l + 1; i <= r; ++i) if (!(a[i-1] < a[i])) return false;
    return true;
}

static bool IsStrictlyDecreasing(const std::vector<int>& a, size_t l, size_t r) {
    for (size_t i = l + 1; i <= r; ++i) if (!(a[i-1] > a[i])) return false;
    return true;
}

static bool IsStrictMonotone(const std::vector<int>& a, size_t l, size_t r) {
    return IsStrictlyIncreasing(a, l, r) || IsStrictlyDecreasing(a, l, r);
}

// Эталонная максимальная длина строго монотонного подотрезка (полный перебор)
static size_t BruteMaxLen(const std::vector<int>& a) {
    if (a.empty()) return 0;
    const size_t n = a.size();
    size_t best = 1;
    for (size_t l = 0; l < n; ++l) {
        for (size_t r = l; r < n; ++r) {
            if (IsStrictMonotone(a, l, r)) {
                best = std::max(best, r - l + 1);
            }
        }
    }
    return best;
}

// Общая проверка корректности ответа (границы, монотонность, максимальность)
static void ExpectValidAndMaximal(const std::vector<int>& a,
                                  std::pair<size_t,size_t> ans)
{
    ASSERT_FALSE(a.empty()) << "Поведение на пустом массиве не определяется этими тестами";
    const size_t n = a.size();
    ASSERT_LE(ans.first, ans.second) << "Ожидается l <= r";
    ASSERT_LT(ans.second, n)         << "Ожидается r < n";
    ASSERT_TRUE(IsStrictMonotone(a, ans.first, ans.second)) << "Возвращённый подотрезок не является строго монотонным";
    const size_t got_len = ans.second - ans.first + 1;
    const size_t want_len = BruteMaxLen(a);
    ASSERT_EQ(got_len, want_len) << "Длина подотрезка не максимальна";
}

// ============= Тесты =============

GTEST_TEST(FindMaxMonotonousSubarray, SingleElement) {
    std::vector<int> a{42};
    auto ans = find_max_monotonous_subarray(a);
    ExpectValidAndMaximal(a, ans);
    EXPECT_EQ(ans.first, 0u);
    EXPECT_EQ(ans.second, 0u);
}

GTEST_TEST(FindMaxMonotonousSubarray, AllEqual) {
    std::vector<int> a{5,5,5,5};
    auto ans = find_max_monotonous_subarray(a);
    ExpectValidAndMaximal(a, ans);
    EXPECT_EQ(ans.second - ans.first + 1, 1u);
}

GTEST_TEST(FindMaxMonotonousSubarray, StrictlyIncreasingWholeArray) {
    std::vector<int> a{1,2,3,4,5,6};
    auto ans = find_max_monotonous_subarray(a);
    ExpectValidAndMaximal(a, ans);
    EXPECT_EQ(ans.first, 0u);
    EXPECT_EQ(ans.second, a.size() - 1);
    EXPECT_TRUE(IsStrictlyIncreasing(a, ans.first, ans.second));
}

GTEST_TEST(FindMaxMonotonousSubarray, StrictlyDecreasingWholeArray) {
    std::vector<int> a{9,7,5,3,1};
    auto ans = find_max_monotonous_subarray(a);
    ExpectValidAndMaximal(a, ans);
    EXPECT_EQ(ans.first, 0u);
    EXPECT_EQ(ans.second, a.size() - 1);
    EXPECT_TRUE(IsStrictlyDecreasing(a, ans.first, ans.second));
}

GTEST_TEST(FindMaxMonotonousSubarray, ExampleFromPrompt_Mixed) {
    // [2, 7, 5, 3] -> любой ответ длины 3 корректен (например, [1,3] убывающий)
    std::vector<int> a{2,7,5,3};
    auto ans = find_max_monotonous_subarray(a);
    ExpectValidAndMaximal(a, ans);
    EXPECT_EQ(ans.second - ans.first + 1, 3u);
    EXPECT_TRUE(IsStrictMonotone(a, ans.first, ans.second));
    // Если хотите зафиксировать ровно [1,3], раскомментируйте:
    // EXPECT_EQ(ans.first, 1u);
    // EXPECT_EQ(ans.second, 3u);
}

GTEST_TEST(FindMaxMonotonousSubarray, PlateauBreaksStrictness) {
    // [1,2,2,3] -> макс длина 2 (строго), например [0,1] или [2,3]
    std::vector<int> a{1,2,2,3};
    auto ans = find_max_monotonous_subarray(a);
    ExpectValidAndMaximal(a, ans);
    EXPECT_EQ(ans.second - ans.first + 1, 2u);
}

GTEST_TEST(FindMaxMonotonousSubarray, AlternatingUpDown) {
    // 1,3,2,4,3,5 -> нет строго монотонных > 2
    std::vector<int> a{1,3,2,4,3,5};
    auto ans = find_max_monotonous_subarray(a);
    ExpectValidAndMaximal(a, ans);
    EXPECT_EQ(ans.second - ans.first + 1, 2u);
}

GTEST_TEST(FindMaxMonotonousSubarray, TieBetweenIncAndDec) {
    // Два максимума длины 4 (убывание и возрастание); принять любой.
    std::vector<int> a{10,8,6,4,  1,2,3,4};
    auto ans = find_max_monotonous_subarray(a);
    ExpectValidAndMaximal(a, ans);
    EXPECT_EQ(ans.second - ans.first + 1, 4u);
    EXPECT_TRUE(IsStrictMonotone(a, ans.first, ans.second));
}

GTEST_TEST(FindMaxMonotonousSubarray, NegativesAndZeros) {
    // Возрастающий [-5,-3,-1,0] длины 4 и убывающий [0,-1,-2,-3] длины 4
    std::vector<int> a{-5,-3,-1,0,-1,-2,-3,5};
    auto ans = find_max_monotonous_subarray(a);
    ExpectValidAndMaximal(a, ans);
    EXPECT_EQ(ans.second - ans.first + 1, 4u);
}

GTEST_TEST(FindMaxMonotonousSubarray, LongFlatThenRun) {
    std::vector<int> a{7,7,7,7,7,  9,8,7,6,5,4};
    auto ans = find_max_monotonous_subarray(a);
    ExpectValidAndMaximal(a, ans);
    EXPECT_TRUE(IsStrictlyDecreasing(a, ans.first, ans.second));
    EXPECT_EQ(ans.second - ans.first + 1, 6u); // 9..4
}

GTEST_TEST(FindMaxMonotonousSubarray, RunAtTheEnd) {
    std::vector<int> a{4,3,4,3,   1,2,3,4,5};
    auto ans = find_max_monotonous_subarray(a);
    ExpectValidAndMaximal(a, ans);
    EXPECT_TRUE(IsStrictlyIncreasing(a, ans.first, ans.second));
    EXPECT_EQ(ans.second - ans.first + 1, 5u);
}

GTEST_TEST(FindMaxMonotonousSubarray, RunAtTheBeginning) {
    std::vector<int> a{1,2,3,4,5,  3,3,3,2,2};
    auto ans = find_max_monotonous_subarray(a);
    ExpectValidAndMaximal(a, ans);
    EXPECT_TRUE(IsStrictlyIncreasing(a, ans.first, ans.second));
    EXPECT_EQ(ans.first, 0u);
    EXPECT_EQ(ans.second, 4u);
}

GTEST_TEST(FindMaxMonotonousSubarray, TwoEqualMaxRunsPickAny) {
    std::vector<int> a{1,2,3,  5,4,3,  6,7,8};
    auto ans = find_max_monotonous_subarray(a);
    ExpectValidAndMaximal(a, ans);
    EXPECT_EQ(ans.second - ans.first + 1, 3u);
    EXPECT_TRUE(IsStrictMonotone(a, ans.first, ans.second));
}

GTEST_TEST(FindMaxMonotonousSubarray, BigDeterministic) {
    // 0..999 (inc), шум, затем 1000..1 (dec) — максимум 1000
    std::vector<int> a;
    a.reserve(3000);
    for (int i = 0; i < 1000; ++i) a.push_back(i);
    for (int i = 0; i < 500;  ++i) a.push_back(1000 + (i % 3)); // плато/шум
    for (int i = 1000; i >= 1; --i) a.push_back(i);
    auto ans = find_max_monotonous_subarray(a);
    ExpectValidAndMaximal(a, ans);
    EXPECT_EQ(ans.second - ans.first + 1, 1000u);
}

// ============= Тесты =============