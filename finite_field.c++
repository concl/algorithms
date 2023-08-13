#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1000000007;

class CyclicGroup {

    long long value;
    long long mod;

    public:
        // Default constructor
        CyclicGroup() : value(0), mod(1000000007) {}

        // Constructor with value and mod
        CyclicGroup(long long value, long long mod = 1000000007) : value(value % mod), mod(mod) {}

        // Overloaded addition operator
        CyclicGroup operator+(const CyclicGroup& other) const {
            return CyclicGroup((value + other.value) % mod, mod);
        }

        // Overloaded subtraction operator
        CyclicGroup operator-(const CyclicGroup& other) const {
            return CyclicGroup((value - other.value + mod) % mod, mod);
        }

        // Overloaded multiplication operator
        CyclicGroup operator*(const CyclicGroup& other) const {
            return CyclicGroup((value * other.value) % mod, mod);
        }

        // Overloaded division operator
        CyclicGroup operator/(const CyclicGroup& other) const {
            long long inv = 1, base = other.value;
            long long exponent = mod - 2;
            while (exponent > 0) {
                if (exponent & 1) inv = (inv * base) % mod;
                base = (base * base) % mod;
                exponent >>= 1;
            }
            return CyclicGroup((value * inv) % mod, mod);
        }

        // Overloaded compound assignment operators
        CyclicGroup& operator+=(const CyclicGroup& other) {
            value = (value + other.value) % mod;
            return *this;
        }

        CyclicGroup& operator-=(const CyclicGroup& other) {
            value = (value - other.value + mod) % mod;
            return *this;
        }

        CyclicGroup& operator*=(const CyclicGroup& other) {
            value = (value * other.value) % mod;
            return *this;
        }

        CyclicGroup& operator/=(const CyclicGroup& other) {
            *this = *this / other;
            return *this;
        }

        // Overloaded stream insertion operator for printing
        friend std::ostream& operator<<(std::ostream& os, const CyclicGroup& group) {
            os << group.value;
            return os;
        }
};

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    
    
    return 0;
}