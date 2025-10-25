#include <bits/stdc++.h>

using namespace std;


bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int getLargestPrime(int n) {
    for (int i = n; i >= 2; i--) {
        if (isPrime(i)) {
            return i;
        }
    }
    return 2;
}

void solution(int* arr, int n, int sizeOfWarehouse) {
    // problem constraints are 0 < stock_id == sz of warehouse <= 1000
    int* hashMap = new int[sizeOfWarehouse];
    for (int i = 0; i < sizeOfWarehouse; i++) {
        // give default value ot each warehouse
        hashMap[i] = 0;
    }

    // THE GUESS: Use a prime modulus for hashing logic
    int primeModulus = getLargestPrime(sizeOfWarehouse);
    
    // Handle the edge case where sizeOfWarehouse is < 2
    if (sizeOfWarehouse <= 1) primeModulus = 1;
    
    for (int i = 0; i < n; i++) {
        int stock_id = arr[i];

        
        int hash = stock_id % primeModulus;
        if (hashMap[hash] == 0) {
            hashMap[hash] = stock_id;
        }
        else {
            // we have to probe to the next available sequence
            // we start probing from index 1
            int j = 1; // j = 0 is already taken
            int counter = 0;
            while (counter < 1000) {
                int newLocation = (hash + j * j) % sizeOfWarehouse;
                if (hashMap[newLocation] == 0) {
                    hashMap[newLocation] = stock_id;
                    break;
                }
                j++;
                counter++;
            }
        }
    }


    for (int i = 0; i < sizeOfWarehouse; i++) {
        cout << i << " = " << hashMap[i] << endl;;
    }

    delete[] hashMap;
}


int main() {
    int sz;
    int n;
    cin >> sz;
    cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    solution(arr, n, sz);
    delete[] arr;
    return 0;
}