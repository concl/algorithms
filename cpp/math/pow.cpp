/**
 * Author: concl
 * Status: Somewhat tested
 * Tags: exponentiation, modular exponentiation, binary exponentiation
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int pow(int a, int b) {

    int output = 1;
    while (b > 0) {
        if (b & 1) {
            output *= a;
        }

        a *= a;
        b >>= 1;
    }
    return output;

}

// possible overflow issues
ll mod_pow(ll a, ll b, ll m) {
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
