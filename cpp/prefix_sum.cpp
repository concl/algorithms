
#include <bits/stdc++.h>

using namespace std;


// make sure arr isn't empty
vector<int> make_prefix_sum(vector<int>& arr) {
    int n = arr.size();
    vector<int> out(n);
    out[0] = arr[0];

    for (int i = 1; i < n; i++) {
        out[i] = arr[i] + out[i - 1];
    }
    return out;
}

// sum of the elements from l to r inclusive, given a prefix sum
int query(vector<int>& pref_sum, int l, int r) {
    if (l == 0) {
        return pref_sum[r];
    }
    return pref_sum[r] - pref_sum[l];
}


int main() {


    return 0;
}

