
#include <bits/stdc++.h>

using namespace std;

vector<int> topological_sort(vector<vector<int>> &graph) {
    int n = graph.size();
    
    vector<int> output;

    unordered_set<int> roots;
    for (int x = 0; x < n; x++) {
        roots.insert(x);
    }

    for (int i = 0; i < n; i++) {
        for (int j : graph[i]) {
            if (roots.find(j) != roots.end()) {
                roots.erase(j);
            }
        }
    }
    
    unordered_map<int,int> node_level;
    vector<unordered_set<int>> levels = {roots};
    vector<int> bread;



}

int main() {


    return 0;
}
