
/*
* Author: concl
* Status: Tested on https://leetcode.com/problems/range-sum-query-mutable/
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

template <typename T>
class SegmentTree {
public:
    vector<T> tree;
    vector<T> arr;
    T identity;
    function<T(T, T)> merge;
    int n;

    SegmentTree(const vector<T> &array, T identity, function<T(T, T)> func)
        : arr(array), identity(identity), merge(func) {
        n = arr.size();
        tree = vector<T>(2 * n, identity);
        build();
    }

    void build() {
        for (int i = 0; i < n; i++) {
            tree[i + n] = arr[i];
            int node = (i + n) / 2;
            while (node > 0) {
                tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
                node /= 2;
            }
        }
    }

    void update(int idx, T val) {
        tree[idx + n] = val;
        int node = (idx + n) / 2;
        while (node > 0) {
            tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
            node /= 2;
        }
    }

    T query(int l, int r) {
        
        T left = identity;
        T right = identity;
        int l_node = l + n;
        int r_node = r + n;

        while (l_node < r_node) {
            if (l_node % 2 == 1) {
                left = merge(left, tree[l_node]); // add to the right since we move right
                l_node += 1;
            }
            if (r_node % 2 == 1) {
                right = merge(tree[r_node - 1], right);  // since right is exclusive we add r_node - 1
                r_node -= 1;
            }
            l_node /= 2; r_node /= 2;
        }
        return merge(left, right);
    }
};


// Example usage
void example() {
    vector<int> array = {1, 2, 3, 4, 5};
    SegmentTree<int> st(array, 0, [](int a, int b) { return a + b; });

    cout << "Sum of range [1, 3]: " << st.query(1, 3) << endl;
    st.update(2, 10);
    cout << "Sum of range [1, 3] after update: " << st.query(1, 3) << endl;
}
