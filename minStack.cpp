#include <bits/stdc++.h>

using namespace std;

class Stack {
public:
    int SIZE;
    int* stk;
    int ptr = -1;

    Stack(int n) {
        SIZE = n;
        stk = new int[SIZE];
    }

    ~Stack() {
        delete[] stk;
    }

    void push(int x) {
        if (isFull()) {
            cout << "Stack Overflow" << endl;
        } else {
            stk[++ptr] = x;
        }
    }

    void pop() {
        if (isEmpty()) cout << "Underflow" << endl;
        else ptr--;
    }

    int peek() {
        if (isEmpty()) return INT_MIN;
        return stk[ptr];
    }

    bool isEmpty() {
        return ptr == -1;
    }

    bool isFull() {
        return ptr == SIZE;
    }
};

class MinStack : public Stack {
public:
    MinStack(int n) : Stack(n) {}

    int getMin() {
        if (this->isEmpty()) {
            cout << "Stack is empty, no minimum." << endl;
            return INT_MAX;
        }

        // Use a temporary stack instead of an array
        Stack tempStack(SIZE);
        int minElement = this->peek();

        // 1. Empty the main stack into the temp stack and find the minimum
        while (!this->isEmpty()) {
            int element = this->peek();
            minElement = min(minElement, element);
            tempStack.push(element);
            this->pop();
        }

        // 2. Restore the original stack from the temp stack
        while (!tempStack.isEmpty()) {
            this->push(tempStack.peek());
            tempStack.pop();
        }

        return minElement;
    }
};


int main() {
    MinStack* stk = new MinStack(6);
    stk->push(2);
    stk->push(3);
    stk->push(-1);
    stk->push(100);
    stk->pop();
    cout << "Stack top: " << stk->peek() << endl;
    cout << "Minimum Element: " << stk->getMin() << endl;
    return 0;
}