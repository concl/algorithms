#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1000000007;

class IntegerMod {
    long long value;
    long long mod;

    public:
        IntegerMod(long long value, long long mod) {
            this->value = value;
            this->mod = mod;
        }

        IntegerMod(long long value) {
            this->value = value;
            this->mod = MOD;
        }

        IntegerMod() {
            this->value = 0;
            this->mod = MOD;
        }

        IntegerMod operator+(IntegerMod &other) {
            return IntegerMod((value + other.value) % mod, mod);
        }

        IntegerMod operator-(IntegerMod &other) {
            return IntegerMod((value - other.value + mod) % mod, mod);
        }

        IntegerMod operator*(IntegerMod &other) {
            return IntegerMod((value * other.value) % mod, mod);
        }

        IntegerMod operator/(IntegerMod &other) {
            return IntegerMod((value * other.inverse().value) % mod, mod);
        }

        IntegerMod operator+=(IntegerMod &other) {
            value = (value + other.value) % mod;
            return *this;
        }

        IntegerMod operator-=(IntegerMod &other) {
            value = (value - other.value + mod) % mod;
            return *this;
        }

        IntegerMod operator*=(IntegerMod &other) {
            value = (value * other.value) % mod;
            return *this;
        }

        IntegerMod operator/=(IntegerMod &other) {
            value = (value * other.inverse().value) % mod;
            return *this;
        }

        IntegerMod inverse() {
            long long a = value, b = mod, x = 0, y = 1, x0 = 1, y0 = 0, q, temp;
            while (b != 0) {
                q = a / b;
                temp = a;
                a = b;
                b = temp % b;
                temp = x;
                x = x0;
                x0 = temp - q * x0;
                temp = y;
                y = y0;
                y0 = temp - q * y0;
            }
            return IntegerMod(x, mod);
        }

};


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    
    
    return 0;
}