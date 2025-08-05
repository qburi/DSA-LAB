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
        if (isEmpty()) return INT_MAX;
        return stk[ptr];
    }

    bool isEmpty() {
        return ptr == -1;
    }

    bool isFull() {
        return ptr == SIZE - 1;
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

        Stack tempStack(SIZE);
        int minElement = this->peek();

        while (!this->isEmpty()) {
            int element = this->peek();
            minElement = min(minElement, element);
            tempStack.push(element);
            this->pop();
        }

        // build original stack
        while (!tempStack.isEmpty()) {
            this->push(tempStack.peek());
            tempStack.pop();
        }

        return minElement;
    }
};


// --- Test Case 5: Interleaved Operations ---
// This test simulates more complex usage by mixing push, pop, and getMin calls
// to ensure the stack state remains consistent.
int main() {
    cout << "--- Test Case 5: Interleaved Operations ---" << endl;
    MinStack* stk = new MinStack(8);
    stk->push(2);
    stk->push(0);
    stk->push(3);
    stk->push(0);
    cout << "Minimum is: " << stk->getMin() << endl; // Should be 0
    stk->pop(); // Removes a 0
    cout << "Popped. Top is now: " << stk->peek() << endl; // Should be 3
    cout << "Minimum is: " << stk->getMin() << endl; // Should still be 0
    stk->pop(); // Removes 3
    cout << "Popped. Top is now: " << stk->peek() << endl; // Should be 0
    cout << "Minimum is: " << stk->getMin() << endl; // Should still be 0
    stk->pop(); // Removes the last 0
    cout << "Popped. Top is now: " << stk->peek() << endl; // Should be 2
    cout << "Minimum is: " << stk->getMin() << endl; // Should now be 2

    delete stk;
    return 0;
}