#include <bits/stdc++.h>
#define ll long long
#define uint unsigned int
#define elif else if
using namespace std;

int cindex(char c) {
    return c - 'a';
}


// Trie vertex
struct Vertex {
    int edges[26];
    bool end = false;
    Vertex() {
        fill(edges, edges + 26, -1);
    }
};

// Trie wrapper
class Trie {
    public:
        vector<Vertex> trie;
        Trie() {
            trie = vector<Vertex>(1);
        }

        void add_string(string s) {

            int index = 0;
            for (auto x : s) {
                if (trie[index].edges[x - 'a'] == -1) {
                    trie.push_back(Vertex());
                    trie[index].edges[x - 'a'] = trie.size() - 1;
                    index = trie.size() - 1;
                } else {
                    index = trie[index].edges[x - 'a'];
                }
                trie[index].end = true;
            }
        }

        bool match(string s) {

            int index = 0;
            for (auto x : s) {
                if (trie[index].edges[x - 'a'] == -1){
                    return false;
                } else {
                    index = trie[index].edges[x - 'a'];
                }
            }
            return trie[index].end;

        }
};


int main() {
    
    
    return 0;
}