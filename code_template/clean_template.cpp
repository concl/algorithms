
#pragma region clean_template
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define forn(i,n) for(int i=0; (i)<(n); i++)
#define all(x) begin(x), end(x)
#define len(x) (int) x.size()

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

template<typename A, typename B> ostream& operator<< (ostream &cout, pair<A,B> const &p);
template<typename A> ostream& operator<< (ostream &cout, vector<A> const&v);
template<typename K, typename V> ostream& operator<< (ostream &cout, unordered_map<K, V> const &m);

// print pairs
template<typename A, typename B> ostream& operator<< (ostream &cout, pair<A,B> const &p) {
    return cout << "(" << p.first << ", " << p.second << ")";
}

// print vectors
template<typename A> ostream& operator<< (ostream &cout, vector<A> const&v) {
    cout << "["; rep (i, 0, v.size()){ if (i) cout << ", "; cout << v[i];} return cout << "]";
}

// print maps
template<typename K, typename V>
ostream& operator<< (ostream &cout, unordered_map<K, V> const &m) {
    cout << "{";
    for (auto it = m.begin(); it != m.end(); ++it) {
        if (it != m.begin()) cout << ", "; // can add a newline for clarity
        cout << it->first << ": " << it->second; 
    }
    return cout << "}";
}

// easier print
template<typename... Args>
void print(Args&&... args) {
    ((cout << args << " "), ...) << endl;
}

#pragma endregion

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    

    return 0;
}