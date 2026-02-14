
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

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

ll inv(ll x, ll m) {
    // euclidean algorithm solves:
    // ax + bm = 1
    // if we take this mod m, we get:
    // ax = 1 mod m
    // this means a is the modular inverse of x
    ll modulus = m;
    ll a1, b1;
    ll a2, b2;
    a1 = 1;
    b1 = 0;

    a2 = 0;
    b2 = 1;

    while (x != 1) {
        ll factor = m / x;
        ll rem = m % x;

        a2 += modulus - (a1 * factor % modulus);
        b2 += modulus - (b1 * factor % modulus);

        m = rem;
        swap(x, m);
        swap(a1, a2);
        swap(b1, b2);
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


class Mint {
public:
    ll val;
    static const ll MOD = 1e9 + 7;

    Mint(ll val) : val(val) {
        val = val % MOD;
        if (val < 0) val += MOD; // handle negative values
    }

    Mint inv() const {
        return modpow(val, MOD - 2, MOD);
    }

    Mint operator+(const Mint& other) const {
        return Mint(val + other.val);
    }

    Mint operator-(const Mint& other) const {
        return Mint(val - other.val);
    }

    Mint operator*(const Mint& other) const {
        return Mint(val * other.val);
    }

    Mint operator/(const Mint& other) const {
        return Mint(val * other.inv().val);
    }

    Mint& operator+=(const Mint& other) {
        val += other.val;
        val %= MOD;
        return *this;
    }

    Mint& operator-=(const Mint& other) {
        val -= other.val;
        val %= MOD;
        return *this;
    }

    Mint& operator*=(const Mint& other) {
        val *= other.val;
        val %= MOD;
        return *this;
    }

    Mint& operator/=(const Mint& other) {
        val *= other.inv().val;
        val %= MOD;
        return *this;
    }

    Mint operator-() const {
        return Mint(-val);
    }

    bool operator==(const Mint& other) const {
        return val == other.val;
    }

    bool operator!=(const Mint& other) const {
        return val != other.val;
    }

    friend ostream& operator<<(ostream& os, const Mint& mint) {
        os << mint.val;
        return os;
    }

    friend istream& operator>>(istream& is, Mint& mint) {
        is >> mint.val;
        return is;
    }
};

int main() {

    cout << inv(2, 5) << endl;
    cout << modpow(2, 5 - 2, 5) << endl;


    for (int m : {3, 5, 7, 11, 13}) {
        for (int x = 2; x < m; x++) {
            int first = inv(2, m);
            int second = modpow(2, m - 2, m);
            cout << inv(2, m) << endl;
            cout << modpow(2, m - 2, m) << endl;

            if (first == second) cout << "same" << endl;
            else cout << "diff" << endl;
        }
    }

}


