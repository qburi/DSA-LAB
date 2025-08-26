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

    ~PriorityQueue() {
        delete[] arr;
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
        for (int j = 0; j < i; j++) {
            push(tempArray[j]);
        }

        delete[] tempArray;
        if (maxElement == INT_MIN) return -1;
        return maxElement;
    }

    int getMin() {
        int minElement = INT_MAX;
        int* tempArray = new int[MAX_SIZE];
        int i = 0;
        while (!isEmpty()) {
            int element = peek();
            pop();
            tempArray[i++] = element;
            minElement = min(minElement, element);
        }
        for (int j = 0; j < i; j++) {
            push(tempArray[j]);
        }

        delete[] tempArray;
        if (minElement == INT_MAX) return -1;
        return minElement;
    }

    void removeLowestPriority() {
        // we assume the array has size: MAX_SIZE
        // this function should only be called when the queue is full
        int minElement = getMin();
        int* tempArray = new int[MAX_SIZE];
        int i = 0;
        bool seen = false;
        while (! isEmpty()) {
            int element = peek();
            pop();

            if (minElement == element && ! seen) {
                seen = true;
                continue;
            }
            tempArray[i++] = element;
        }
        for (int j = 0; j < i; j++) push(tempArray[j]);
        delete[] tempArray;
    }

    void push(int x) {
        if (isFull()) {
            if (x > getMax()) {
                removeLowestPriority();
                rear = (rear + 1) % MAX_SIZE;
                arr[rear] = x;
                return;
            }
            // cout << "Queue is full. Can't enqueue more elements." << endl; // queue is full
            return;

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
        for (int j = 0; j < i; j++) {
            push(tempArray[j]);
        }
        delete[] tempArray;
    }
};

int main() {
    int n ;
    cin >> n;
    int m; // no of patieents
    cin >> m;
    int* arr = new int[m];
    for (int i = 0; i < m; i++) cin >> arr[i];
    PriorityQueue* pq = new PriorityQueue(n);
    for (int i = 0; i < m; i++) {
        pq->push(arr[i]);
    }
    pq->display();
    delete pq;
    return 0;
}