#include <bits/stdc++.h>

using namespace std;

#define ll long long

// Disjoint set union
int find(vector<int>& dsu, int node) {

    if (dsu[node] == node) {
        return node;
    } else {
        return dsu[node] = find(dsu,dsu[node]);
    }
}

void union_sets(vector<int>& dsu, vector<int>& sizes, int a, int b) {

    int x = find(dsu, a);
    int y = find(dsu, b);

    if (x == y) {
        return;
    } else if (sizes[x] < sizes[y]) {
        swap(x,y);
    }

    dsu[y] = x;
    sizes[x] += sizes[y];
}

// Check if subgraph is splittable, or bipartite
bool splittable(vector<vector<int>>& adj, int node) {

    unordered_map<int, int> color;
    queue<int> q;

    // Assign the first color to the start node
    color[node] = 0;
    q.push(node);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (int x : adj[curr]) {
            // If neighbor not colored yet, color it with opposite color
            if (color.find(x) == color.end()) {
                color[x] = 1 - color[curr];
                q.push(x);
            }
            // If neighbor has same color, not bipartite
            else if (color[x] == color[curr]) {
                return false;
            }
        }
    }

    return true;
}

int main() {

    int N, M;
    cin >> N >> M;

    vector<int> dsu(N);
    vector<int> sizes(N, 1);
    for (int i = 0; i < N; i++) {
        dsu[i] = i;
    }

    vector<vector<int>> adj(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);

        union_sets(dsu, sizes, u, v);
    }

    // Find the total number of components, including splits.
    unordered_set<int> seen;
    ll components = 0;
    ll splits = 0;
    ll individual = 0;
    for (int i = 0; i < N; i++) {
        int rep = find(dsu, i);
        if (seen.count(rep)) {
            continue;
        }
        seen.insert(rep);
        components++;
        if (sizes[rep] > 1 && splittable(adj, rep)) {
            splits++;
        } else if (sizes[rep] == 1) {
            individual++;
        }
    }

    ll output = 0;
    seen.clear();
    for (int i = 0; i < N; i++) {
        int rep = find(dsu, i);
        if (seen.count(rep)) {
            continue;
        }
        seen.insert(rep);

        if (sizes[rep] > 1 && splittable(adj, rep)) {
            output += components + splits;
            output += sizes[rep] * individual - individual;
            
        } else if (sizes[rep] == 1) {
            output += N;

        } else {
            output += components;
            output += sizes[rep] * individual - individual;
        }
    }

    cout << output << endl;

    return 0;
}