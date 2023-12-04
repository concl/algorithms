
// Problem: Weird Algorithm (CSES)
// Link: https://cses.fi/problemset/task/1068


#include <bits/stdc++.h>

using namespace std;

#define ll long long

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    
    ll n; cin >> n;
 
    cout << n;
 
    while (n > 1) {
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = 3*n + 1;
        }
        cout << " " << n;
    }
 
    return 0;
}


