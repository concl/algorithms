
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Constants
const ll MOD = 1e9 + 7;    // Prime modulus for modular arithmetic
const int N = 5000001;     // Maximum size for precomputed arrays

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

// Functions for modular arithmetic
ll add(ll a, ll b) { return (a + b) % MOD; }

ll sub(ll a, ll b) {
    ll out = (a - b) % MOD;
    if (out < 0) return out + MOD;
    return out;
}

ll mul(ll a, ll b) { return (a * b) % MOD; }

ll inv(ll x) { return modpow(x, MOD - 2); }

// Combination function: Computes nCr % MOD
ll comb(int n, int r) {
    if (r > n || r < 0) return 0;    // Return 0 for invalid inputs
    return mul(mul(factorial[n], inv_factorial[r]), inv_factorial[n - r]);
}

void preprocess() {
    // Step 1: Precompute factorials and modular inverses
    factorial[0] = inv_factorial[0] = 1;
    for (int i = 1; i < N; i++) {
        factorial[i] = factorial[i - 1] * i % MOD;    // Factorial % MOD
        inv_factorial[i] = inv(factorial[i]);    // Modular inverse using Fermat's theorem
    }
}

int main() {
    int N, pos, val;
    cin >> N >> pos >> val;

    // Edge Case: Grid has no intersections
    if (N == 1) {
        cout << 1 << endl;
        return 0;
    }

    // Precompute factorials
    preprocess();

    ll out = 0;
    
    // Top left
    vector<ll> prefsum(N);
    prefsum[0] = 1;
    for (int i = 1; i < N; i++) {

        // Selecting i extra points from the bottom right quadrant
        prefsum[i] = mul(comb(N - val, i), comb(N - pos, i));
        prefsum[i] = add(prefsum[i], prefsum[i - 1]);
    }

    for (int i = 1; i <= min(val - 1, pos - 1); i++) {

        // Selecting i - 1 points from the top left quadrant
        ll addition = mul(comb(pos - 2, i - 1), comb(val - 2, i - 1));
        int l = N + 1 + i - val - pos;
        int r = min({N - 1 - i, N - pos, N - val});
        if (l > r) {
            continue;
        }

        // Selecting extra points
        addition = l > 0 ? mul(addition, sub(prefsum[r], prefsum[l - 1])) : mul(addition, prefsum[r]);
        out = add(out, addition);
    }

    // Bottom right
    prefsum[0] = 1;
    for (int i = 1; i < N; i++) {

        // Selecting i extra points from the top left quadrant
        prefsum[i] = mul(comb(val - 1, i), comb(pos - 1, i));
        prefsum[i] = add(prefsum[i], prefsum[i - 1]);
    }

    for (int i = 1; i <= min(N - val, N - pos); i++) {

        // Selecting i - i points from the bottom right quadrant
        ll addition = mul(comb(N - 1 - val, i - 1), comb(N - 1 - pos, i - 1));
        int l = val + pos - N + i - 1;
        int r = min({N - 1 - i, pos - 1, val - 1});
        if (l > r) {
            continue;
        }

        // Selecting extra points
        addition = l > 0 ? mul(addition, sub(prefsum[r], prefsum[l - 1])) : mul(addition, prefsum[r]);
        out = add(out, addition);
    }

    // Inclusion-exclusion principle
    if (val < N && pos < N) {
        for (int i = 1; i <= min(val - 1, pos - 1); i++) {

            // Selecting i - 1 points from the top left quadrant
            ll addition = mul(comb(pos - 2, i - 1), comb(val - 2, i - 1));

            // Multiplying by the counts of selecting points from the bottom left and top right quadrants
            addition = mul(addition, mul(comb(N - 1 - pos, val - 1 - i), comb(N - 1 - val, pos - 1 - i)));

            // Exclude
            out = sub(out, addition);
        }
    }

    // Top right
    prefsum[0] = 1;
    for (int i = 1; i < N; i++) {

        // Selecting i extra points from the bottom left quadrant
        prefsum[i] = mul(comb(N - pos, i), comb(val - 1, i));
        prefsum[i] = add(prefsum[i], prefsum[i - 1]);
    }

    for (int i = 1; i <= min(pos - 1, N - val); i++) {

        // Selecting i - 1 points from the top right quadrant
        ll addition = mul(comb(pos - 2, i - 1), comb(N - 1 - val, i - 1));
        int l = val - pos + i;
        int r = min({N - 1 - i, N - pos, val - 1});
        if (l > r) {
            continue;
        }

        // Selecting extra points
        addition = l > 0 ? mul(addition, sub(prefsum[r], prefsum[l - 1])) : mul(addition, prefsum[r]);
        out = add(out, addition);
    }

    // Bottom left
    prefsum[0] = 1;
    for (int i = 1; i < N; i++) {

        // Selecting i extra points from the top right quadrant
        prefsum[i] = mul(comb(N - val, i), comb(pos - 1, i));
        prefsum[i] = add(prefsum[i], prefsum[i - 1]);
    }

    for (int i = 1; i <= min(val - 1, N - pos); i++) {

        // Selecting i - 1 points from the bottom left quadrant
        ll addition = mul(comb(val - 2, i - 1), comb(N - 1 - pos, i - 1));
        int l = pos - val + i;
        int r = min({N - 1 - i, N - val, pos - 1});
        if (l > r) {
            continue;
        }

        // Selecting extra points
        addition = l > 0 ? mul(addition, sub(prefsum[r], prefsum[l - 1])) : mul(addition, prefsum[r]);
        out = add(out, addition);
    }

    // Inclusion-exclusion principle
    if (val - 1 > 0 && N - pos > 0) {
        for (int i = 1; i <= min(pos - 1, N - val); i++) {

            // Selecting i - 1 points from the top right quadrant
            ll addition = mul(comb(pos - 2, i - 1), comb(N - 1 - val, i - 1));

            // Multiplying by the counts of selecting points from the top left and bottom right quadrants
            addition = mul(addition, mul(comb(val - 2, pos - 1 - i), comb(N - 1 - pos, N - val - i)));

            // Exclude
            out = sub(out, addition);
        }
    }

    // Selecting the top and bottom grid lines only
    for (int i = 1; i <= min(pos - 1, val - 2); i++) {
        ll addition = mul(comb(pos - 2, i - 1), comb(val - 2, i));
        addition = mul(addition, mul(comb(N - 1 - pos, val - i - 1), comb(N - 1 - val, pos - i - 2)));

        out = add(out, addition);
    }

    // Selecting the left and right grid lines only
    for (int i = 1; i <= min(pos - 2, val - 1); i++) {
        ll addition = mul(comb(pos - 2, i), comb(val - 2, i - 1));
        addition = mul(addition, mul(comb(N - 1 - val, pos - i - 1), comb(N - 1 - pos, val - i - 2)));

        out = add(out, addition);
    }

    cout << out << endl;

    return 0;
}
