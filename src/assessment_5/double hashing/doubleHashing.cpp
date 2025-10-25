#include <bits/stdc++.h>

using namespace std;

// Define constants based on the problem
#define TABLE_SIZE 20
// A prime number less than TABLE_SIZE for h2
#define R_PRIME 19

/**
 * @brief The first hash function, h1.
 * Deduced from the example: 101 -> 1, 202 -> 2
 */
int h1(int key) {
    return key % TABLE_SIZE;
}

/**
 * @brief The second hash function, h2.
 * This is a standard, safe implementation for double hashing.
 * It's 1 + (key % R) to ensure it's never 0.
 */
int h2(int key) {
    return 1 + (key % R_PRIME);
}

void solution() {
    int n;
    cin >> n;

    // 1. Check for the "FULL" alert
    if (n > TABLE_SIZE) {
        cout << "FULL" << endl;
        return;
    }

    // 2. Initialize all beds to 0 (empty)
    vector<int> hashTable(TABLE_SIZE, 0);
    int kids_placed = 0;

    // 3. Loop 'n' times to read all roll numbers
    for (int k = 0; k < n; k++) {
        int roll_no;
        cin >> roll_no;

        // If the room is already full, we must
        // still read the input but we can't place the kid.
        if (kids_placed == TABLE_SIZE) {
            continue;
        }

        // 4. Find an empty bed using double hashing
        int hash1_val = h1(roll_no);
        int hash2_val = h2(roll_no);
        int i = 0;
        int final_hash;

        while (true) {
            // The double hashing formula
            final_hash = (hash1_val + i * hash2_val) % TABLE_SIZE;

            if (hashTable[final_hash] == 0) {
                // Found an empty bed!
                hashTable[final_hash] = roll_no;
                kids_placed++;
                break; // Exit while loop, move to next kid
            }

            i++; // Collision, probe to the next spot

            // Safety check: if we've probed 20+ times, the table
            // must be full, so we can't place this kid.
            if (i >= TABLE_SIZE) {
                cout << "FULL" << endl;
                break;
            }
        }
    }

    // 5. Print the final bed chart
    for (int i = 0; i < TABLE_SIZE; i++) {
        // Use "\t" for the tab as shown in the output format
        cout << "Bed no " << i << " rollno = " << hashTable[i] << endl;
    }
}

int main() {
    // Faster I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solution();
    return 0;
}
