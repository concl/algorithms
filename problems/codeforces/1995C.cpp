// Problem 1995C
// Link: https://codeforces.com/problemset/problem/1995/C

/* #region cp template */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define pb push_back
#define mp make_pair
#define endl "\n"
#define all(x) (x).begin(), (x).end()
#define elif else if
#define hash_table gp_hash_table
#define forn(i,n) for(int i=0;(i)<(n);i++)
#define rep(i,a,b) for(int i=a;(i)<(b);i++)

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vll> vvl;

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

template<typename K, typename V>
ostream& operator<< (ostream &cout, unordered_map<K, V> const &m) {
    cout << "{";
    for (auto it = m.begin(); it != m.end(); ++it) {
        if (it != m.begin()) cout << ", ";
        cout << it->first << ": " << it->second;
    }
    return cout << "}";
}

template<typename K, typename V>
ostream& operator<< (ostream &cout, map<K, V> const &m) {
    cout << "{";
    for (auto it = m.begin(); it != m.end(); ++it) {
        if (it != m.begin()) cout << ", ";
        cout << it->first << ": " << it->second;
    }
    return cout << "}";
}

template<typename A>
ostream& operator<< (ostream &cout, unordered_set<A> const &s) {
    cout << "{";
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (it != s.begin()) cout << ", ";
        cout << *it;
    }
    return cout << "}";
}


template<typename A>
ostream& operator<< (ostream &cout, set<A> const &s) {
    cout << "{";
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (it != s.begin()) cout << ", ";
        cout << *it;
    }
    return cout << "}";
}

/* #endregion */

const ll MOD = 1e9+7;
// const ll MOD = 998244353;
const ll INF = 1e18;




int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vll arr(n);
        forn(i, n) cin >> arr[i];

        ll out = 0;
        ll prev = 0;
        ll squares = 0;

        for (int i = 0; i < n; i++) {
            // 1 squared is 1
            if (arr[i] == 1) {
                if (arr[i] < prev) {
                    out = -1;
                    break;
                } else {
                    prev = arr[i];
                    continue;
                }
            }

            if (arr[i] > prev) {
                if (prev <= 1) {
                    squares = 0;
                } else {

                    int squares_to_equalize = 0; // number of times you must square prev for it to be just less than or equal to arr[i]
                    ll temp = prev;
                    while (temp <= arr[i]) {
                        temp *= temp;
                        squares_to_equalize++;
                    }
                    squares_to_equalize--;

                    int extra = squares - squares_to_equalize;
                    squares = max(0, extra);
                }
            } else {

                int squares_to_equalize = 0; // number of times you must square arr[i] for it to be greater than prev
                ll temp = arr[i];
                while (temp < prev) {
                    temp *= temp;
                    squares_to_equalize++;
                }
                squares = squares + squares_to_equalize;
            }
            prev = arr[i];
            out += squares;
        }

        cout << out << endl;

    }
    return 0;
}
// python tester.py B input -v testpy.py

