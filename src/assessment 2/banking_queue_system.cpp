#include <iostream>
#include <string>
#include <utility> // Required for std::pair

using namespace std;

template <typename T>
class CircularQueue {
private:
    int rear;
    int front;
    int MAX_SIZE;
    T* arr;
public:
    CircularQueue(int SIZE) {
        arr = new T[SIZE];
        MAX_SIZE = SIZE;
        rear = -1;
        front = -1;
    }

    ~CircularQueue() {
        delete[] arr;
    }

    void enqueue(T n) {
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

    T dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return T();
        }
        T data = arr[front];
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


// Function to process customers in the queue
void serveCustomers(CircularQueue<pair<string, int>>& q) {
    while (!q.isEmpty()) {
        pair<string, int> customer = q.dequeue();
        cout << "\n--- Serving Customer: " << customer.first << " ---" << endl;

        switch(customer.second) {
            case 1:
                cout << "Check Balance: A report will be sent to the registered mobile number." << endl;
                break;
            case 2:
                cout << "Withdraw Money: Money has been withdrawn successfully." << endl;
                break;
            case 3:
                cout << "Deposit Money: Cash has been deposited successfully." << endl;
                break;
            default:
                cout << "Invalid transaction type found. Please try again later." << endl;
                break;
        }
    }
}

int main() {
    cout << "The Banking System has the following transaction types: " << endl;
    cout << "1. Check Balance" << endl;
    cout << "2. Withdraw money" << endl;
    cout << "3. Deposit money" << endl;
    cout << "------------------------------------------" << endl;

    int n;

    cout << "\nEnter the number of customers: ";
    cin >> n;
    CircularQueue<pair<string, int>>* q = new CircularQueue<pair<string, int>>(n);
    for (int i = 0; i < n; i++) {
        pair<string, int> p;
        cout << "\nEnter details for customer " << i + 1 << endl;
        cout << "Name: ";
        cin >> p.first;
        cout << "Transaction type (1-3): ";
        cin >> p.second;
        q->enqueue(p);
    }

    serveCustomers(*q);
    delete q;
    return 0;
}