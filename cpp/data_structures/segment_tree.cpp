/**
 * Author: concl
 * Description: Segment tree with a generic type supporting arbitrary associative
 * operations. Queries are done on a half open interval [l, r).
 * Status: Tested on https://leetcode.com/problems/range-sum-query-mutable/
 */

#include "../bit_tricks.hpp"
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template <typename T>
class SegmentTree {
public:
    vector<T> tree;
    T identity;
    function<T(T, T)> merge;
    int n;

    SegmentTree(const vector<T> &arr, T identity, function<T(T, T)> func)
        : identity(identity), merge(func) {
        n = arr.size();
        tree = vector<T>(2 * n, identity);
        build(arr);
    }

    void build(const vector<T> &arr) {
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
                right = merge(tree[r_node - 1], right); // since right is exclusive we add r_node - 1
                r_node -= 1;
            }
            l_node /= 2;
            r_node /= 2;
        }
        return merge(left, right);
    }
};

// display segment tree
template <typename T>
ostream& operator<<(ostream &os, const SegmentTree<T> &tr) {
    if (tr.n == 0) {
        os << "(empty segment tree)";
        return os;
    }

    struct block {
        vector<string> lines;
        int width;
        int height;
        int root_center;
    };

    auto label = [&](int idx) {
        ostringstream oss;
        oss << "[" << idx << "] " << tr.tree[idx];
        return oss.str();
    };

    function<block(int)> build = [&](int idx) -> block {
        int left = idx * 2;
        int right = left + 1;
        bool has_left = left <= 2 * tr.n - 1;
        bool has_right = right <= 2 * tr.n - 1;

        if (!has_left && !has_right) {
            string s = label(idx);
            int w = (int)s.size();
            return { {s}, w, 1, w / 2 };
        }

        block left_block = build(left);
        block right_block = build(right);

        string s = label(idx);
        int u = (int)s.size();
        int n = left_block.width;
        int m = right_block.width;
        int x = left_block.root_center;
        int y = right_block.root_center;

        string first_line = string(x + 1, ' ') +
                            string(n - x - 1, '_') + s +
                            string(y, '_') +
                            string(m - y, ' ');
        string second_line = string(x, ' ') + "/" +
                             string(n - x - 1 + u + y, ' ') + "\\" +
                             string(m - y - 1, ' ');

        while ((int)left_block.lines.size() < (int)right_block.lines.size()) {
            left_block.lines.push_back(string(n, ' '));
        }
        while ((int)right_block.lines.size() < (int)left_block.lines.size()) {
            right_block.lines.push_back(string(m, ' '));
        }

        vector<string> lines;
        lines.push_back(first_line);
        lines.push_back(second_line);
        for (int i = 0; i < (int)left_block.lines.size(); ++i) {
            lines.push_back(left_block.lines[i] + string(u, ' ') + right_block.lines[i]);
        }

        return { lines, n + m + u, (int)lines.size(), n + u / 2 };
    };

    block root = build(1);
    for (const string &line : root.lines) {
        string trimmed = line;
        while (!trimmed.empty() && trimmed.back() == ' ') {
            trimmed.pop_back();
        }
        os << trimmed << "\n";
    }

    return os;
}


// Example usage
void example() {
    vector<int> array = {1, 2, 3, 4, 5};
    SegmentTree<int> st(array, 0, [](int a, int b) { return a + b; });

    cout << "Sum of range [1, 3): " << st.query(1, 3) << endl;
    st.update(2, 10);
    cout << "Sum of range [1, 3) after update: " << st.query(1, 3) << endl;
    
    cout << st;
}
