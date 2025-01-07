
#include <bits/stdc++.h>

using namespace std;


// calculates the length of the longest prefix that a substring starting at each position matches with.
vector<int> z_function(string s) {
    int n = s.size();
    vector<int> output(n,0);
    
    int p1 = 1;
    int p2 = 1;
    // i is the index of the thing we are solving for
    for (int i = 1; i < n; i++) {
        if (i >= p2) {
            p1 = i;
            p2 = i;
        }

        int check = i - p1; // position in output to check
        if (i + output[check] < p2) {
            output[i] = output[check];
            continue;
        }
        p1 = i;

        while (p2 < n && s[p2] == s[p2 - i]) {
            p2++;
        }
        output[i] = p2 - i;
    }
    return output;
}


int main() {

    vector<int> test = z_function("aaaaabbbaabcdefabcdefaaaaabbb");
    for (int x : test) {
        cout << x << ' ';
    } cout << endl;

    return 0;
}

