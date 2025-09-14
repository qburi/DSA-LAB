#include <bits/stdc++.h>

using namespace std;

// Node structure for the linked list
struct ListNode {
    ListNode* next;
    int val;
    ListNode() : next(nullptr), val(0) {};
    ListNode(int val) : next(nullptr), val(val) {};
    ListNode(int val, ListNode* next) : val(val), next(next) {};
};

// Calculates the length of the linked list
int getLength(ListNode* head) {
    int length = 0;
    ListNode* tail = head;
    while (tail != nullptr) {
        length++;
        tail = tail->next;
    }
    return length;
}

// Inserts a value at a specific index in the linked list
void insert(ListNode*& head, int index, int val) {
    int length = getLength(head);
    if (index > length || index < 0) {
        cout << "Index out of bounds" << endl;
        return;
    }
    if (index == 0) {
        ListNode* next = head;
        head = new ListNode(val);
        head->next = next;
        return;
    }
    ListNode* tail = head;
    for (int i = 0; i < index - 1; i++) {
        tail = tail->next;
    }
    ListNode* nodeToAppend = tail->next;
    tail->next = new ListNode(val);
    tail->next->next = nodeToAppend;
}

// Prints all elements of the linked list
void printLinkedList(ListNode* head) {
    ListNode* tail = head;
    while (tail != nullptr) {
        cout << tail->val << endl;
        tail = tail->next;
    }
}

// Deletes a node at a specific index
void deleteIndex(ListNode*& head, int index) {
    int length = getLength(head);
    if (index < 0 || index >= length) {
        cout << "Index out of bounds." << endl;
        return;
    }
    if (index == 0) {
        ListNode* nodeToDelete = head;
        head = head->next;
        delete nodeToDelete;
        return;
    }
    ListNode* tail = head;
    for (int i = 0; i < index - 1; i++) {
        tail = tail->next;
    }
    ListNode* nodeToDelete = tail->next;
    tail->next = tail->next->next;
    delete nodeToDelete;
}

// Merges two sorted linked lists
ListNode* merge(ListNode* l1, ListNode* l2) {
    ListNode* ans = new ListNode(0);
    ListNode* ansHead = ans;
    while (l1 != nullptr && l2 != nullptr) {
        if (l1->val <= l2->val) {
            ans->next = l1;
            l1 = l1->next;
        }
        else {
            ans->next = l2;
            l2 = l2->next;
        }
        ans = ans->next;
    }

    if (l1 != nullptr) {
        ans->next = l1;
    }

    if (l2 != nullptr) {
        ans->next = l2;
    }
    return ansHead->next;
}

// Sorts a linked list using the merge sort algorithm
ListNode* sortList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode* slow = head;
    ListNode* fast = head;
    ListNode* temp = nullptr;
    while (fast != nullptr && fast->next != nullptr) {
        temp = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    if (temp != nullptr) temp->next = nullptr; // break the list into two halves
    ListNode* left = sortList(head);
    ListNode* right = sortList(slow);
    return merge(left, right);
}

// Main function to test the linked list operations
int main() {
    ListNode* head = new ListNode(7);
    ListNode* tail = head;
    tail->next = new ListNode(1);
    tail->next->next = new ListNode(12);
    tail->next->next->next = new ListNode(13);
    tail->next->next->next->next = new ListNode(14);
    
    insert(head, 0, 15);
    printLinkedList(head);
    
    return 0;
}