/**
 * Author: concl
 * Status: Tested on CSES
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = LLONG_MAX;

/**
 * Description: Uses Dijkstra's algorithm to find the distance of the shortest path between
 * a given node and all other nodes in a graph. For nodes that are unreachable, the distance
 * is set to be -1
 * 
 * graph[i] stores all neighbors to node i, graph[i][j] is the weight of the edge between
 * node i and j.
 *
 * Note that graph uses a map, replace this with a vector of pairs, or hash map for speed.
 */
vector<ll> shortest_distances(vector<map<int, ll>> &graph, int start) {

    int n = graph.size();

    priority_queue<
        pair<ll, int>,
        vector<pair<ll, int>>,
        greater<pair<ll, int>>>
        pq;

    pq.push({0, start});

    vector<ll> distances(n, -1);

    while (pq.size() > 0) {

        auto [dist, node] = pq.top();
        pq.pop();

        if (distances[node] != -1)
            continue;
        distances[node] = dist;

        for (const auto &[nbr, weight] : graph[node]) {
            if (distances[nbr] == -1) {
                pq.push({dist + weight, nbr});
            }
        }
    }

    return distances;
}

/**
 * Description: Finds the length of the shortest path between start and target.
 */
ll distance(vector<map<int, ll>> &graph, int start, int target) {

    int n = graph.size();
    
    unordered_set<int> seen;
    priority_queue<
        pair<ll, int>,
        vector<pair<ll, int>>,
        greater<pair<ll, int>>>
        pq;

    pq.push({0, start});

    while (pq.size() > 0) {
        
        auto [dist, node] = pq.top();
        pq.pop();

        if (seen.find(node) != seen.end()) {
            continue;
        } else if (node == target) {
            return dist;
        }
        seen.insert(node);

        for (const auto &[nbr, weight] : graph[node]) {
            if (seen.find(nbr) == seen.end()) {
                pq.push({dist + weight, nbr});
            }
        }
    }

    return -1;
}

/**
 * Description: Returns a matrix[i][j] that stores the shortest path from any node i
 * to any node j, using the Floyd-Warshall algorithm.
 */
vector<vector<ll>> all_pairs_shortest_distances(vector<map<int, ll>> &graph) {
    
    int n = graph.size();
    
    vector<vector<ll>> res(n, vector<ll>(n, INF));
    
    for (int i = 0; i < n; i++) {
        res[i][i] = 0;
        for (const auto& [nbr, weight] : graph[i]) {
            res[i][nbr] = weight;
        }
    }
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (res[i][k] != INF && res[k][j] != INF) {
                    res[i][j] = min(res[i][j], res[i][k] + res[k][j]);
                }
            }
        }
    }
    
    return res;
}