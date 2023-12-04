
// 2954. Count the Number of Infection Sequences
// Link: https://leetcode.com/problems/count-the-number-of-infection-sequences/
// Combinatorics problem. Between two initially infected children with positions i and j, there are a number, n = j - i - 1, of uninfected kids.
// Only considering these uninfected kids, there are 2^(n - 1) ways to infect them.
// (At each step, you can either choose to infect the child on the left, or the child on the right. For the last child however, it doesn't matter which side we choose)
// For uninfected kids that aren't between 2 initially infected kids, there is only one way to infect them.
// Use permutations to combine these sequences.

#include <bits/stdc++.h>

using namespace std;

#define ll long long

const ll MOD = 1e9+7;
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

ll permutations(ll n, vector<ll> split) {
    ll start = fact(n);

    for (ll x : split) {
        start *= modpow(fact(x), MOD-2, MOD);
        start %= MOD;
    }
    return start;
}


class Solution {
public:
    int numberOfSequence(int n, vector<int>& sick) {
        
        vector<ll> runs;
        int start = 0;
        if (sick[0] == 0) {
            runs.push_back(0);
        }
        for (int i = 0; i < sick.size(); i++) {
            if (sick[i] - start >= 1) {
                runs.push_back(sick[i] - start);
            }
            start = sick[i] + 1;
        }
        runs.push_back(n - start);

        ll uninfected = n - sick.size();
        ll output = permutations(uninfected, runs);
        for (int i = 1; i < runs.size() - 1; i++) {
            output *= modpow(2, runs[i] - 1, MOD);
            output %= MOD;
        }
        return (int) output;
    }
};