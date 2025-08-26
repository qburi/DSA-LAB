#include <bits/stdc++.h>


using namespace std;

int getMax(int* arr, int size) {
    if (size < 1) return INT_MIN;
    int maxElement = arr[0];
    for (int i = 1; i < size; i++) {
        maxElement = max(maxElement, arr[i]);
    }
    return maxElement;
}

void countingSort(int* arr, int size) {
    int n = size;
    if (n == 0) return;
    int maxVal = getMax(arr, size);


    int* count = new int[maxVal + 1];
    for (int i = 0; i < maxVal + 1; i++) count[i] = 0;
    int* output = new int[n];

    for (int i = 0; i < n; i++) count[arr[i]]++;

    for (int i = 1; i < maxVal + 1; i++) {
        // we add prefix sum in this loop
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[--count[arr[i]]] = arr[i];
    }

    for (int i = 0; i < n; i++) arr[i] = output[i];
    delete[] count;
    delete[] output;
}

void selectionSort(int* array, int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (array[minIndex] > array[j]) {
                minIndex = j;
            }
        }
        int temp = array[i];
        array[i] = array[minIndex];
        array[minIndex] = temp;
    }
}

int main() {
    int n, m, p;
    cin >> n;
    int* arr1 = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr1[i];
    }
    cin >> m;
    int* arr2 = new int[m];
    for (int i = 0; i < m; i++) {
        cin >> arr2[i];
    }
    cin >> p;
    int* arr3 = new int[p];
    for (int i = 0; i < p; i++) {
        cin >> arr3[i];
    }

    int* final = new int[n + m + p];
    int index = 0;
    for (int i = 0; i < n; i++) {
        final[index++] = arr1[i];
    }
    for (int i = 0; i < m; i++) {
        final[index++] = arr2[i];
    }
    for (int i = 0; i < p; i++) {
        final[index++] = arr3[i];
    }

    countingSort(final, n + m + p);

    for (int i = 0; i < n + m + p; i++) {
        cout << final[i] << " ";
    }
    cout << endl;

    selectionSort(final, n + m + p);
    for (int i = 0; i < n + m + p; i++) {
        cout << final[i] << " ";
    }

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] final;
    return 0;
}