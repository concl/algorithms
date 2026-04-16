/**
 * Author: concl
 * Status: Untested
 */

#include <bits/stdc++.h>

using namespace std;

// Aho-Corasick wrapper
class AhoCorasick {
private:
    static const int ALPHABET_SIZE = 26;
    struct Vertex {
        int edges[ALPHABET_SIZE], fail;
        bool end = false;
        Vertex() {
            fill(edges, edges + ALPHABET_SIZE, -1);
            fail = -1;
        }
    };

public:
    vector<Vertex> trie;
    AhoCorasick() {
        trie = vector<Vertex>(1);
    }
    int c_index(char c) {
        return c - 'a';
    }

    void add_string(string s) {
        int index = 0;
        for (auto x : s) {
            if (trie[index].edges[c_index(x)] == -1) {
                trie.push_back(Vertex());
                trie[index].edges[c_index(x)] = trie.size() - 1;
            }
            index = trie[index].edges[c_index(x)];
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

            for (int i = 0; i < ALPHABET_SIZE; i++) {
                int &v = trie[u].edges[i];

                if (v == -1) {
                    v = trie[trie[u].fail].edges[i];
                    continue;
                }

                int j = trie[u].fail;
                while (trie[j].edges[i] == -1)
                    j = trie[j].fail;
                trie[v].fail = trie[j].edges[i];
                trie[v].end |= trie[trie[v].fail].end;

                q.push(v);
            }
        }
    }

    bool match(string s) {
        int index = 0;
        for (auto x : s) {
            if (trie[index].edges[c_index(x)] == -1) {
                return false;
            } else {
                index = trie[index].edges[c_index(x)];
            }
        }
        return trie[index].end;
    }

    // only finds end indices for matches (if multiple matches end at the same index, it will only return one of them)
    vector<int> matches(string s) {
        vector<int> result;
        int u = 0;
        for (int i = 0; i < s.size(); i++) {
            u = trie[u].edges[c_index(s[i])];
            if (trie[u].end) {
                result.push_back(i);
            }
        }
        return result;
    }
};
