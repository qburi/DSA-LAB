#include <bits/stdc++.h>

using namespace std;

void dfs(vector<vector<int>>& adj, vector<bool>& visited, int node) {

    cout << node << " ";

    for (int v: adj[node]) {
        if (! visited[v]) {
            visited[v] = true;
            dfs(adj, visited, v);
        }
    }
}

int main() {
    int n;
    int e;
    cin >> n >> e;
    vector<vector<int>> adj(n);
    for (int i = 0; i < e; i++) {
        int u;
        int v;
        cin >> u >> v;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }
    for (int i = 0; i < n; i++) {
        // good practice to sort
        sort(adj[i].begin(), adj[i].end());
    }
    vector<bool> visited(n, false);
    visited[0] = true;
    dfs(adj, visited, 0);
    return 0;
}