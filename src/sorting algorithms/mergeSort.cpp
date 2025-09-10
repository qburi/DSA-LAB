#include <bits/stdc++.h>

using namespace std;

void merge(vector<int>& arr, vector<int>& leftArray, vector<int>& rightArray);

void mergeSort(vector<int>& arr) {
    if (arr.size() <= 1) return;
    int middle = arr.size() / 2;
    vector<int> leftArray(arr.begin(), arr.begin() + middle);
    vector<int> rightArray(arr.begin() + middle, arr.end());
    merge(arr, leftArray, rightArray);
}

void merge(vector<int>& arr, vector<int>& leftArray, vector<int>& rightArray) {
    int l = 0;
    int r = 0;
    int i = 0;
    while (l < leftArray.size() && r < rightArray.size()) {
        arr[i++] = leftArray[l] < rightArray[r] ? leftArray[l++] : rightArray[r++];
    }
    while (l < leftArray.size()) {
        arr[i++] = leftArray[l++];
    }
    while (r < rightArray.size()) {
        arr[i++] - rightArray[r++];
    }
}

int main() {
    vector<int> arr{1, 5, 10, 2, 10, 20};
    mergeSort(arr);
    for (int num: arr) cout << num << " ";
    cout << endl;
    return 0;
}