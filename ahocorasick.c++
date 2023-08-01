// incomplete (also dont trust ai)

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
    int edges[alphabet_size];
    bool end = false;
    Vertex() {
        fill(edges, edges + alphabet_size, -1);
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
                    index = trie.size() - 1;
                } else {
                    index = trie[index].edges[cindex(x)];
                }
                trie[index].end = true;
            }
        }

        void construct_automaton(vector<string> strings) {
            
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

        vector<int> matches(string s) {

            return {};
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
    vector<int> ans = ac2.matches("ushers");
    for (auto x : ans) {
        cout << x << " ";
    }
}


int main() {
    
    return 0;
}