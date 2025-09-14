#include <bits/stdc++.h>
#include "commonDataStructures.h"

using namespace std;

struct Patient {
    string name;
    string symptom;
    int priority; // 1 for non-emergency and 2 for emergency
    Patient() : name(""), symptom(""), priority(0) {};
    Patient(string name, string symptom, int priority) : name(name), symptom(symptom), priority(priority) {}
};


class PriorityLinearQueue {
public:
    int rear;
    int SIZE;
    Patient* patients;
    int front;


    PriorityLinearQueue() {
        SIZE = 100;
        patients = new Patient[SIZE];
        rear = -1;
        front = -1;
    }

    void insertionSort() {
        for (int i = front + 1; i <= rear; i++) {
            int j = i - 1;
            Patient temp = patients[i];
            while (j >= front && patients[j].priority < temp.priority) {
                patients[j + 1] = patients[j];
                j--;
            }
            patients[j + 1] = temp;
        }
    }

    bool isEmpty() {
        return front == - 1 || front > rear;
    }

    bool isFull() {
        return rear == SIZE - 1;
    }

    void enqueue(const Patient& patient) {
        if (isFull()) {
            cout << "Cannot enqueue more" << endl;
            return;
        }
        if (isEmpty()) {
            front = 0;
        }
        rear++;
        patients[rear] = patient;
        insertionSort();
    }

    Patient dequeue() {
        if (isEmpty()) {
            cout << "Cannot dequeue" << endl;
            return Patient();
        }
        // we remove the first position
        Patient patient = patients[front];
        front++;
        return patient;
    }
};

int main() {
    int n;
    cout << "Enter number of patients" << endl;
    cin >> n;
    PriorityLinearQueue pq;
    for (int i = 0; i < n; i++) {
        Patient patient;
        string buffer;
        getline(cin, buffer);
        cout << "Enter name: ";
        getline(cin, patient.name);
        cout << "Enter symptom: ";
        getline(cin, patient.symptom);
        cout << "Enter priority: ";
        cin >> patient.priority;
        pq.enqueue(patient);
    }
    while (! pq.isEmpty()) {
        Patient patient = pq.dequeue();
        cout << "Patient: " << patient.name << endl;;
        cout << "Symptom: " << patient.symptom << endl;
        cout << "Priority: " << patient.priority << endl;
    }
    return 0;
}