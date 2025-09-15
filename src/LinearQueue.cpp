#include <bits/stdc++.h>

using namespace std;


class LinearQueue {
public:
    int rear;
    int front;
    int *arr;
    int SIZE;

    LinearQueue(int SIZE) {
        front = -1;
        rear = -1;
        this->SIZE = SIZE;
        arr = new int[SIZE];
    }

    LinearQueue() {
        front = -1;
        rear = -1;
        SIZE = 100;
        arr = new int[SIZE];
    }

    ~LinearQueue() {
        delete[] arr;
    }

    bool isEmpty() {
        return front == -1 || front > rear;
    }

    bool isFull() {
        return rear == SIZE - 1;
    }

    void push(int x) {
        if (isFull()) {
            cout << "Queue is full. Cannot enqueue more elements" << endl;
            return;
        }
        if (front == -1) {
            front = 0;
        }
        rear++;
        arr[rear] = x;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Queue underflow" << endl;
            return;
        }
        front++;
    }

    int peek() {
        if (isEmpty()) {
            cout << "Queue Underflow" << endl;
            return INT_MIN;
        }
        return arr[front];
    }
};



