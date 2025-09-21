#include <bits/stdc++.h>
#include "TreeNode.h"

using namespace std;


class Solution {
public:
    int minVal;

    void dfs(TreeNode* root, int& k) {
        if (root == nullptr || k <= 0) return;

        dfs(root->left, k);
        k--;
        if (k == 0) {
            minVal = root->val;
            return;
        }
        dfs(root->right, k);
    }
    int kthSmallest(TreeNode* root, int k) {
        if (root == nullptr) return 0;
        dfs(root, k);
        return minVal;
    }
};



int main() {
    return 0;
}