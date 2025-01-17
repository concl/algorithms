
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

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll sub(ll a, ll b) {
    ll out = (a - b) % MOD;
    if (out < 0) return out + MOD;
    return out;
}

ll mul(ll a, ll b) {
    return (a * b) % MOD;
}

ll inv(ll x) {
    return modpow(x, MOD - 2);
}

// Combination function: Computes nCr % MOD
ll comb(int n, int r) {
    if (r > n || r < 0) return 0; // Return 0 for invalid inputs
    return mul(mul(factorial[n], inv_factorial[r]), inv_factorial[n - r]);
}

void preprocess() {
    // Step 1: Precompute factorials and modular inverses
    factorial[0] = inv_factorial[0] = 1;
    for (int i = 1; i < N; i++) {
        factorial[i] = factorial[i - 1] * i % MOD;               // Factorial % MOD
        inv_factorial[i] = inv(factorial[i]);        // Modular inverse using Fermat's theorem
    }
}


int main() {

    int N, pos, val;
    cin >> N >> pos >> val;

    preprocess();
    ll out = 0;
    
    // top left
    vector<ll> prefsum(N);
    prefsum[0] = 1;
    for (int i = 1; i < N; i++) {
        prefsum[i] = mul(comb(N - val, i), comb(N - pos, i));
        prefsum[i] = add(prefsum[i], prefsum[i - 1]);
    }

    for (int i = 1; i <= min(val - 1, pos - 1); i++) {
        ll addition = mul(comb(pos - 2, i - 1), comb(val - 2, i - 1));
        int l = N + 1 + i - val - pos;
        int r = N - 1 - i;
        addition = l > 0 ? mul(addition, sub(prefsum[r], prefsum[l - 1])) : mul(addition, prefsum[r]);

        out = add(out, addition);
    }

    // bottom right
    vector<ll> prefsum2(N);
    prefsum2[0] = 1;
    for (int i = 1; i < N; i++) {
        prefsum2[i] = mul(comb(N - val - 1, i), comb(N - pos - 1, i));
        prefsum2[i] = add(prefsum2[i], prefsum2[i - 1]);
    }

    for (int i = 1; i <= min(val, pos); i++) {
        ll addition = mul(comb(pos - 1, i - 1), comb(val - 1, i - 1));
        int l = N - 1 + i - val - pos;
        int r = N - 1 - i;
        addition = l > 0 ? mul(addition, sub(prefsum2[r], prefsum2[l - 1])) : mul(addition, prefsum2[r]);

        out = add(out, addition);
    }

    // both
    for (int i = 1; i <= min(val - 1, pos - 1); i++) {
        ll addition = mul(comb(pos - 2, i - 1), comb(val - 2, i - 1));
        int l = N - 1 + i - val - pos;
        int r = N - 1 - i - 1;
        addition = l > 0 ? mul(addition, sub(prefsum2[r], prefsum2[l - 1])) : mul(addition, prefsum2[r]);

        out = sub(out, addition);
    }
    

    // top right
    prefsum[0] = 1;
    for (int i = 1; i < N; i++) {
        prefsum[i] = mul(comb(N - pos, i), comb(val - 1, i));
        prefsum[i] = add(prefsum[i], prefsum[i - 1]);
    }

    for (int i = 1; i <= min(pos - 1, N - val); i++) {
        ll addition = mul(comb(pos - 2, i - 1), comb(N - val - 1, i - 1));
        int l = i;
        int r = N - 1 - i;
        addition = l > 0 ? mul(addition, sub(prefsum[r], prefsum[l - 1])) : mul(addition, prefsum[r]);

        out = add(out, addition);
    }

    // bottom right
    prefsum2[0] = 1;
    for (int i = 1; i < N; i++) {
        prefsum2[i] = mul(comb(N - pos - 1, i), comb(val - 1, i));
        prefsum2[i] = add(prefsum2[i], prefsum2[i - 1]);
    }

    for (int i = 1; i <= min(pos, N - val + 1); i++) {
        ll addition = mul(comb(pos - 1, i - 1), comb(N - val, i - 1));
        int l = i - 2;
        int r = N - 1 - i;
        addition = l > 0 ? mul(addition, sub(prefsum2[r], prefsum2[l - 1])) : mul(addition, prefsum2[r]);

        out = add(out, addition);
    }

    // both
    for (int i = 1; i <= min(pos - 1, N - val); i++) {
        ll addition = mul(comb(pos - 2, i - 1), comb(N - val - 1, i - 1));
        int l = i - 2;
        int r = N - 1 - i - 1;
        addition = l > 0 ? mul(addition, sub(prefsum2[r], prefsum2[l - 1])) : mul(addition, prefsum2[r]);

        out = sub(out, addition);
    }

    prefsum[0] = N - 1 - pos;
    for (int i = 1; i < N - 1; i++) {
        prefsum[i] = add(prefsum[i - 1], mul(comb(N - 1 - val, i), comb(N - 1 - pos, i + 1)));
    }

    // remaining top bottom blue
    for (int i = 1; i <= min(pos - 2, val - 2); i++) {
        ll addition = mul(comb(pos - 2, i - 1), comb(val - 2, i));
        int l = N + i - val - pos;
        int r = N - 1 - i - 1;
        addition = l > 0 ? mul(addition, sub(prefsum[r], prefsum[l - 1])) : mul(addition, prefsum[r]);
        
        out = add(out, addition);
    }

    prefsum2[0] = N - 1 - val;
        for (int i = 1; i < N; i++) {
        prefsum2[i] = add(prefsum2[i - 1], mul(comb(N - 1 - val, i + 1), comb(N - 1 - pos, i)));
    }
    // remaining left right blue
    for (int i = 1; i <= min(pos - 2, val - 2); i++) {
        ll addition = mul(comb(pos - 2, i), comb(val - 2, i - 1));
        int l = N + i - val - pos;
        int r = N - 1 - i - 1;
        addition = l > 0 ? mul(addition, sub(prefsum2[r], prefsum2[l - 1])) : mul(addition, prefsum2[r]);
        
        out = add(out, addition);
    }

    cout << out << endl;

    return 0;
}
