/**
 * IO harness for Lazy Segment Tree (range add, range sum).
 *
 * Input format:
 *   n
 *   a[0] a[1] ... a[n-1]
 *   q
 *   <query_type> <args>
 *
 * Query types:
 *   "range_update l r val"  — add val to every element in [l, r)
 *   "query l r"              — sum of elements in [l, r)
 *
 * Output: one line per query result.
 */

#include "../../cpp/data_structures/lazy_segment_tree.cpp"
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    LazySegmentTree tree(arr);

    int q;
    cin >> q;
    while (q--) {
        string type;
        cin >> type;
        if (type == "range_update") {
            int l, r; long long val;
            cin >> l >> r >> val;
            tree.range_update(l, r, val);
        } else if (type == "query") {
            int l, r;
            cin >> l >> r;
            cout << tree.query(l, r) << "\n";
        }
    }
    return 0;
}
