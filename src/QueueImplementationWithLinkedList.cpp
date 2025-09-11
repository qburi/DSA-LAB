#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct ListNode {
    T val;
    ListNode* next;
    ListNode() : val(T()), next(nullptr) {}
    ListNode(T val) : val(val), next(nullptr) {}
    ListNode(T val, ListNode* next) : val(val), next(next) {}
};


template <typename T>
class Queue {
public:
    ListNode<T>* front;
    ListNode<T>* rear;

    Queue() {
        front = rear = nullptr;
    }

    ~Queue() {
        while (front != nullptr) {
            ListNode<T>* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void push(T val) {
        if (rear != nullptr) {
            rear->next = new ListNode(val);
            rear = rear->next;
        }
        else {
            rear = new ListNode(val);
            front = rear;
        }
    }

    T pop() {
        if (front == nullptr) {
            cout << "Cannot pop. There are no elements" << endl;
            return T();
        }
        T elementPopped = front->val;
        ListNode<T>* temp = front;
        front = front->next;
        delete temp;

        if (front == nullptr) rear = nullptr;
        return elementPopped;
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

int main() {
    Queue<int> q = Queue<int>();
    q.push(10);
    q.push(20);
    q.push(30);
    while (! q.isEmpty()) {
        cout << q.pop() << " ";
    }
    cout << endl;
    return 0;
}