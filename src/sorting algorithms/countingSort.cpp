#include <bits/stdc++.h>


using namespace std;

void countingSort(vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return;

    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> count(maxVal + 1, 0);
    vector<int> output(n, 0);

    for (int i = 0; i < n; i++) count[arr[i]]++;

    for (int i = 1; i <= maxVal; i++) count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[--count[arr[i]]] = arr[i];
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}


int main() {
    vector<int> arr{1, 2, 5, 10, 2, 3, 8};
    countingSort(arr);

    for (int num: arr) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}