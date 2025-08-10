#include <bits/stdc++.h>


using namespace std;

void insertionSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int j = i - 1;
        int temp = arr[i];
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

int main() {
    vector<int> arr{1, 2, 3, 6, 1, 3};
    insertionSort(arr);
    for (int i: arr) cout << i << " ";
    cout << endl;
    return 0;
}