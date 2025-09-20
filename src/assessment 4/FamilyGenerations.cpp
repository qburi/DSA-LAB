#include <iostream>
#include <vector>

// 1. Define the structure for a tree node
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    // Constructor to initialize a new node
    TreeNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// 2. Create the insert function
TreeNode* insert(TreeNode* root, int value) {
    // If the tree is empty, this new node becomes the root
    if (root == nullptr) {
        return new TreeNode(value);
    }

    // Otherwise, recur down the tree
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else { // Handles greater than or equal to cases
        root->right = insert(root->right, value);
    }
    return root;
}

// A global flag to handle spacing correctly for the first element
bool isFirstElement = true;

// 3. Create the in-order traversal function to print the nodes
void inorderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    // Visit left subtree
    inorderTraversal(root->left);

    // Print the node's data (with correct spacing)
    if (!isFirstElement) {
        std::cout << " ";
    }
    std::cout << root->data;
    isFirstElement = false;

    // Visit right subtree
    inorderTraversal(root->right);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<int> allAges;
    int age;
    for (int i = 0; i < n; ++i) {
        std::cin >> age;
        allAges.push_back(age);
    }
    int guestAge;
    std::cin >> guestAge;
    allAges.push_back(guestAge);

    // 4. Main logic: Build the tree
    TreeNode* root = nullptr; // Start with an empty tree
    for (int currentAge : allAges) {
        root = insert(root, currentAge);
    }

    // 5. Perform in-order traversal to print the sorted result
    inorderTraversal(root);
    std::cout << std::endl;

    // Note: In a real-world application, you would also need to deallocate the memory
    // for the tree nodes to avoid memory leaks. For this lab, it might not be required.

    return 0;
}