/**
 * IO harness for Segment Tree (point update, range query).
 *
 * Input format:
 *   n
 *   a[0] a[1] ... a[n-1]
 *   q
 *   <query_type> <args>
 *
 * Query types:
 *   "update idx val"  — point update: set a[idx] = val
 *   "query l r"        — range query on [l, r)
 *
 * Output: one line per query result.
 */

#include "../../cpp/data_structures/segment_tree.cpp"
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    SegmentTree<ll> st(arr, 0LL, [](ll a, ll b) { return a + b; });

    int q;
    cin >> q;
    while (q--) {
        string type;
        cin >> type;
        if (type == "update") {
            int idx; ll val;
            cin >> idx >> val;
            st.update(idx, val);
        } else if (type == "query") {
            int l, r;
            cin >> l >> r;
            cout << st.query(l, r) << "\n";
        }
    }
    return 0;
}
