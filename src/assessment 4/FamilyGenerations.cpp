#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

TreeNode* insert(TreeNode* root, int value) {
    if (root == nullptr) {
        return new TreeNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

bool isFirstElement = true;

void inorderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    inorderTraversal(root->left);

    if (!isFirstElement) {
        cout << " ";
    }
    cout << root->data;
    isFirstElement = false;

    inorderTraversal(root->right);
}

int main() {
    int n;
    cin >> n;

    vector<int> allAges;
    int age;
    for (int i = 0; i < n; ++i) {
        cin >> age;
        allAges.push_back(age);
    }
    int guestAge;
    cin >> guestAge;
    allAges.push_back(guestAge);

    TreeNode* root = nullptr;
    for (int currentAge : allAges) {
        root = insert(root, currentAge);
    }


    inorderTraversal(root);
    cout << endl;

    return 0;
}