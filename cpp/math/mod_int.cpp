/**
 * Author: concl
 * Status: Untested
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

/**
 * Class for modular arithmetic with a prime modulus.
 */
class ModInt {
public:
    ll val;
    static const ll MOD = 1e9 + 7;

    ModInt(ll val) : val(val) {
        this->val = val % MOD;
        if (val < 0) this->val += MOD; // handle negative values
    }

    ModInt inv() const {
        ll m = MOD;
        ll a1, b1;
        ll a2, b2;
        ll x = val;
        a1 = 1;
        b1 = 0;

        a2 = 0;
        b2 = 1;

        while (x != 1) {
            ll factor = m / x;
            ll rem = m % x;

            a2 += MOD - (a1 * factor % MOD);
            b2 += MOD - (b1 * factor % MOD);

            m = rem;
            swap(x, m);
            swap(a1, a2);
            swap(b1, b2);
        }

        return ModInt(a1 % MOD);
    }

    ModInt operator+(const ModInt& other) const {
        return ModInt(val + other.val);
    }

    ModInt operator-(const ModInt& other) const {
        return ModInt(val - other.val);
    }

    ModInt operator*(const ModInt& other) const {
        return ModInt(val * other.val);
    }

    ModInt operator/(const ModInt& other) const {
        return ModInt(val * other.inv().val);
    }

    ModInt& operator+=(const ModInt& other) {
        val += other.val;
        val %= MOD;
        return *this;
    }

    ModInt& operator-=(const ModInt& other) {
        val -= other.val;
        val %= MOD;
        if (val < 0) val += MOD;
        return *this;
    }

    ModInt& operator*=(const ModInt& other) {
        val *= other.val;
        val %= MOD;
        return *this;
    }

    ModInt& operator/=(const ModInt& other) {
        val *= other.inv().val;
        val %= MOD;
        return *this;
    }

    ModInt operator-() const {
        return ModInt(-val);
    }

    bool operator==(const ModInt& other) const {
        return val == other.val;
    }

    bool operator!=(const ModInt& other) const {
        return val != other.val;
    }

    friend ostream& operator<<(ostream& os, const ModInt& mint) {
        os << mint.val;
        return os;
    }

    friend istream& operator>>(istream& is, ModInt& mint) {
        is >> mint.val;
        mint.val %= MOD;
        if (mint.val < 0) mint.val += MOD;
        return is;
    }
};


int main() {    


    return 0;
}