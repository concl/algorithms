/**
 * Author: concl
 * Status: Untested
 * Description: Exposes a simple class for prefix sums, which can be used to answer range sum queries in O(1) time after O(n) preprocessing time.
 * Tags: prefix sums, range queries
 */

#include <bits/stdc++.h>

using namespace std;

template <typename T>
class PrefixSum {
public:
    vector<T> prefix_sum;

    PrefixSum(const vector<T> &array) {
        prefix_sum.resize(array.size() + 1);
        for (int i = 0; i < array.size(); i++) {
            prefix_sum[i + 1] = prefix_sum[i] + array[i];
        }
    }

    // returns the sum of the subarray from [start, end)
    T query(int start, int end) {
        return prefix_sum[end] - prefix_sum[start];
    }
};

int main() {

    return 0;
}
