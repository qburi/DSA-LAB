#include <bits/stdc++.h>

using namespace std;

int partition(vector<int>& arr, int start, int end);


void quickSort(vector<int>& arr, int start, int end) {
    if (start >= end) return;

    int pivot = partition(arr, start, end);
    quickSort(arr, start, pivot - 1);
    quickSort(arr, pivot + 1, end);
}


int partition(vector<int>& arr, int start, int end) {
    int i = start - 1;
    int pivot = arr[end];

    for (int j = start; j <= end - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    i++;
    int temp = arr[i];
    arr[i] = arr[end];
    arr[end] = temp;
    return i;
}


int main() {
    vector<int> arr{1, 2, 5, 10, 2, 3, 8, -1, -4};
    quickSort(arr, 0, arr.size() - 1);

    for (int num: arr) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}