#include <bits/stdc++.h>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int val) : val(val), next(nullptr) {}
    ListNode(int val, ListNode* next) : val(val), next(next) {}
    ListNode() : val(0), next(nullptr) {}
};

ListNode* merge(ListNode* leftArray, ListNode* rightArray) {
    ListNode* head = new ListNode();
    ListNode* tail = head;

    while (leftArray != nullptr && rightArray != nullptr) {
        if (leftArray->val < rightArray->val) {
            tail->next = leftArray;
            leftArray = leftArray->next;
        }
        else {
            tail->next = rightArray;
            rightArray = rightArray->next;
        }
        tail = tail->next;
    }

    if (leftArray != nullptr) {
        tail->next = leftArray;
        tail = tail->next;
    }
    if (rightArray != nullptr) {
        tail->next = rightArray;
    }

    return head->next;
}

ListNode* sortList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return head;

    ListNode* fast = head;
    ListNode* slow = head;
    ListNode* temp = nullptr;

    while (fast != nullptr && fast->next != nullptr) {
        temp = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    if (temp != nullptr) temp->next = nullptr; // we break the two lists
    ListNode* leftArray = sortList(head);
    ListNode* rightArray = sortList(slow);
    return merge(leftArray, rightArray);
}


int main() {
    return 0;
}