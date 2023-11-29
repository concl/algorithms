
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const ll MOD = 1e9+7;
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

ll dp[100000] = {1};
ll biggest = 0;
ll fact(ll n) {
    if (n == 0) return 1;

    for (ll i = biggest+1; i <= n; i++) {
        dp[i] = (dp[i-1] * i) % MOD;
    }
    biggest = n;
    return dp[n];
}


ll comb(ll n, ll k) {
    if (k > n) return 0;
    return (fact(n) * modpow(fact(k), MOD-2, MOD) % MOD * modpow(fact(n-k), MOD-2, MOD) % MOD) % MOD;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << comb(3,1);
    
    return 0;
}