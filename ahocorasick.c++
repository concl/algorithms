// incomplete

#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vll vector<ll>
#define elif else if
using namespace std;

const int alphabet_size = 26;

int cindex(char c) {
    return c - 'a';
}

// Aho-Corasick Vertex
struct Vertex {
    int edges[alphabet_size], fail;
    bool end = false;
    Vertex() {
        fill(edges, edges + alphabet_size, -1);
        fail = -1;
    }
};

// Aho-Corasick wrapper
class AhoCorasick {
public:
    vector<Vertex> trie;
    AhoCorasick() {
        trie = vector<Vertex>(1);
    }

    void add_string(string s) {
        int index = 0;
        for (auto x : s) {
            if (trie[index].edges[cindex(x)] == -1) {
                trie.push_back(Vertex());
                trie[index].edges[cindex(x)] = trie.size() - 1;
            }
            index = trie[index].edges[cindex(x)];
        }
        trie[index].end = true;
    }

    void construct_automaton(vector<string> strings) {
        for (auto &s : strings) {
            add_string(s);
        }

        queue<int> q;
        for (int &edge : trie[0].edges) {
            if (edge != -1) {
                trie[edge].fail = 0;
                q.push(edge);
            } else {
                edge = 0;
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int i = 0; i < alphabet_size; i++) {
                int &v = trie[u].edges[i];

                if (v == -1) {
                    v = trie[trie[u].fail].edges[i];
                    continue;
                }

                int j = trie[u].fail;
                while (trie[j].edges[i] == -1) j = trie[j].fail;
                trie[v].fail = trie[j].edges[i];
                trie[v].end |= trie[trie[v].fail].end;

                q.push(v);
            }
        }
    }

    bool match(string s) {
        int index = 0;
        for (auto x : s) {
            if (trie[index].edges[cindex(x)] == -1){
                return false;
            } else {
                index = trie[index].edges[cindex(x)];
            }
        }
        return trie[index].end;
    }
    
    // only finds end indices for matches (if multiple matches end at the same index, it will only return one of them)
    vector<int> matches(string s) {
        vector<int> result;
        int u = 0;
        for (int i = 0; i < s.size(); i++) {
            u = trie[u].edges[cindex(s[i])];
            if (trie[u].end) {
                result.push_back(i);
            }
        }
        return result;
    }
};

void tests() {
    // asserts
    AhoCorasick ac;
    vector<string> test = {"he", "she", "his", "hers"};
    ac.construct_automaton(test);
    assert(ac.match("he") == true);
    assert(ac.match("she") == true);

    // tests
    AhoCorasick ac2;
    vector<string> test2 = {"he", "she", "his", "hers"};
    ac2.construct_automaton(test2);
    vector<int> ans = ac2.matches("ushershis");
    for (auto x : ans) {
        cout << x << " ";
    }
}


int main() {
    tests();
    return 0;
}