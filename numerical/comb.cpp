
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

const ll MOD = 1e9+7;
const ll N = 1000000;
// const ll MOD = 998244353;

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

ll dp[N] = {1};
ll inv_factorial[N] = {1};
ll biggest = 0;
ll fact(ll n) {
    if (n == 0) return 1;

    for (ll i = biggest+1; i <= n; i++) {
        dp[i] = (dp[i-1] * i) % MOD;
        inv_factorial[i] = modpow(dp[i], MOD-2, MOD);
    }
    biggest = n;
    return dp[n];
}

ll inv_fact(ll n) {
    if (n == 0) return 1;
    return inv_factorial[n];
}


ll comb(ll n, ll k) {
    if (k > n) return 0;
    return (fact(n) * inv_fact(k) % MOD * inv_fact(n - k) % MOD) % MOD;
}

ll permutations(ll n, vector<ll> split) {
    ll start = fact(n);

    for (ll x : split) {
        start *= modpow(fact(x), MOD-2, MOD);
        start %= MOD;
    }
    return start;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << comb(3,1);
    
    return 0;
}