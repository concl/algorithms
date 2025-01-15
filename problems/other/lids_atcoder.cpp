
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Constants
const ll MOD = 1e9 + 7;  // Prime modulus for modular arithmetic
const int N = 5000001;      // Maximum size for precomputed arrays

// Precomputed arrays for factorials
ll factorial[N], inv_factorial[N];


// Function for fast modular exponentiation
ll modpow(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// Combination function: Computes nCr % MOD
ll comb(int n, int r) {
    if (r > n || r < 0) return 0; // Return 0 for invalid inputs
    return factorial[n] * inv_factorial[r] % MOD * inv_factorial[n - r] % MOD;
}

void preprocess() {
    // Step 1: Precompute factorials and modular inverses
    factorial[0] = inv_factorial[0] = 1;
    for (int i = 1; i < N; i++) {
        factorial[i] = factorial[i - 1] * i % MOD;               // Factorial % MOD
        inv_factorial[i] = modpow(factorial[i], MOD - 2);        // Modular inverse using Fermat's theorem
    }
}


int main() {

    int N, pos, val;
    cin >> N >> pos >> val;

    preprocess();

    ll out = 0;
    cout << out << endl;




    return 0;
}
