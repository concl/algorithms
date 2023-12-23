


#include <bits/stdc++.h>

using namespace std;

const int alphabet_size = 26;

int cindex(char c) {
    return c - 'a';
}

struct Vertex {
    int edges[alphabet_size];
    bool end = false;
    int mark;
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

        void add_string(string s, int ind) {

            int index = 0;
            for (auto x : s) {
                if (trie[index].edges[cindex(x)] == -1) {
                    trie.push_back(Vertex());
                    trie[index].edges[cindex(x)] = trie.size() - 1;
                    index = trie.size() - 1;
                } else {
                    index = trie[index].edges[cindex(x)];
                }

            }
            trie[index].end = true;
            trie[index].mark = ind;
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

class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        
        int n = words.size();
        vector<vector<int>> output;

        Trie bud;
        for (int i = 0; i < n; i++) {
            string add = words[i];
            reverse(add.begin(),add.end());
            bud.add_string(add, i);
        }



    }
};
