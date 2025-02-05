
// Problem 1416D
// Rating: 2600
// Note that this problem is garbage and has terrible time contraints

#include <bits/stdc++.h>

using namespace std;

// Disjoint Set Union
int find(vector<int>& dsu, int node) {
    if (dsu[node] == node) return node;
    return dsu[node] = find(dsu,dsu[node]);
}

// Only path compression is done
void union_sets_no_new_node(vector<int>& dsu, int a, int b) {
    int x = find(dsu, a);
    int y = find(dsu, b);

    if (x == y) return;
    
    dsu[x] = y;
}

void union_sets(vector<int>& dsu, vector<unordered_set<int>>& adj, int a, int b) {
    int x = find(dsu, a);
    int y = find(dsu, b);

    if (x == y) return;
    
    int new_node = adj.size();
    adj.push_back({x, y});
    adj[x].insert(new_node);
    adj[y].insert(new_node);

    dsu.push_back(new_node);
    dsu[x] = new_node;
    dsu[y] = new_node;
}

vector<int> euler_path(vector<unordered_set<int>>& adj, int start_node) {
    int n = adj.size();

    vector<int> stack = {start_node};
    vector<int> path = {start_node};

    while (!stack.empty()) {
        int node = stack.back();
        if (adj[node].empty()) {
            path.push_back(node);
            stack.pop_back();
        } else {
            int new_node = *adj[node].begin();
            adj[node].erase(new_node);
            adj[new_node].erase(node);
            stack.push_back(new_node);
            path.push_back(new_node);
        }
    }

    return path;
}

struct MaxOp {
    static constexpr int neutral = 0;
    int operator()(int a, int b) const { return max(a, b); }
};

template<typename Op = MaxOp>
class SegmentTree {
    Op op;
    int n;
    int m;
    vector<int> tree;

    int next_power_of_two(int x) {
        if (x == 0) return 1;
        x--;        // Ensure we handle x=1 correctly
        x |= x >> 1;
        x |= x >> 2;
        x |= x >> 4;
        x |= x >> 8;
        x |= x >> 16;
        return x + 1;
    }

public:
    SegmentTree(const vector<int>& arr) : n(arr.size()), op() {
        m = next_power_of_two(n);
        tree.resize(2 * m, Op::neutral);
        // Initialize leaves
        for (int i = 0; i < n; ++i)
            tree[m + i] = arr[i];
        // Build the tree bottom-up
        for (int i = m - 1; i > 0; --i)
            tree[i] = op(tree[2 * i], tree[2 * i + 1]);
    }

    void update(int idx, int val) {
        idx += m; // Move to the leaf node
        tree[idx] = val;
        // Propagate up the tree
        for (idx >>= 1; idx >= 1; idx >>= 1) {
            int new_val = op(tree[2 * idx], tree[2 * idx + 1]);
            if (tree[idx] == new_val) break; // Early exit if no change
            tree[idx] = new_val;
        }
    }

    int query(int l, int r) {
        l += m;
        r += m;
        int res = Op::neutral;
        while (l <= r) {
            if (l % 2 == 1) { // If l is a right child, include it
                res = op(res, tree[l]);
                l++;
            }
            if (r % 2 == 0) { // If r is a left child, include it
                res = op(res, tree[r]);
                r--;
            }
            // Move to the parent level
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    cin >> n >> m >> q;

    // Label each vertex
    vector<int> labels(n);
    for (int i = 0; i < n; i++) {
        cin >> labels[i];
    }
    
    // Map each label to a node
    vector<int> label_to_node(n + 1);
    for (int i = 0; i < n; i++) {
        label_to_node[labels[i]] = i;
    }

    // Disjoint Set Union
    vector<int> dsu(n);
    for (int i = 0; i < n; i++) {
        dsu[i] = i;
    }

    // Using unordered_set to store the adjacency list, since we need to remove edges efficiently
    vector<unordered_set<int>> adj(n);

    // Store the edges
    vector<pair<int,int>> edges(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edges[i] = {a,b};
        adj[a].insert(b);
        adj[b].insert(a);
    }

    // Store the queries, and remove the edges to create an initial DSU state
    vector<pair<int,int>> queries(q);
    for (int i = 0; i < q; i++) {
        int type, x;
        cin >> type >> x;
        x--;
        queries[i] = {type, x};
        if (type == 2) {
            int edge = x;
            int a = edges[edge].first;
            int b = edges[edge].second;

            adj[a].erase(b);
            adj[b].erase(a);
        }
    }


    // Create an initial DSU state
    for (int i = 0; i < n; i++) {
        vector<int> to_remove;
        for (int j : adj[i]) {

            if (j < i) continue; // Avoid double counting
            // If the edge connects two vertices in the same component, remove it, making the component a tree

            if (find(dsu, i) == find(dsu, j)) {
                to_remove.push_back(j);
                continue;
            }

            union_sets_no_new_node(dsu, i, j);
        }
        for (int j : to_remove) {
            adj[i].erase(j);
            adj[j].erase(i);
        }
    }  

    // For queries of the first type, store the representative node of the tree
    // For queries of the second type, store a -1
    vector<int> repr(q, -1);
    for (int i = q - 1; i >= 0; i--) {
        int type = queries[i].first;
        if (type == 1) {

            int node = queries[i].second;
            repr[i] = find(dsu, node);

        } else {

            pair<int,int> edge = edges[queries[i].second];

            int a = edge.first;
            int b = edge.second;

            if (find(dsu, a) == find(dsu, b)) {
                continue;
            } else {
                union_sets(dsu, adj, a, b);
            }
        }
    }

    // Make the graph (which could be a disjoint set of trees) a tree
    bool is_tree = true;
    int previous = find(dsu, 0);

    for (int i = 0; i < n; i++) {
        if (find(dsu, i) != previous) {
            is_tree = false;
            break;
        }
    }

    if (!is_tree) {
        previous = -1;
        adj.push_back({});
        for (int i = 0; i < n; i++) {
            int rep = find(dsu, i);
            if (rep != previous) {
                adj[adj.size() - 1].insert(rep);
                adj[rep].insert(adj.size() - 1);
                previous = rep;
            }
        }
    }

    // Flatten the tree, making it processably by a segment tree
    vector<int> flattened = euler_path(adj, adj.size() - 1);
    vector<int> labels_flattened(flattened.size(),0);
    for (int i = 0; i < flattened.size(); i++) {
        if (flattened[i] >= n) {
            continue;
        }
        labels_flattened[i] = labels[flattened[i]];
    }

    SegmentTree tree(labels_flattened);
    vector<vector<int>> positions(adj.size());
    for (int i = 0; i < flattened.size(); i++) {
        positions[flattened[i]].push_back(i);
    }

    // Process the queries
    for (int i = 0; i < q; i++) {
        if (repr[i] == -1) {
            continue;
        }

        // Find the label of the root of the subtree
        int rep = repr[i];

        // Find the maximum element in the subtree
        int rep_label = tree.query(positions[rep][0], positions[rep][positions[rep].size() - 1]);

        cout << rep_label << endl;

        if (rep_label == 0) {
            continue;
        }

        // Remove the maximum element from the subtree
        for (int idx : positions[label_to_node[rep_label]]) {
            tree.update(idx, 0);
        }
    }

    return 0;
}