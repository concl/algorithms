
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;

ll add(ll a, ll b) { return (a + b) % MOD; }
ll sub(ll a, ll b) { return (((a - b) % MOD) + MOD) % MOD; }
ll mul(ll a, ll b) { return (a * b) % MOD; }


void compute_dist_and_paths(
    vector<unordered_map<ll, ll>> &graph,
    vector<ll> &dist_from_S,
    vector<ll> &dist_from_T,
    vector<ll> &paths_from_S,
    vector<ll> &paths_from_T,
    int S,
    int T) {

    int n = graph.size();
    
    // Lambda function to perform Dijkstra's algorithm with path counting.
    auto dijkstra = [&](int source, vector<ll>& dist, vector<ll>& paths) {

        dist[source] = 0;
        paths[source] = 1;

        // Min-heap: pair<distance, node>
        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
        pq.emplace(0, source);

        while (!pq.empty()) {
            auto [current_dist, u] = pq.top();
            pq.pop();

            // Skip if we've already found a better way to u.
            if (current_dist > dist[u]) continue;

            // Relaxation step for each neighbor.
            for (auto& [v, weight] : graph[u]) {
                ll new_dist = current_dist + weight;
                if (new_dist < dist[v]) {
                    // Found a strictly shorter path to v.
                    dist[v] = new_dist;
                    paths[v] = paths[u];
                    pq.emplace(new_dist, v);
                } else if (new_dist == dist[v]) {
                    // Found an alternative shortest path to v.
                    paths[v] = add(paths[v], paths[u]);
                }
            }
        }

    };

    // Compute distances and paths from S.
    dijkstra(S, dist_from_S, paths_from_S);
    // Compute distances and paths from T.
    dijkstra(T, dist_from_T, paths_from_T);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Take in input
    int N, M;
    cin >> N >> M;

    int S, T;
    cin >> S >> T;
    S--; T--;

    // Create a weighted graph
    vector<unordered_map<ll, ll>> graph(N);

    for (int i = 0; i < M; i++) {
        ll u, v, d;
        cin >> u >> v >> d;
        u--; v--;
        graph[u][v] = d;
        graph[v][u] = d;
    }

    // Distance from S and from T
    vector<ll> dist_from_S(N, LLONG_MAX);
    vector<ll> dist_from_T(N, LLONG_MAX);

    // Number of shortest paths from S and from T
    vector<ll> paths_from_S(N, 0);
    vector<ll> paths_from_T(N, 0);

    // Compute distances and paths from S and from T
    compute_dist_and_paths(graph, dist_from_S, dist_from_T, paths_from_S, paths_from_T, S, T);

    ll total_dist = dist_from_S[T];
    ll total_paths = paths_from_S[T];
    ll res = mul(total_paths, total_paths);

    assert(total_dist == dist_from_T[S]);
    assert(total_paths == paths_from_T[S]);

    for (int i = 0; i < N; i++) {
        if (dist_from_S[i] + dist_from_T[i] != total_dist) continue;
        
        if (dist_from_S[i] * 2 == total_dist) {
            int meet = mul(paths_from_S[i], paths_from_T[i]);
            res = sub(res, mul(meet, meet));
            continue;
        }

        for (auto& [v, weight] : graph[i]) {
            if (dist_from_S[i] + dist_from_T[v] + weight != total_dist) continue;

            if (2 * dist_from_S[i] < total_dist && 2 * dist_from_T[v] < total_dist) {
                ll meet = mul(paths_from_S[i], paths_from_T[v]);
                res = sub(res, mul(meet, meet));
            }
        }

    }
    
    cout << res << endl;
}

