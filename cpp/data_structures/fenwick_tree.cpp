#include <bits/stdc++.h>

using namespace std;


class FenwickTree {

public:
    vector<int> tree;
    int n;

    FenwickTree(int size, vector<int> &arr) : n(size) {
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