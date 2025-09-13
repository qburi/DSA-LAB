#include <bits/stdc++.h>

using namespace std;

class Stack {
public:
    int ptr;
    int SIZE;
    int* arr;

    Stack() {
        SIZE = 100;
        arr = new int[SIZE];
        ptr = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    bool isFull() {
        return ptr == SIZE - 1;
    }

    bool isEmpty() {
        return ptr == -1;
    }

    int size() {
        return ptr + 1;
    }

    void push(int x) {
        if (isFull()) {
            cout << "Stack Overflow" << endl;
            return;
        }
        ptr++;
        // push is pre-increment operation
        arr[ptr] = x;

    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack Underflow. Cannot pop elements" << endl;
            return;
        }
        ptr--;
    }

    int peek() {
        if (isEmpty()) {
            cout << "Stack Underflow. Cannot peek" << endl;
            return INT_MIN;
        }
        return arr[ptr];
    }
};

class MinStack {
public:
    Stack minStack;
    Stack mainStack;

    void push(int x) {
        if (mainStack.isFull()) {
            cout << "Stack overflow. Cannot add more elements" << endl;
            return;
        }
        if (mainStack.isEmpty()) {
            mainStack.push(x);
            minStack.push(x);
            return;
        }
        if (x <= minStack.peek()) {
            minStack.push(x);
        }
        mainStack.push(x);
    }

    void pop() {
        if (mainStack.isEmpty()) {
            cout << "Stack underflow" << endl;
            return;
        }
        int element = mainStack.peek(); mainStack.pop();
        if (!minStack.isEmpty() && element == minStack.peek()) {
            minStack.pop();
        }
    }

    int getMin() {
        return minStack.peek();
    }
};


int main() {
    MinStack* stk = new MinStack();
    stk->push(10);
    stk->push(-1);
    stk->push(20);
    stk->push(30);
    stk->push(-7);
    cout << stk->getMin() << endl;

    delete stk;
    return 0;
}