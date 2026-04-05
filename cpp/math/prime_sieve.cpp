
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

// returns a vector, v, of integers, where v[i] is the smallest prime factor of i
vector<int> sieve_of_eratosthenes(int n) {

    vector<int> output(n + 1);
    for (int i = 0; i <= n; i++) {
        output[i] = i;
    }

    for (int x = 2; x * x <= n; x++) {
        if (output[x] == x) {
            for (int y = x * x; y <= n; y += x) {
                if (output[y] == y)
                    output[y] = x;
            }
        }
    }

    return output;
}

// Returns a vector of primes up to n
vector<int> primes(int n) {
    vector<bool> prime(n + 1, true);
    prime[0] = prime[1] = 0;
    for (int i = 2; i * i <= n; i++) {
        if (prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                prime[j] = 0;
            }
        }
    }
    vector<int> out;
    for (int i = 2; i <= n; i++) {
        if (prime[i]) {
            out.push_back(i);
        }
    }
    return out;
}
