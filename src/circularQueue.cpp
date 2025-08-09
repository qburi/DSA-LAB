#include <bits/stdc++.h>

using namespace std;


class CircularQueue {
private:
    int rear;
    int front;
    int MAX_SIZE;
    int* arr;
public:
    CircularQueue(int SIZE) {
        arr = new int[SIZE];
        MAX_SIZE = SIZE;
        rear = -1;
        front = -1;
    }

    ~CircularQueue() {
        delete[] arr;
    }

    void enqueue(int n) {
        // recollect that enqueue operation takes place at the rear position as per FIFO
        if (isFull()) {
            cout << "Queue is full. Can't add more elements" << endl;
            return;
        }
        if (isEmpty()) {
            front = 0;
        }
        rear = (rear + 1) % MAX_SIZE;
        arr[rear] = n;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return INT_MAX;
        }
        int data = arr[front];
        if (front == rear) {
            // last element
            front = -1;
            rear = -1;
        }
        else
            front = (front + 1) % MAX_SIZE;
        return data;
    }

    bool isEmpty() {
        return front == -1;
    }

    bool isFull() {
        return (rear + 1) % MAX_SIZE == front;
    }
};

int main() {

    return 0;
}