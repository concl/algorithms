
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
    
    vector<pair<int,int>> stack;
    for (int root : roots) {
        stack.push_back({root, 0});
    }
    
    unordered_set<int> visited;
    for (int root : roots) {
        visited.insert(root);
    }

    while (!stack.empty()) {
        if (stack.back().second == graph[stack.back().first].size()) {
            output.push_back(stack.back().first);
            stack.pop_back();
        } else {
            stack.back().second++;
            if (visited.find(graph[stack.back().first][stack.back().second - 1]) != visited.end()) {
                continue;
            }
            visited.insert(graph[stack.back().first][stack.back().second - 1]);
            stack.push_back({graph[stack.back().first][stack.back().second - 1], 0});
        }
    }
    
    reverse(output.begin(), output.end());
    return output;
}

int main(int argc, char **argv) {


    return 0;
}
