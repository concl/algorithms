#include <bits/stdc++.h>

#define forn(i,n) for (int i = 0; i < n; i++)

using namespace std;



template<typename A> ostream& operator<< (ostream &cout, vector<A> const&v) {
    cout << "["; forn(i,(int)v.size()){ if (i) cout << ", "; cout << v[i];} return cout << "]";
}



vector<int> kmp(string& s) {

    int n = s.size();

    int fail = 0;
    vector<int> output(n,0);

    for (int i = 1; i < n; i++) {
        while (fail > 0 && s[i] != s[fail]) {
            fail = output[fail - 1];
        }
        if (s[i] == s[fail])
            fail++;
        output[i] = fail;
    }

    return output;
}

int main() {

    string f = "abcabcabcaaabbccc";
    cout << kmp(f);

    return 0;
}
