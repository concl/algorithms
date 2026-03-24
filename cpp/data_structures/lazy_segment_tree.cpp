/*
* Author: concl
* Status: Untested
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Lazy Segment Tree for range sum queries and range updates
class LazySegmentTree {
public:
    vector<ll> tree;
    vector<ll> lazy;
    int n;

    LazySegmentTree(const vector<ll>& arr) {
        n = arr.size();
        tree = vector<ll>(4 * n - 1, 0);
        lazy = vector<ll>(4 * n, 0);
        build(arr); 
    }

    void _insert(int pos, int idx, int tl, int tr, ll val) {
        if (tl == tr - 1) {
            tree[idx] = val;
            return;
        }

        int mid = (tl + tr) / 2;
        if (pos < mid) {
            _insert(pos, idx * 2 + 1, tl, mid, val);
        } else {
            _insert(pos, idx * 2 + 2, mid, tr, val);
        }
        tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    }

    void build(const vector<ll>& arr) {
        for (int i = 0; i < n; i++) 
            _insert(i, 0, 0, n, arr[i]);
    }

    void _range_update(int l, int r, int idx, int tl, int tr, ll val) {
        if (tl >= tr) return;
        if (tl == tr - 1) {
            tree[idx] += val;
            return;
        }
        if (tl == l && tr == r) {
            lazy[idx] += val;
            return;
        }

        int mid = (tl + tr) / 2;
        if (r <= mid) {
            _range_update(l, r, idx * 2 + 1, tl, mid, val);
            return;
        } else if (l >= mid) {
            _range_update(l, r, idx * 2 + 2, mid, tr, val);
            return;
        }
        _range_update(l, mid, idx * 2 + 1, tl, mid, val);
        _range_update(mid, r, idx * 2 + 2, mid, tr, val);
    }

    // Adds val to every element in [l, r)
    void range_update(int l, int r, ll val) { _range_update(l, r, 0, 0, n, val); }

    // [tl, tr) should always be a superset of [l, r)
    ll _query(int l, int r, int idx, int tl, int tr) {
        if (tl >= tr) return 0;
        if (tl == tr - 1) {
            return tree[idx];
        }

        if (tl == l && tr == r) return tree[idx] + lazy[idx] * (tr - tl);

        ll extra = lazy[idx] * (r - l);
        int mid = (tl + tr) / 2;
        if (r <= mid) {
            return extra + _query(l, r, idx * 2 + 1, tl, mid);
        } else if (l >= mid) {
            return extra + _query(l, r, idx * 2 + 2, mid, tr);
        }

        return extra + _query(l, mid, idx * 2 + 1, tl, mid) + _query(mid, r, idx * 2 + 2, mid, tr);
    }

    // Query for the interval [l, r)
    ll query(int l, int r) { return _query(l, r, 0, 0, n); }
};

// Standard io interface
int main() {

    int n; cin >> n;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    LazySegmentTree tree(arr);

    int q; cin >> q;
    for (int _ = 0; _ < q; _++) {

        string query_type; cin >> query_type;
        if (query_type == "range_update") {
            int l, r; ll val;
            cin >> l >> r >> val;
            tree.range_update(l, r, val);
        } else if (query_type == "query") {
            int l, r;
            cin >> l >> r;
            ll res = tree.query(l, r);
            cout << res << endl;
        } else {
            cerr << "Skipping unknown query type" << endl;
        }
    }

    return 0;
}