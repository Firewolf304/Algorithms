#include <iostream>
#include <unordered_map>
#include <vector>

// https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/description/?envType=daily-question&envId=2024-07-18

struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

class Solution {
public:
    int distance;
    std::unordered_map <TreeNode *, std::vector<TreeNode*>> leavesPaths;
    void findLeaves(TreeNode* current, std::vector<TreeNode*> path, std::vector<TreeNode*> & leaves) {
        path.emplace_back(current);
        if(current->left == nullptr && current->right == nullptr) {
            leavesPaths.insert({current, path});
            leaves.emplace_back(current);
            return;
        }
        if(current->right != nullptr)
            findLeaves(current->right, path, leaves);
        if(current->left != nullptr)
            findLeaves(current->left, path, leaves);
    }

    int countPairs(TreeNode* root, int distance) {
        int count = 0;
        std::vector<TreeNode *> leaves;
        findLeaves(root, {}, leaves);
        for(auto p1 = 0; p1 < leaves.size(); p1++) {
            for(auto p2 = p1+1; p2 < leaves.size(); p2++) {
                auto & path1 = leavesPaths[leaves[p1]];
                auto & path2 = leavesPaths[leaves[p2]];
                for(int i = 0; i < std::min(path1.size(), path2.size()); i++) {
                    if (path1[i] != path2[i]) {
                        int dist = path1.size() - i + path2.size() - i;
                        if (dist <= distance) {
                            count++;
                        }
                        break;
                    }
                }
            }
        }
        return count;
    }
};