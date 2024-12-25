#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Constants
const ll MOD = 998244353;  // Prime modulus for modular arithmetic
const int N = 500001;      // Maximum size for precomputed arrays

// Precomputed arrays for factorials and modular inverses
ll factorial[N], inv_factorial[N]; 

// Function for fast modular exponentiation
ll powmod(ll a, ll b) {
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

int main() {
    int n, k;  // Input values
    cin >> n >> k;

    // Step 1: Precompute factorials and modular inverses
    factorial[0] = inv_factorial[0] = 1;
    for (int i = 1; i <= k; i++) {
        factorial[i] = factorial[i - 1] * i % MOD;               // Factorial % MOD
        inv_factorial[i] = powmod(factorial[i], MOD - 2);        // Modular inverse using Fermat's theorem
    }

    // Step 2: Compute the result by iterating over possible values of R
    int result = 0;
    for (ll r = n; r <= k; r++) {
        ll b = k - r;
        if (r < b) continue;  // Skip values of R that are less than B
        else if (r == b) result = (result + comb(r + b - 1, r) - comb(r + b - 1, b - 1 - (r - n + 1))) % MOD;
        else result = (result + comb(r + b, r) - comb(r + b, b - (r - n + 1))) % MOD;
    }

    cout << result << endl;

    return 0;
}