#include <bits/stdc++.h>

using namespace std;


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

    return 0;
}
