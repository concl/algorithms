

#include <bits/stdc++.h>
#define ll long long
#define uint unsigned int
#define elif else if
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
ll pow(ll a, ll b, ll m) {

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
    
    cout << pow(2,8) << endl;
    cout << pow(3,5) << endl;
    cout << pow((int) 5,2, 123483) << endl;

    return 0;
}
