/**
 * Author: concl
 * Status: Untested
 */

#include <bits/stdc++.h>

#define ll long long

using namespace std;

// Returns the floor of the base 2 logarithm of x
long long log2_floor(unsigned long long x) {
    // __builtin_clzll is built in count leading zeros for long long
    return x ? __builtin_clzll(1) - __builtin_clzll(x) : -1;
}

int LCA(vector<vector<int>> &jumps, int root, int node1, int node2) {
    
    // equalize depths
    int depth1 = 0;
    int depth2 = 0;
    
    
    
    // find largest jump such that the node pointed to still differs between the 2
    int n = jumps.size();
    int biggest_jump = log2_floor(n) + 1;
    int curr_jump = 0;
    while (
        curr_jump < biggest_jump 
        && jumps[node1][curr_jump + 1] != jumps[node2][curr_jump + 1]
        && jumps[node1][curr_jump + 1] != -1
        && jumps[node2][curr_jump + 1] != -1
    ) {
        curr_jump += 1;
    }
    
    while (curr_jump > 0 && node1 != node2) {
        if (
            jumps[node1][curr_jump] != jumps[node2][curr_jump]
            && jumps[node1][curr_jump] != -1
            && jumps[node2][curr_jump] != -1
        ) {
            node1 = jumps[node1][curr_jump];
            node2 = jumps[node2][curr_jump];
        } else {
            curr_jump -= 1;
        }
    }
    
    return node1;
}

/**
 * Description: Returns a table where table[i][j] represents the 2^(j - 1)th parent of node i.
 * If this parent doesn't exist, we store a -1.
 */
vector<vector<int>> preprocessing(vector<vector<int>> &graph, int root) {
    int n = graph.size();
    int biggest_jump = log2_floor(n) + 1;

    vector<vector<int>> res(n, vector<int>(biggest_jump + 1, -1));
    for (int i = 0; i < n; i++) res[i][0] = i;

    vector<bool> seen(n, false);
    seen[root] = true;
    
    vector<int> q = {root};

    while (q.size() > 0) {
        vector<int> temp;

        for (int node : q) {
            for (int child : graph[node]) {
                if (!seen[child]) {
                    seen[child] = true;
                    res[child][1] = node;
                    temp.push_back(child);
                }
            }
        }
        q = temp;
    }

    for (int i = 2; i < biggest_jump + 1; i++) {
        for (int node = 0; node < n; node++) {
            // if the i-1-th jump is valid and the node at the jump also has an i-1-th jump, then there is an ith jump
            if (res[node][i - 1] != -1 && res[res[node][i - 1]][i - 1] != -1) {
                res[node][i] = res[res[node][i - 1]][i - 1];
            }
        }
    }

    return res;
}
