/* #region cp template */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds; // includes gp_hash_table

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define elif else if
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

    size_t operator()(const std::string &s) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        // Start with an offset (FNV offset basis + a bit of randomness)
        uint64_t result = 0xcbf29ce484222325ULL ^ FIXED_RANDOM; 
        // A typical FNV-like loop
        for (unsigned char c : s) {
            result ^= c;
            result *= 0x100000001b3ULL; // FNV prime
        }
        return static_cast<size_t>(result);
    }

    template <typename T>
    size_t operator()(const std::vector<T> &v) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        uint64_t result = 0xcbf29ce484222325ULL ^ FIXED_RANDOM; 
        // Combine the hash of each element
        for (auto &elem : v) {
            // Recursively call our custom hash on the element
            // This works for ints, strings, or even nested vectors
            uint64_t h_elem = (*this)(elem);
            result ^= h_elem + 0x9e3779b97f4a7c15ULL + (result << 6) + (result >> 2);
        }
        return static_cast<size_t>(result);
    }
};

template <typename X, typename Y>
using u_map = unordered_map<X, Y, custom_hash>;

template <typename X>
using u_set = unordered_set<X, custom_hash>;

template <typename X, typename Y>
using hash_table = gp_hash_table<X, Y, custom_hash>;

// concatenate vectors
template<typename T>
vector<T> operator+(const vector<T>& a, const vector<T>& b) {
    vector<T> res = a;
    res.insert(res.end(), b.begin(), b.end());
    return res;
}

template<typename T>
vector<T>& operator+=(vector<T>& a, const vector<T>& b) {
    a.insert(a.end(), b.begin(), b.end());
    return a;
}


template<typename A, typename B> ostream& operator<< (ostream &cout, pair<A,B> const &p);
template<typename A> ostream& operator<< (ostream &cout, vector<A> const&v);
template<typename K, typename V> ostream& operator<< (ostream &cout, unordered_map<K, V> const &m);
template<typename K, typename V> ostream& operator<< (ostream &cout, map<K, V> const &m);
template<typename A> ostream& operator<< (ostream &cout, unordered_set<A> const &s);
template<typename A> ostream& operator<< (ostream &cout, multiset<A> const &s);

// print pairs
template<typename A, typename B> ostream& operator<< (ostream &cout, pair<A,B> const &p) {
    return cout << "(" << p.first << ", " << p.second << ")";
}


// print vectors
template<typename A> ostream& operator<< (ostream &cout, vector<A> const&v) {
    cout << "["; for (int i = 0; i < v.size(); i++){ if (i) cout << ", "; cout << v[i];} return cout << "]";
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

template<typename A>
ostream& operator<< (ostream &cout, multiset<A> const &s) {
    cout << "{";
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (it != s.begin()) cout << ", ";
        cout << *it;
    }
    return cout << "}";
}

template<typename... Args>
void print(Args&&... args) {
    ((cout << args << " "), ...) << "\n";
}

/* #endregion */

const ll MOD = 1e9+7;
// const ll MOD = 998244353;
const ll INF = 1e18;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    
    
    return 0;
}
// Things to check:
// * Modulo
// * Overflow (for powers of 2, use 1LL << x instead of 1 << x)
// * Edge cases
// * unordered_map and unordered_set is unsafe
// * Did you skip taking in input by breaking out of a test case early?
// * Do you need to clear state between test cases?
// * 1 based or 0 based indexing?
// * In interactive problems, delete fast io