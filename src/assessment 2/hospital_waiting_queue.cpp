#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Patient {
    string name;
    string symptom;
    int priority; // 2 for emergency, 1 for non-emergency

    // default constructor
    Patient() : name(""), symptom(""), priority(0) {}

    // parametrized constructor
    Patient(const string& n, const string& s, int p) : name(n), symptom(s), priority(p) {}
};

class PriorityLinearQueue {
private:
    int rear;
    int MAX_SIZE;
    Patient* arr;

public:
    PriorityLinearQueue(int SIZE) {
        arr = new Patient[SIZE];
        MAX_SIZE = SIZE;
        // In this simple linear queue, the queue is the segment from index 0 to rear.
        rear = -1;
    }

    ~PriorityLinearQueue() {
        delete[] arr;
    }

    void enqueue(const Patient& patient) {
        if (isFull()) {
            cout << "Queue is full. Can't add more patients." << endl;
            return;
        }
        rear++;
        arr[rear] = patient;

        // Re-sort the entire queue
        insertionSort();
    }

    void insertionSort() {
        for (int i = 1; i <= rear; i++) {
            Patient temp = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j].priority < temp.priority) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = temp;
        }
    }

    Patient dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return Patient();
        }

        // The highest priority patient is always at the front (index 0) after sorting
        Patient data = arr[0];

        // Shift all subsequent elements one position to the left
        for (int i = 0; i < rear; i++) {
            arr[i] = arr[i + 1];
        }

        // Decrease the size of the queue
        rear--;
        return data;
    }

    bool isEmpty() {
        return rear == -1;
    }

    bool isFull() {
        return rear == MAX_SIZE - 1;
    }
};


void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    int n;
    cout << "Enter the number of patients: ";
    cin >> n;

    PriorityLinearQueue waitingRoom(n);

    for (int i = 0; i < n; i++) {
        string name, symptom;
        int priority;

        cout << "\nEnter patient's name: ";
        clearInputBuffer();
        getline(cin, name);
        cout << "Enter symptom: ";
        getline(cin, symptom);
        cout << "Enter state of emergency (2 for Emergency, 1 for Non-Emergency): ";
        cin >> priority;

        Patient patient(name, symptom, priority);
        waitingRoom.enqueue(patient);
    }

    cout << "--- Serving Patients from the Queue ---" << endl;
    cout << "Patients will be served based on priority (Emergency cases first)." << endl;

    int patientNumber = 1;
    while (!waitingRoom.isEmpty()) {
        Patient currentPatient = waitingRoom.dequeue();
        cout << "\n(" << patientNumber++ << ") Now Serving:" << endl;
        cout << "  Name: " << currentPatient.name << endl;
        cout << "  Symptom: " << currentPatient.symptom << endl;
        cout << "  Status: " << (currentPatient.priority == 2 ? "EMERGENCY" : "Non-Emergency") << endl;
    }

    cout << "\nAll patients in the waiting room have been served." << endl;

    return 0;
}