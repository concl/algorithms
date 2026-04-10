/**
 * Author: concl
 * Status: Untested
 * Description: Implements a binary indexed tree for
 * range queries with a left endpoint of 0, e.g. [0, k]
 * Tags: fenwick tree, binary indexed tree, range queries, point updates, BIT
 */

#include <bits/stdc++.h>

using namespace std;

class BIT {
public:
    vector<int> tree;
    int n;

    BIT(int size, vector<int> &arr) : n(size) {
        tree.resize(n, 0);
        for (int i = 0; i < n; i++) {
            update(i, arr[i]);
        }
    }

    void update(int idx, int val) {
        for (; idx < n; idx |= idx + 1) {
            tree[idx] += val;
        }
    }

    int query(int idx) {
        int sum = 0;
        for (; idx >= 0; idx = (idx & (idx + 1)) - 1) {
            sum += tree[idx];
        }
        return sum;
    }
};

int main() {

    return 0;
}