#include <bits/stdc++.h>

using namespace std;


vector<vector<int>> subtree_sizes(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> size(n, 1);
    vector<vector<int>> subtree(n);
    for (int i = 0; i < n; i++) {
        subtree[i].push_back(i);
    }
    function<void(int, int)> dfs = [&](int u, int p) {
        for (int v : adj[u]) {
            if (v == p) continue;
            dfs(v, u);
            size[u] += size[v];
            for (int x : subtree[v]) {
                subtree[u].push_back(x);
            }
        }
    };
    dfs(0, -1);
    return subtree;
}

