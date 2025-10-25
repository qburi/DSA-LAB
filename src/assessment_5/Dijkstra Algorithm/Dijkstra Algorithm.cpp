#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    int e;
    cin >> n >> e;
    vector<vector<pair<int, int>>> adj(n);

    for (int i = 0; i < e; i++) {
        int u;
        int v;
        int wt;
        cin >> u >> v >> wt;
        adj[u].push_back({v, wt});
    }

    int start;
    cin >> start;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, start});
    vector<int> distances(n, INT_MAX);
    distances[start] = 0;

    while (! pq.empty()) {
        auto p = pq.top(); pq.pop();
        int node = p.second;
        int distance = p.first;

        if (distance > distances[node]) continue;

        for (auto p: adj[node]) {
            int neighborNode = p.first;
            int neighborDist = p.second;
            int newDist = distance + neighborDist;
            if (newDist < distances[neighborNode]) {
                distances[neighborNode] = newDist;
                pq.push({newDist, neighborNode});
            }
        }
    }

    for (int v = 0; v < n; v++) {
        if (distances[v] == INT_MAX)
            cout << "Junction " << v << " : Distance = " << "INF" << endl;
        else cout << "Junction " << v << " : Distance = " << distances[v] << endl;
    }
    return 0;
}