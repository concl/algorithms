// Problem 2049E
// Link: https://codeforces.com/problemset/problem/2049/E

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
#define u_map unordered_map
#define u_set unordered_set

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

// print pairs
template<typename A, typename B> ostream& operator<< (ostream &cout, pair<A,B> const &p) {
    return cout << "(" << p.F << ", " << p.S << ")";
}

// print vectors
template<typename A> ostream& operator<< (ostream &cout, vector<A> const&v) {
    cout << "["; forn(i,(int)v.size()){ if (i) cout << ", "; cout << v[i];} return cout << "]";
}

// print maps
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

// print sets
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

// there is no one here
void solve_small(int lo, int hi) {

    int start = lo;
    int mid = (hi + lo) / 2;

    while (hi > lo) {

        cout << "? " << start << " " << mid << endl;
        cout.flush();
        int test; cin >> test;

        if (test == 1) {
            hi = mid;
        } else if (test == 0) {
            lo = mid + 1;
        }
        mid = (hi + lo) / 2;
    }
    cout << "! " << mid - start + 1 << endl;
}

void solve_big(int lo, int hi, int end) {
    int mid = (hi + lo) / 2 + (hi + lo) % 2;
    while (hi > lo) {

        cout << "? " << mid << " " << end << endl;
        cout.flush();
        int test; cin >> test;

        if (test == 1) {
            hi = mid - 1;
        } else if (test == 0) {
            lo = mid;
        }
        mid = (hi + lo) / 2 + (hi + lo) % 2;
    }

    cout << "! " << end - mid + 1 << endl;
}

void solve_big2(int lo, int hi) {
    int start = 1;
    int mid = (hi + lo) / 2;
    while (hi > lo) {

        cout << "? " << start << " " << mid << endl;
        cout.flush();
        int test; cin >> test;

        if (test == 1) {
            lo = mid + 1;
        } else if (test == 0) {
            hi = mid;
        }
        mid = (hi + lo) / 2;
    }

    cout << "! " << mid << endl;
}

int main() {
    
    int t; cin >> t;
    while(t--) {

        int n; cin >> n;
        
        int size = n / 4;

        int start1 = 1;
        int end1 = 1 + size - 1;

        int start2 = end1 + 1;
        int end2 = end1 + size;

        cout << "? " << start1 << " " << end1 << endl;
        cout.flush();
        int test1; cin >> test1;

        cout << "? " << start2 << " " << end2 << endl;
        cout.flush();
        int test2; cin >> test2;

        if (test1 == test2) {

            cout << "? " << start1 << " " << end2 << endl;
            cout.flush();
            int test3; cin >> test3;

            if (test3 == 1) {
                solve_small(start1, end2);
            } else {
                solve_big(start1, end2 + 1, n);
            }
        } else {

            cout << "? " << end2 + 1 << " " << n << endl;
            cout.flush();
            int test3; cin >> test3;

            if (test3 == 1) {
                solve_small(end2 + 1, n);
            } else {
                solve_big2(end2 + 1, n);
            }

        }
        
    }
    
    
    return 0;
}
// Things to check:
// * Modulo
// * Overflow (for powers of 2, use 1LL << x instead of 1 << x)
// * Edge cases
// * Did you skip taking in input by breaking out of a test case early?
// * Do you need to clear state between test cases?
// * 1 based or 0 based indexing?
// * In interactive problems, delete fast io
// python tester.py E input -v testpy.py
// python3 tester.py E input -v testpy.py