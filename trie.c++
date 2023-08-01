#include <bits/stdc++.h>
#define ll long long
#define uint unsigned int
#define elif else if
using namespace std;

const int alphabet_size = 26;

int cindex(char c) {
    return c - 'a';
}

// Trie vertex
struct Vertex {
    int edges[alphabet_size];
    bool end = false;
    Vertex() {
        fill(edges, edges + alphabet_size, -1);
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
};


int main() {
    
    
    return 0;
}