#include <bits/stdc++.h>

using namespace std;


void selectionSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++ ) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) minIndex = j;
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

int main() {
    int testCases;
    cin >> testCases;
    for (int z = 0; z < testCases; z++) {
        int n;
        cin >> n;
        int* arr = new int[n];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        selectionSort(arr, n);
        for (int i = 0; i < n / 2; i++) {
            cout << arr[n - i - 1] << " ";
            cout << arr[i] << " ";
        }
        if (n % 2 != 0) {
            cout << arr[n / 2];
        }

        delete[] arr;
    }
    return 0;
}