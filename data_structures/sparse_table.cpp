
#include <bits/stdc++.h>

using namespace std;

// Returns the floor of the base 2 logarithm of x
int log2_floor(unsigned long long x) {
    return x ? __builtin_clzll(1) - __builtin_clzll(x) : -1;
}

// min or max element in range [l, r]
class SparseTable {

public:
    vector<vector<int>> table;
    function<int(int, int)> f; // min or max
    SparseTable(vector<int> &a, function<int(int, int)> f) {
        this->f = f;

        int n = a.size();
        int k = log2_floor(n) + 1;
        table = vector<vector<int>>(n, vector<int>(k));

        for (int i = 0; i < n; i++) {
            table[i][0] = a[i];
        }

        for (int j = 1; j < k; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                table[i][j] = f(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r) {
        int j = log2_floor(r - l + 1);
        return f(table[l][j], table[r - (1 << j) + 1][j]);
    }

};

int main() {


    return 0;


}

