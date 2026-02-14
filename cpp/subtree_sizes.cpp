#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

// given an adjacency list for a graph, for each node,
// treats it as a root and finds the size of the subtree
// rooted at each child.
vector<vector<pii>> subtree_sizes(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<vector<pii>> subtree(n);

    function<int(int, int)> dfs = [&](int node, int parent) {   
        int res = 1;
        for (int v : adj[node]) {
            if (v == parent) continue;
            int child_size = dfs(v, node);
            res += child_size;
            subtree[node].push_back({v, child_size});
        }
        if (parent != -1) {
            subtree[node].push_back({parent, n - res});
        }
        return res;
    };
    dfs(0, -1);
    return subtree;
}

