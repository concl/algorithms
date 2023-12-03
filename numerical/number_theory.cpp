
#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) {

    while (b % a != 0) {
        b %= a;
        swap(a,b);
    }
    return a;
}

int lcm(int a, int b) {
    return a * (b / gcd(a,b));
}

// returns a vector, v, of integers, where v[i] is the smallest prime factor of i
vector<int> sieve_of_eratosthenes(int n) {

    vector<int> output(n + 1);
    for (int i = 0; i <= n; i++) {
        output[i] = i;
    }

    for (int x = 2; x * x <= n; x++) {
        if (output[x] == x) {
            for (int y = x * x; y <= n; y += x) {
                if (output[y] == y)
                    output[y] = x;
            }
        }
    }

    return output;

}

// pretty print vectors
#define forn(i,n) for(int i=0;(i)<(n);i++)
template<typename A> ostream& operator<< (ostream &cout, vector<A> const&v) {
    cout << "["; forn(i,(int)v.size()){ if (i) cout << ", "; cout << v[i];} return cout << "]";
}

int main() {

    printf("%d\n",gcd(21,14));
    printf("%d\n",gcd(23,105));
    printf("%d\n",gcd(105,25));

    cout << sieve_of_eratosthenes(100);

    return 0;

}

