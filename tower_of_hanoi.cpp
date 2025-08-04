#include <bits/stdc++.h>

using namespace std;


void hanoi(int n, char src, char dest, char aux) {
    if (n == 1) {
        cout << "Move disk 1 from " << src << " to " << dest << endl;
        return;
    }
    hanoi(n - 1, src, aux, dest);
    cout << "Move disk " << n << " from " << src << " to " << dest << endl;
    hanoi(n - 1, aux, dest, src);
}


int main() {
    int n;
    cout << "Enter the number of disks: " << endl;
    cin >> n;
    hanoi(n, 'A', 'C', 'B');
    return 0;
}