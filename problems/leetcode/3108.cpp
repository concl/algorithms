
// 3108. Minimum Cost Walk in Weighted Graph
// Link: https://leetcode.com/problems/minimum-cost-walk-in-weighted-graph/
// Union Find problem

#include <bits/stdc++.h>

using namespace std;

int find(vector<int>& uf, int a) {
    if (a == uf[a]) return a;
    return uf[a] = find(uf, uf[a]);
}

void union_sets(vector<int>& uf, vector<long long>& sizes, vector<int>& rep, int a, int b, int weight) {

    // ap and bp are the parents of a and b
    int ap = find(uf, a);
    int bp = find(uf, b);

    // edge case where a and b are already in the same component
    if (ap == bp) {
        rep[ap] &= weight;
        return;
    }
    if (sizes[ap] < sizes[bp]) {
        swap(ap, bp);
    }

    uf[bp] = ap;
    sizes[ap] += sizes[bp];

    if ((rep[ap] != -1) && (rep[bp] != -1)) {
        // if both a and b have more than 1 node then the bitwise and will be the bitwise and of all the edges in both components, and the edge connecting them
        rep[ap] &= rep[bp];
        rep[ap] &= weight;
    } else if ((rep[ap] == -1) && (rep[bp] == -1)) {
        // if both a and b have only 1 node then the bitwise and will only be the edge weight connecting them
        rep[ap] = weight;
    } else {
        // b is a single node, so we update the bitwise and of the connected component including a with the edge weight
        rep[ap] &= weight;
    }
}

class Solution {
public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        
        // stores the bitwise and of all the edges in a connected component.
        // -1 means there is only 1 node.
        vector<int> rep(n,-1);

        // standard union find
        vector<long long> sizes(n,1);
        vector<int> uf(n);
        for (int i = 0; i < n; i++) {
            uf[i] = i;
        }

        for (auto x : edges) {
            // modified union sets
            union_sets(uf, sizes, rep, x[0], x[1], x[2]);
        }

        // for each query, check if the nodes are in the same connected component.
        // if they are, then return the bitwise and of all the edges in the connected component.
        vector<int> out;
        for (auto x : query) {
            if (x[0] == x[1]) {
                out.push_back(0);
            } else if (find(uf, x[0]) == find(uf, x[1])) {
                out.push_back(rep[find(uf, x[0])]);
            } else {
                out.push_back(-1);
            }
        }
        return out;
    }
};