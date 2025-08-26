#include <bits/stdc++.h>

using namespace std;

class PriorityQueue {
public:
    int* arr;
    int MAX_SIZE;
    int front;
    int rear;

    PriorityQueue(int SIZE) {
        MAX_SIZE = SIZE;
        arr = new int[MAX_SIZE];
        front = rear = -1;
    }

    void sort(int* t, int SIZE) {
        for (int i = 1; i < SIZE; i++) {
            int temp = t[i];
            int j = i - 1;
            while (j >= 0 && t[j] > temp) {
                t[j + 1] = t[j];
                j--;
            }
            t[j + 1] = temp;
        }
    }

    void pushWithPriority(int x) {
        int* temp = new int[MAX_SIZE];
        int i = 0;
        while (!isEmpty()) {
            int val = peek();
            pop();
            temp[i++] = val;
        }
        temp[i++] = x;
        sort(temp, i);
        for (int j = 0; j < i; j++) {
            push(temp[j]);
        }
    }

    bool isEmpty() {
        return front == -1;
    }

    bool isFull() {
        return (rear + 1) % MAX_SIZE == front;
    }

    int getMax() {
        int maxElement = INT_MIN;
        int* tempArray = new int[MAX_SIZE];
        int i = 0;
        while (!isEmpty()) {
            int element = peek();
            pop();
            tempArray[i++] = element;
            maxElement = max(maxElement, element);
        }
        arr = tempArray;
        if (maxElement == INT_MIN) return -1;
        return maxElement;
    }

    void removeLeastElement() {}

    void push(int x) {
        if (isFull()) {
            if (x > getMax()) {
                pop(); // pop the least element not the first one
                removeLeastElement();
                pushWithPriority(x);
            } else {
                cout << "Queue is full. Can't enqueue more elements." << endl;
                return;
            }
        }
        if (isEmpty()) {
            front = 0;
        }
        rear = (rear + 1) % MAX_SIZE;
        arr[rear] = x;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Queue is empty. Cannot pop elements" << endl;
            return;
        }
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % MAX_SIZE;
        }
    }

    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty. Cannot peek" << endl;
            return -1;
        }
        return arr[front];
    }

    void display() {
        int* tempArray = new int[MAX_SIZE];
        int i = 0;
        while (!isEmpty()) {
            int element = peek();
            pop();
            tempArray[i++] = element;
            cout << element << " ";
        }
        cout << endl;
        arr = tempArray;
    }
};

int main() {
    int n = 4;
    // cin >> n;
    vector<int> arr{15, 10, 30, 5, 46, 25, 8};
    PriorityQueue* pq = new PriorityQueue(n);
    for (int num : arr) {
        pq->push(num);
    }
    pq->display();
    return 0;
}