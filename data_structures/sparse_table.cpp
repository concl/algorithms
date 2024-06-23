
#include <bits/stdc++.h>

using namespace std;

// Returns the floor of the base 2 logarithm of x
int log2_floor(unsigned long long x) {
    return x ? __builtin_clzll(1) - __builtin_clzll(x) : -1;
}

// minimum element in range [l, r)
class SparseTable {

public:
    vector<vector<int>> st;
    SparseTable(vector<int> &a) {

        int n = a.size();
        int k = log2_floor(n) + 1;
        st = vector<vector<int>>(k, vector<int>(n));

        for (int i = 0; i < n; i++) {
            st[0][i] = a[i];
        }

        for (int j = 1; j < k; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }

    }

    int query(int l, int r) {
        int j = log2_floor(r - l + 1);
        return min(st[j][l], st[j][r - (1 << j) + 1]);
    }

};

int main() {
    return 0;
}

