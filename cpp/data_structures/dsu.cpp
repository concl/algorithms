/**
 * Author: concl
 * Status: Somewhat tested
 */

#include <bits/stdc++.h>

using namespace std;

class DSU {
public:
    vector<int> dsu;
    vector<int> sizes;

    DSU(int n) {
        dsu.resize(n);
        sizes.resize(n, 1);
        for (int i = 0; i < n; i++) {
            dsu[i] = i;
        }
    }

    int find(int node) {
        if (dsu[node] == node) {
            return node;
        } else {
            return dsu[node] = find(dsu[node]);
        }
    }

    void union_sets(int a, int b) {
        int x = find(a);
        int y = find(b);

        if (x == y) {
            return;
        } else if (sizes[x] < sizes[y]) {
            swap(x, y);
        }

        dsu[y] = x;
        sizes[x] += sizes[y];
    }
};

// Functional implementation of disjoint set union (union find) data structure
int find(vector<int> &dsu, int node) {

    if (dsu[node] == node) {
        return node;
    } else {
        return dsu[node] = find(dsu, dsu[node]);
    }
}

void union_sets(vector<int> &dsu, vector<int> &sizes, int a, int b) {

    int x = find(dsu, a);
    int y = find(dsu, b);

    if (x == y) {
        return;
    } else if (sizes[x] < sizes[y]) {
        swap(x, y);
    }

    dsu[y] = x;
    sizes[x] += sizes[y];
}
