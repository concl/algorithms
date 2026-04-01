/**
 * 3721. Longest Balanced Subarray II
 * Link: https://leetcode.com/problems/longest-balanced-subarray-ii/
 * Author: concl
 * Tags: Lazy Segment Tree, RMQ
 * Description: Demonstrates usage of lazy segment tree which supports range updates and can find positions of zeros in the array.
 */

#include <bits/stdc++.h>

using namespace std;

// Modified lazy segment tree
class LazySegmentTree {
public:
    vector<int> lower;
    vector<int> upper;
    vector<int> lazy;
    int n;

    LazySegmentTree(const vector<int> &arr) {
        n = arr.size();
        lower = vector<int>(4 * n - 1, INT_MAX);
        upper = vector<int>(4 * n - 1, INT_MIN);
        lazy = vector<int>(4 * n, 0);
        build(arr);
    }

    void _insert(int pos, int idx, int tl, int tr, int val) {
        if (tl == tr - 1) {
            lower[idx] = val;
            upper[idx] = val;
            return;
        }

        int mid = (tl + tr) / 2;
        if (pos < mid) {
            _insert(pos, idx * 2 + 1, tl, mid, val);
        } else {
            _insert(pos, idx * 2 + 2, mid, tr, val);
        }
        lower[idx] = min(lower[2 * idx + 1], lower[2 * idx + 2]);
        upper[idx] = max(upper[2 * idx + 1], upper[2 * idx + 2]);
    }

    void build(const vector<int> &arr) {
        for (int i = 0; i < n; i++)
            _insert(i, 0, 0, n, arr[i]);
    }

    void _range_update(int l, int r, int idx, int tl, int tr, int val) {
        if (tl >= tr)
            return;
        if (tl == tr - 1) {
            lower[idx] += val;
            upper[idx] += val;
            return;
        }
        if (tl == l && tr == r) {
            lazy[idx] += val;
            return;
        }

        int mid = (tl + tr) / 2;
        // split into [tl, mid) and [mid, tr)
        if (r <= mid) {
            _range_update(l, r, idx * 2 + 1, tl, mid, val);
        } else if (l >= mid) {
            _range_update(l, r, idx * 2 + 2, mid, tr, val);
        } else {
            _range_update(l, mid, idx * 2 + 1, tl, mid, val);
            _range_update(mid, r, idx * 2 + 2, mid, tr, val);
        }
        lower[idx] = min(lower[idx * 2 + 1] + lazy[idx * 2 + 1], lower[idx * 2 + 2] + lazy[idx * 2 + 2]);
        upper[idx] = max(upper[idx * 2 + 1] + lazy[idx * 2 + 1], upper[idx * 2 + 2] + lazy[idx * 2 + 2]);
    }

    // Adds val to every element in [l, r)
    void range_update(int l, int r, int val) { _range_update(l, r, 0, 0, n, val); }

    // [tl, tr) should always be a superset of [l, r)
    int _query(int l, int r, int idx, int tl, int tr, int shift) {

        assert (tl < tr);
        if (tl == tr - 1) {
            if (lower[idx] + shift <= 0 && 0 <= upper[idx] + shift) {
                return tl;
            } else {
                return tr;
            }
        }

        int extra = lazy[idx] + shift;
        if (tl == l && tr == r) {
            if (0 < lower[idx] + extra || 0 > upper[idx] + extra) {
                return tr;
            }
        }
        
        int mid = (tl + tr) / 2;
        if (r <= mid) {
            return _query(l, r, idx * 2 + 1, tl, mid, extra);
        } else if (l >= mid) {
            return _query(l, r, idx * 2 + 2, mid, tr, extra);
        }

        int value1 = _query(l, mid, idx * 2 + 1, tl, mid, extra);
        if (value1 == mid) {
            int value2 = _query(mid, r, idx * 2 + 2, mid, tr, extra);
            return value2;
        } else {
            return value1;
        }
    }

    int query(int l, int r) { return _query(l, r, 0, 0, n, 0); }

    int _find_value(int pos, int idx, int tl, int tr, bool is_lower) {
        if (tl == tr - 1) {
            return is_lower ? lower[idx] : upper[idx];
        }

        int mid = (tl + tr) / 2;
        if (pos < mid) {
            return _find_value(pos, idx * 2 + 1, tl, mid, is_lower);
        } else {
            return _find_value(pos, idx * 2 + 2, mid, tr, is_lower);
        }
    }

    // Useful debugging method which prints out the internal array state
    // void print_state() {
    //     print("Lower: ");
    //     vector<int> low;
    //     for (int i = 0; i < n; i++) {
    //         low.push_back(_find_value(i, 0, 0, n, true));
    //     }
    //     print(low);
    //     print(" ");
    // }
};


class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        
        int res = 0;
        int n = nums.size();

        LazySegmentTree state(vector<int>(n, 0));
        unordered_map<int,int> last_seen;

        for (int i = 0; i < n; i++) {
            int l;
            if (last_seen.count(nums[i])) {
                l = last_seen[nums[i]] + 1;
            } else {
                l = 0;
            }
            last_seen[nums[i]] = i;

            if (nums[i] & 1) {
                state.range_update(l, i + 1, 1);
            } else {
                state.range_update(l, i + 1, -1);
            }

            int best = state.query(0, i + 1);
            res = max(res, i - best + 1);
        }
        return res;
    }
};