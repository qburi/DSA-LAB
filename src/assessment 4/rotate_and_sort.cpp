#include <bits/stdc++.h>

using namespace std;

void merge(vector<int>& arr, vector<int>& leftArray, vector<int>& rightArray);

void mergeSort(vector<int>& arr) {
    if ((int)arr.size() <= 1) return;
    int middle = (int)arr.size() / 2;
    vector<int> leftArray(arr.begin(), arr.begin() + middle);
    vector<int> rightArray(arr.begin() + middle, arr.end());
    mergeSort(leftArray);
    mergeSort(rightArray);
    merge(arr, leftArray, rightArray);
}

void merge(vector<int>& arr, vector<int>& leftArray, vector<int>& rightArray) {
    int l = 0;
    int r = 0;
    int i = 0;
    while (l < (int)leftArray.size() && r < (int)rightArray.size()) {
        arr[i++] = leftArray[l] < rightArray[r] ? leftArray[l++] : rightArray[r++];
    }
    while (l < (int)leftArray.size()) {
        arr[i++] = leftArray[l++];
    }
    while (r < (int)rightArray.size()) {
        arr[i++] = rightArray[r++];
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> arr;
    for (int i = 0; i < n; i++) {
        int element;
        cin >> element;
        arr.push_back(element);
    }
    int* finalArr = new int[n];
    int index = 0;
    for (int i = m; i < arr.size(); i++) finalArr[index++] = arr[i];
    for (int i = 0; i < m; i++) finalArr[index++] = arr[i];

    for (int i = 0; i < n; i++) cout << finalArr[i] << " ";
    cout << endl;

    mergeSort(arr);
    for (int num: arr) cout << num << " ";
    cout << endl;
    delete[] finalArr;
    return 0;
}