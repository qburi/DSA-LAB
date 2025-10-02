#include <bits/stdc++.h>

using namespace std;

int partition(std::vector<int>& array, int start, int end) {
    int i = start;
    int pivot = array[start];

    for (int j = start + 1; j <= end; j++) {
        if (array[j] < pivot) {
            i++;
            swap(array[i], array[j]);
        }
    }

    swap(array[start], array[i]);
    return i;
}


void quickSort(vector<int>& array, int start, int end) {
    if (start >= end) return;

    int pivotIndex = partition(array, start, end);
    quickSort(array, start, pivotIndex - 1);
    quickSort(array, pivotIndex + 1, end);
}

int main() {
    vector<int> array = {10, 6, 1, 25, 3, 100, 29};
    quickSort(array, 0, static_cast<int>(array.size()) - 1);
    for (int number : array) {
        cout << number << " ";
    }
    cout << endl;
    return 0;
}