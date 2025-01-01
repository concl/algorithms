
#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair

typedef long long ll;
typedef vector<int> vi;

using namespace std;

// returns the path taken in euler path for an undirected graph
vector<int> euler_path(unordered_map<int, unordered_set<int>>& graph) {
    int n = graph.size();
    
    int start_node = 0; // will be set to one of the nodes with odd degree if applicable, otherwise to some node with edges
    int odds = 0;
    for (auto& kv : graph) {
        if (kv.second.size() % 2 == 1) {
            start_node = kv.first;
            odds++;
        }
        if (graph[start_node].empty() && !graph[kv.first].empty()) {
            start_node = kv.first;
        }
    }

    if (odds != 0 && odds != 2) {
        throw "The graph has no euler path";
    }

    unordered_map<int, unordered_set<int>> graph_copy = graph;

    vector<int> stack = {start_node};
    vector<int> path;

    while (!stack.empty()) {
        int node = stack.back();
        if (graph_copy[node].empty()) {
            path.push_back(node);
            stack.pop_back();
        } else {
            int new_node = *graph_copy[node].begin();
            graph_copy[node].erase(new_node);
            graph_copy[new_node].erase(node);
            stack.push_back(new_node);
        }
    }

    reverse(path.begin(),path.end());
    return path;
}

// finds an euler path for a directed graph. currently assumes that there exists a path
vector<int> euler_path_directed(unordered_map<int, unordered_set<int>>& graph) {
    int n = graph.size();

    unordered_map<int,int> deg;
    for (auto kv : graph) {
        deg[kv.first] += kv.second.size();
        for (int x : kv.second) {
            deg[x] -= 1;
        }
    }
    
    int start = deg.begin()->first;
    int end = deg.begin()->first;
    for (auto kv : deg) {
        if (kv.second == 1) {
            start = kv.first;
        } else if (kv.second == -1) {
            end = kv.first;
        }
    }

    unordered_map<int, unordered_set<int>> graph_copy = graph;

    vector<int> stack = {start};
    vector<int> path;

    while (!stack.empty()) {
        int node = stack.back();
        if (graph_copy[node].empty()) {
            path.push_back(node);
            stack.pop_back();
        } else {
            int new_node = *graph_copy[node].begin();
            graph_copy[node].erase(new_node);
            stack.push_back(new_node);
        }
    }

    reverse(path.begin(),path.end());
    return path;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    

    return 0;
}
// python tester.py euler_tour input -v testpy.py
