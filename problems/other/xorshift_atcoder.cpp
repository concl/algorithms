
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int SIZE = 4001;
const ll MOD = 998244353;

// Class for comparisons of large numbers
class BigNum {
public:
    bitset<SIZE> num;
    BigNum(bitset<SIZE> num) : num(num) {

    }

    bool operator > (BigNum other) {
        for (int i = SIZE - 1; i >= 0; i--) {
            if (num[i] > other.num[i]) {
                return true;
            } else if (num[i] < other.num[i]) {
                return false;
            }
        }
        return false;
    }

    bool operator < (BigNum other) {
        for (int i = SIZE - 1; i >= 0; i--) {
            if (num[i] < other.num[i]) {
                return true;
            } else if (num[i] > other.num[i]) {
                return false;
            }
        }
        return false;
    }

    bool operator == (BigNum other) {
        return num == other.num;
    }

    BigNum operator << (int shift) {
        bitset<SIZE> new_num = num << shift;
        return BigNum(new_num);
    }

    BigNum operator >> (int shift) {
        bitset<SIZE> new_num = num >> shift;
        return BigNum(new_num);
    }

    BigNum operator ^ (BigNum other) {
        bitset<SIZE> new_num = num ^ other.num;
        return BigNum(new_num);
    }

    int highest_bit() {
        for (int i = SIZE - 1; i >= 0; i--) {
            if (num[i] == 1) {
                return i;
            }
        }
        return -1;
    }
};

BigNum gcd(BigNum a, BigNum b) {
    
    while (!(a == b)) {
        if (a > b) {
            a = a ^ (b << (a.highest_bit() - b.highest_bit()));
        } else {
            b = b ^ (a << (b.highest_bit() - a.highest_bit()));
        }

        if (a == BigNum(bitset<SIZE>(0))) {
            return b;
        } else if (b == BigNum(bitset<SIZE>(0))) {
            return a;
        }
    }
    return a;
}

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

int main() {

    int N; cin >> N;

    string input; cin >> input;
    int bit_size = input.size();
    BigNum X = BigNum(bitset<SIZE>(input));

    vector<BigNum> nums;
    for (int i = 0; i < N; i++) {
        string input; cin >> input;
        nums.push_back(BigNum(bitset<SIZE>(input)));
    }
    
    // Find the gcd of all the numbers
    BigNum divisor = gcd(nums[0],nums[1]);
    for (int i = 2; i < N; i++) {
        divisor = gcd(divisor,nums[i]);
    }

    int highest_bit = divisor.highest_bit();

    // If X can be constructed exactly, or if a number with a big prefix that is less than X can be constructed
    BigNum current(0);
    ll output = 0;

    for (int i = bit_size - 1; i >= highest_bit; i--) {
        if (X.num[i] == 1) {
            if (current.num[i] != 1) {
                current = current ^ (divisor << (i - highest_bit));
            }
            output += modpow(2, i - highest_bit, MOD);
            output %= MOD;
        } else {
            if (current.num[i] == 1) {
                current = current ^ (divisor << (i - highest_bit));
            }
        }
    }
    

    if (current < X || current == X) {
        output++;
        output %= MOD;
    }


    cout << output << endl;

    return 0;
}
