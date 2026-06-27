/**
 * IO harness for Binary Jumping (LCA via binary lifting).
 *
 * Input format:
 *   n root
 *   u1 v1
 *   u2 v2
 *   ...
 *   u_{n-1} v_{n-1}    (n-1 undirected edges of the tree)
 *   q                   (number of LCA queries)
 *   a1 b1
 *   ...
 *   a_q b_q
 *
 * Output: one line per LCA query — the LCA node index.
 */

#include "../../cpp/graphs/binary_jumping.cpp"
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, root;
    cin >> n >> root;

    vector<vector<int>> graph(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    auto jumps = preprocessing(graph, root);

    int q;
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << LCA(jumps, root, a, b) << "\n";
    }
    return 0;
}
