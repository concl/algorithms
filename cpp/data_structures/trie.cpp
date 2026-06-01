/**
 * Author: concl
 * Status: Somewhat tested
 */

#include <bits/stdc++.h>

using namespace std;

const int ALPHABET_SIZE = 26;

// Trie vertex
struct Vertex {
    int edges[ALPHABET_SIZE];
    bool end = false;
    Vertex() {
        fill(edges, edges + ALPHABET_SIZE, -1);
    }
};

// Trie wrapper
class Trie {
public:
    vector<Vertex> trie;
    Trie() {
        trie = vector<Vertex>(1);
    }

    int c_index(char c) {
        return c - 'a';
    }

    void add_string(string s) {

        int index = 0;
        for (char c : s) {
            if (trie[index].edges[c_index(c)] == -1) {
                trie.push_back(Vertex());
                trie[index].edges[c_index(c)] = trie.size() - 1;
                index = trie.size() - 1;
            } else {
                index = trie[index].edges[c_index(c)];
            }
        }
        trie[index].end = true;
    }

    bool match(string s) {

        int index = 0;
        for (char c : s) {
            if (trie[index].edges[c_index(c)] == -1){
                return false;
            } else {
                index = trie[index].edges[c_index(c)];
            }
        }
        return trie[index].end;
    }
};
