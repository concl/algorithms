/**
 * Author: concl
 * Status: Untested
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll modpow(ll a, ll b, ll m) {

    ll output = 1;
    while (b > 0) {
        if (b & 1) {
            output *= a;
            output %= m;
        }

        a *= a;
        a %= m;
        b >>= 1;
    }
    return output;

}

ll inv(ll x, ll m) {
    // euclidean algorithm solves:
    // ax + bm = 1
    // if we take this mod m, we get:
    // ax = 1 mod m
    // this means a is the modular inverse of x
    ll modulus = m;
    ll a1, b1;
    ll a2, b2;
    a1 = 1;
    b1 = 0;

    a2 = 0;
    b2 = 1;

    while (x != 1) {
        ll factor = m / x;
        ll rem = m % x;

        a2 += modulus - (a1 * factor % modulus);
        b2 += modulus - (b1 * factor % modulus);

        m = rem;
        swap(x, m);
        swap(a1, a2);
        swap(b1, b2);
    }

    return a1 % modulus;
}

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


int main() {

    cout << inv(2, 5) << endl;
    cout << modpow(2, 5 - 2, 5) << endl;


    for (int m : {3, 5, 7, 11, 13}) {
        for (int x = 2; x < m; x++) {
            int first = inv(2, m);
            int second = modpow(2, m - 2, m);
            cout << inv(2, m) << endl;
            cout << modpow(2, m - 2, m) << endl;

            if (first == second) cout << "same" << endl;
            else cout << "diff" << endl;
        }
    }
}


