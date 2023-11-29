
// Problem 1842D
// Link: https://codeforces.com/problemset/problem/1842/D
// Author: Luke Zeng

// All friends who have a restriction with 1 decrease y every time they aren't used.
// All friends who have a restriction with n decrease y every time they are used.

// A friend, a, which is connected to a friend, b, connected to 1 has its restriction, y2, decrease every time b is used and a isn't. (If the y1 between 1 and b decreases to 0, then a must be activated, and so on)
// A friend, a, which is connected to a friend, b, connected to n has its restriction, y2, decrease every time b isn't used and a is. (If the y2 between a and b decreases to 0, then b must be activated, and so on)

// Strategy: Play with as little friends as possible, and add friends as restrictions need.
// (Use a priority queue with each element being an ordered tuple with first element being the friend that must be added and the time it needs to be added by
// (this element determines order))

// Each time you pop from the priority queue, the friend is added and all its restrictions start counting down (need to add all edges for the node), if the friend isn't added already
// If a terminal restriction reaches 0, times up (an edge between an arbitrary friend f and n)

// Print out the friends in each step

/* #region cp template */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vll vector<ll>
#define vvi vector<vi>
#define vvl vector<vll>
#define endl "\n"
#define all(x) (x).begin(), (x).end()
#define elif else if
#define hash_table gp_hash_table
#define forn(i,n) for(int i=0;(i)<(n);i++)

using namespace std;
using namespace __gnu_pbds;


struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

template <typename X, typename Y>
using safe_map = unordered_map<X, Y, custom_hash>;

template <typename X>
using safe_set = unordered_set<X, custom_hash>;

template <typename X, typename Y>
using safe_hash_table = hash_table<X, Y, custom_hash>;

template<typename A, typename B> ostream& operator<< (ostream &cout, pair<A,B> const &p) {
    return cout << "(" << p.F << ", " << p.S << ")";
}
template<typename A> ostream& operator<< (ostream &cout, vector<A> const&v) {
    cout << "["; forn(i,(int)v.size()){ if (i) cout << ", "; cout << v[i];} return cout << "]";
}
/* #endregion */

const ll MOD = 1e9+7;
// const ll MOD = 998244353;
const ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> graph(n);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    forn(i, m) {
        int u, v, y;
        cin >> u >> v >> y;

        u--; v--;

        if (v < u) swap(u, v);

        if (u == 0) {
            pq.push(mp(y, v));
        }
        graph[u].pb(mp(v, y));
        graph[v].pb(mp(u, y));
    }

    vector<pair<string,ll>> sets_of_friends;
    string set_of_friends = string(n, '0');
    set_of_friends[0] = '1';
    vector<bool> visited(n, false);
    visited[0] = true;
    bool done = false;
    ll time = 0;

    while (!pq.empty()) {
        auto [y, u] = pq.top();
        pq.pop();
        
        if (visited[u]) continue;

        if (y - time > 0)
            sets_of_friends.pb(mp(set_of_friends, y - time));
        visited[u] = true;
        set_of_friends[u] = '1';

        time = max(time, y);

        if (u == n-1) {
            done = true;
            break;
        }

        for (auto [v, y2] : graph[u]) {
            if (!visited[v]) {
                pq.push(mp(y + y2, v));
            }
        }
    }

    if (!done) {
        cout << "inf" << endl;
        return 0;
    }
    cout << time << " " << sets_of_friends.size() << endl;
    for (auto [set_of_friends, time] : sets_of_friends) {
        cout << set_of_friends << " " << time << endl;
    }
    
    return 0;
}
// python tester.py 1842D input -v testpy.py
