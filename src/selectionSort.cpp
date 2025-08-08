#include <bits/stdc++.h>

using namespace std;

void printArray(const vector<int>& array) {
    for (int i: array) cout << i << " ";
    cout << endl;
}

void selectionSort(vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;

        cout << "Iteration: " << i + 1 << ": ";
        printArray(arr);
    }
}


int main() {
    vector<int> arr {49, 10, 210, 201, 31};
    selectionSort(arr);
    return 0;
}