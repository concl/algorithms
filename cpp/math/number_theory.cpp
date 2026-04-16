/**
 * Author: concl
 * Status: Untested
 * Tags: modular arithmetic, modular inverse, modular exponentiation, gcd, lcm
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

/**
 * Description: Finds the modular inverse of x with respect to m.
 * 
 * The Euclidean algorithm solves the equation:
 * ax + bm = 1
 * If we take this mod m, we get:
 * ax = 1 mod m
 * This means that a is the modular inverse of x
 * 
 * Since b is not used in the final result, the implementation does not
 * include it.
 */
ll inv(ll x, ll m) {

    ll modulus = m;
    ll a1 = 1;
    ll a2 = 0;
    a1 = 1;
    a2 = 0;

    while (x != 1) {
        ll factor = m / x;
        ll rem = m % x;

        a2 += modulus - (a1 * factor % modulus);

        m = rem;
        swap(x, m);
        swap(a1, a2);
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
