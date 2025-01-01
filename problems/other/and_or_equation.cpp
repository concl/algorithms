#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
static const ll P = 998244353;

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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, K;
    cin >> N >> K;

    K %= P;
    
    ll out = K + 1;
    out %= P;
    
    ll factor = K + 1;
    ll factor_den = 1;

    ll term = 1;
    ll den = 1;

    for (ll i = 1; i <= N; i++) {

        term *= N - i + 1;
        term *= 2;
        term %= P;

        den *= pow(i, P-2, P);
        den %= P;

        factor_den *= pow(i + 1, P-2, P);
        factor_den %= P;

        factor *= K - i + 1;
        factor %= P;

        out += (term * den) % P * factor % P * factor_den % P;
        out %= P;

    }

    cout << out << endl;
    
    return 0;
}
