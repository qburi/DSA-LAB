#include <bits/stdc++.h>
#include "TreeNode.h"

using namespace std;

class Solution {
public:
    TreeNode* findMin(TreeNode* node) {
        // return the inorder successor
        while (node->left != nullptr) node = node->left;
        return node;
    }
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return nullptr;

        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        }
        else {
            // we have to delete the node here
            // case 1: Leaf node is to be deleted
            // case 2: Node which has only one child is to be deleted
            // case 3: Node with two children is to be deleted
            if (root->left == nullptr) {
                // case 1 or case 2
                TreeNode* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                // case 2 confirmed
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }
            else {
                // case 3. We find inorder successor now
                TreeNode* inorderSuccessor = findMin(root->right);
                root->val = inorderSuccessor->val;
                root->right = deleteNode(root->right, inorderSuccessor->val); // will fall under case 1 or 2
            }

        }
        return root;
    }
};


int main() {
    return 0;
}