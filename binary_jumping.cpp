#include <bits/stdc++.h>

#define ll long long

using namespace std;

// Returns the floor of the base 2 logarithm of x
long long log2_floor(unsigned long long x) {
    // __builtin_clzll is built in count leading zeros for long long
    return x ? __builtin_clzll(1) - __builtin_clzll(x) : -1; 
}


int LCA(vector<vector<int>>& jumps, int root, int node1, int node2) {
    // TODO

    

}

vector<vector<int>> preprocessing(vector<vector<int>>& graph, int root) {
    int n = graph.size();
    int biggest_jump = log2_floor(n) + 1;

    vector<vector<int>> res(n, vector<int>(biggest_jump, -1));

    unordered_set<int> seen = {root};
    vector<int> q = {root};

    while (q.size() > 0) {
        vector<int> temp;

        for (int node : q) {
            for (int child : graph[node]) {
                if (!seen.count(child)) {
                    seen.insert(child);
                    res[child][0] = node;
                    temp.push_back(child);
                }
            }
        }
        q = temp;
    }

    for (int i = 1; i < biggest_jump; i++) {
        for (int node = 0; node < n; node++) {
            // if the i-1-th jump is valid and the node at the jump also has an i-1-th jump, then there is an ith jump
            if (res[node][i - 1] != -1 && res[ res[node][i - 1] ][i - 1] != -1) {
                res[node][i] = res[ res[node][i - 1] ][i - 1];
            }
        }
    }

    return res;
} 


int main() {

    return 0;
}
