#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left = nullptr, *right = nullptr;
    TreeNode(int v) : val(v) {}
};

TreeNode* insert(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);
    return root;
}

TreeNode* findMax(TreeNode* node) {
    while (node->right) node = node->right;
    return node;
}

TreeNode* deleteNode(TreeNode* root, int val, bool& found) {
    if (!root) return nullptr;

    if (val < root->val) {
        root->left = deleteNode(root->left, val, found);
    } else if (val > root->val) {
        root->right = deleteNode(root->right, val, found);
    } else {
        found = true;
        if (!root->left || !root->right) {
            return root->left ? root->left : root->right;
        }
        TreeNode* pred = findMax(root->left);
        root->val = pred->val;
        bool dummy = true;
        root->left = deleteNode(root->left, pred->val, dummy);
    }
    return root;
}

void preorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

int main() {
    int n, r, val;
    cin >> n;
    TreeNode* root = nullptr;
    for (int i = 0; i < n; ++i) {
        cin >> val;
        root = insert(root, val);
    }

    cin >> r;
    for (int i = 0; i < r; ++i) {
        cin >> val;
        bool foundNode = false;
        root = deleteNode(root, val, foundNode);
        if (!foundNode) {
            cout << "No such element is in the tree" << endl;
        }
    }
    preorder(root);
    cout << endl;

    return 0;
}

/*
5
50 30 70 60 80
3
3 30 29
*/