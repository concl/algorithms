
#include <bits/stdc++.h>

using namespace std;

int find(vector<int>& dsu, int node) {

    if (dsu[node] == node) {
        return node;
    } else {
        return dsu[node] = find(dsu,dsu[node]);
    }
}

void union_sets(vector<int>& dsu, vector<int>& sizes, int a, int b) {

    int x = find(dsu, a);
    int y = find(dsu, b);

    if (x == y) {
        return;
    } else if (sizes[x] < sizes[y]) {
        swap(x,y);
    }

    dsu[y] = x;
    sizes[x] += sizes[y];
}


int main() {    
    
    int n = 10000;
    vector<int> dsu(n);
    vector<int> sizes(n, 1);
    for (int i = 0; i < n; i++) {
        dsu[i] = i;
    }


    return 0;
}
