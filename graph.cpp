
#include <bits/stdc++.h>

using namespace std;


bool bfs(vector<vector<int>>& graph, int source, int target) {
    unordered_set<int> seen;
    queue<int> q;
    q.push(source);
    seen.insert(source);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        seen.insert(u);
        if (u == target) {
            return true;
        }
        for (int v : graph[u]) {
            if (seen.find(v) == seen.end()) { // not seen
                q.push(v);
                seen.insert(v); // Mark as seen when adding to the queue
            }
        }
    }
    return false; // No path found
}

bool dfs(vector<vector<int>>& graph, int source, int target) {

    unordered_set<int> seen;
    vector<int> stack;

    stack.push_back(source);
    seen.insert(source);    // Mark as seen when adding to the stack

    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        if (u == target) {
            return true;
        }
        for (int v : graph[u]) {
            if (seen.find(v) == seen.end()) { // not seen
                stack.push_back(v);
                seen.insert(v); // Mark as seen when adding to the stack
            }
        }
    }

    return false;
}

// Constructs an undirected graph, given edges
vector<vector<int>> construct_graph(int n, vector<vector<int>>& edges) {

    vector<vector<int>> graph(n);

    for (const auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
    }

    return graph;
}


int main() {
 
    return 0;
}
