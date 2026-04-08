/**
 * Author: concl
 * Status: Tested on CSES
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

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
