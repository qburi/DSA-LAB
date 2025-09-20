#include <bits/stdc++.h>

using namespace std;


int main() {
    int n;
    cin >> n;
    vector<int> arr;
    for (int i = 0; i < n; i++) {
        int element;
        cin >> element;
        arr.push_back(element);
    }
    int element;
    cin >> element;
    arr.push_back(element);
    sort(arr.begin(), arr.end());
    for (int num: arr) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}