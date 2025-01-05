

#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

int pow(int a, int b) {

    int output = 1;
    while (b > 0) {
        if (b & 1) {
            output *= a;
        }

        a *= a;
        b >>= 1;
    }
    return output;

}

// this isnt safe if m is close to the max 64 bit int and a ** b is larger than 2**63 - 1
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
    // tests work
    cout << pow(2,8) << endl;
    cout << pow(3,5) << endl;
    cout << modpow((int) 5,2, 123483) << endl;

    // test with lists
    vector<int> v = {1,2,3,4,5};
    for (int i = 0; i < pow(2,5); i++) {
        for (int j = 0; j < 5; j++) {
            if (i & (1 << j)) {
                cout << v[j] << " ";
            }
        }
        cout << endl;
    }
    // asserts
    assert(pow(2,8) == 256);
    assert(pow(3,5) == 243);
    assert(modpow((int) 5,2, 123483) == 25);
    

    return 0;
}
