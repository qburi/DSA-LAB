#include <bits/stdc++.h>

using namespace std;

void countingSort(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return;

    int maxElement = *max_element(arr.begin(), arr.end());
    vector<int> count(maxElement + 1, 0);
    vector<int> output(n, 0);

    for (int i = 0; i < n; i++) count[arr[i]]++;

    for (int i = 1; i < maxElement + 1; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[--count[arr[i]]] = arr[i];
    }

    for (int i = 0; i < n; i++) arr[i] = output[i];
}

int main() {
    vector<int> arr{1, 2, 5, 16, 61, 20};
    countingSort(arr);
    for (int i: arr) cout << i << " ";
    cout << endl;
    return 0;
}