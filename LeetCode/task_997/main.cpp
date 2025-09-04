#include <iostream>
#include <vector>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

// https://leetcode.com/problems/find-the-town-judge/description/?source=submission-noac

class Solution {
public:
    int findJudge(int n, std::vector<std::vector<int>>& trust) {
        if(n == 1) return n;
        std::vector<int> trustMap(n);
        std::vector<bool> trustedMap(n);
        int judge = -1, max = -1;
        for(int i = 0; i < trust.size(); i++) {
            trustMap[trust[i][1]-1]++;
            trustedMap[trust[i][0]-1] = true;
        }
        for(int i = 0; i < n; i++) {
            if(n-1 == trustMap[i] && !trustedMap[i]) {
                judge = i + 1;
            }
        }
        return judge;
    }
};
