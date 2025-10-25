#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    int e;
    cin >> n >> e;
    vector<vector<int>> adj(n);
    for (int i = 0 ; i < e; i++) {
        int u;
        int v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 0; i < n; i++) {
        // good practice to sort the adj elements
        sort(adj[i].begin(), adj[i].end());
    }

    queue<int> q;
    q.push(0);
    vector<bool> visited(n, false);
    visited[0] = true;

    while (! q.empty()) {
        int node = q.front(); q.pop();
        cout << node << " ";

        for (int neighbor: adj[node]) {
            if (! visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return 0;
}