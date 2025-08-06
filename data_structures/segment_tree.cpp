
#include <bits/stdc++.h>
using namespace std;

#define ll long long

#include <functional>
#include <vector>

template <typename T>
class SegmentTree {
public:
    vector<T> tree;
    vector<T> arr;
    T neutral;
    function<T(T, T)> merge;
    int n;

    SegmentTree(const vector<T> &array, T neutral, function<T(T, T)> func)
        : arr(array), neutral(neutral), merge(func) {
        n = arr.size();
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(2 * node + 1, start, mid);
            build(2 * node + 2, mid + 1, end);
            tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    void update(int node, int start, int end, int idx, T val) {
        if (start == end) {
            arr[idx] = val;
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(2 * node + 1, start, mid, idx, val);
            } else {
                update(2 * node + 2, mid + 1, end, idx, val);
            }
            tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    T query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return neutral;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        T p1 = query(2 * node + 1, start, mid, l, r);
        T p2 = query(2 * node + 2, mid + 1, end, l, r);
        return merge(p1, p2);
    }

    // User-friendly update and query methods
    void update(int idx, T val) {
        update(0, 0, n - 1, idx, val);
    }

    T query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
};

class SegmentTreeAdd {
public:
    vector<ll> tree;
    vector<ll> arr;
    ll neutral = 0;
    int n;

    SegmentTreeAdd(const vector<ll> &array)
        : arr(array) {
        n = arr.size();
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(2 * node + 1, start, mid);
            build(2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    void update(int node, int start, int end, int idx, ll val) {
        if (start == end) {
            arr[idx] = val;
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(2 * node + 1, start, mid, idx, val);
            } else {
                update(2 * node + 2, mid + 1, end, idx, val);
            }
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    ll query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return neutral;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        ll p1 = query(2 * node + 1, start, mid, l, r);
        ll p2 = query(2 * node + 2, mid + 1, end, l, r);
        return p1 + p2;
    }

    // User-friendly update and query methods
    void update(int idx, ll val) {
        update(0, 0, n - 1, idx, val);
    }

    ll query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
};

// Example usage
int main() {
    vector<int> array = {1, 2, 3, 4, 5};
    SegmentTree<int> st(array, 0, [](int a, int b) { return a + b; });

    cout << "Sum of range [1, 3]: " << st.query(1, 3) << endl;
    st.update(2, 10);
    cout << "Sum of range [1, 3] after update: " << st.query(1, 3) << endl;
    return 0;
}
