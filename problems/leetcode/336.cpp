
// 336. Palindrome Pairs [hard]
// Link: https://leetcode.com/problems/palindrome-pairs/

#include <bits/stdc++.h>

using namespace std;

// single numeric only
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

// for tuples
namespace {
    template <class T>
    inline void hash_combine(std::size_t &seed, T const &v) {
        custom_hash hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
    struct HashValueImpl {
        static void apply(size_t &seed, Tuple const &tuple) {
            HashValueImpl<Tuple, Index - 1>::apply(seed, tuple);
            hash_combine(seed, std::get<Index>(tuple));
        }
    };

    template <class Tuple>
    struct HashValueImpl<Tuple, 0> {
        static void apply(size_t &seed, Tuple const &tuple) {
            hash_combine(seed, std::get<0>(tuple));
        }
    };
} // namespace

// combine hash values of all elements in tuple if all elements are numeric
struct tuple_hash {
    template <typename... TT>
    size_t operator()(std::tuple<TT...> const &tt) const {
        size_t seed = 0;
        HashValueImpl<std::tuple<TT...>>::apply(seed, tt);
        return seed;
    }
};

const int alphabet_size = 26;

int cindex(char c) { return c - 'a'; }

struct Vertex {
    int edges[alphabet_size];
    bool end = false;
    int mark;
    Vertex() { fill(edges, edges + alphabet_size, -1); }
};

class Trie {
public:
    vector<Vertex> trie;
    Trie() { trie = vector<Vertex>(1); }

    void add_string(string s, int ind) {

        int index = 0;
        for (char c : s) {
            if (trie[index].edges[cindex(c)] == -1) {
                trie.push_back(Vertex());
                trie[index].edges[cindex(c)] = trie.size() - 1;
                index = trie.size() - 1;
            } else {
                index = trie[index].edges[cindex(c)];
            }
        }
        trie[index].end = true;
        trie[index].mark = ind;
    }
};

vector<int> kmp(string &s) {

    int n = s.size();

    int fail = 0;
    vector<int> output(n, 0);

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

void solve(vector<vector<int>> &output, Trie &bud, string &w, int i,
           bool reversed, unordered_set<tuple<int, int>, tuple_hash> &seen) {
    int m = w.size();
    string checker = w.substr(m / 2 + m % 2, m);
    reverse(checker.begin(), checker.end());
    vector<int> pf = kmp(checker);

    // iterate through the current word, w.
    // if at position i, the substring w[:i + 1] is in the trie, and w[i + 1:]
    // is a palindrome, add the indices to output iterate through the length of
    // the current word. keep an index for the kmp failure function. the length
    // of the rest of the string that has to be checked for if it's a palindrome
    // is m - i - 1 if the index for the kmp failure function is >= (m - i - 1)
    // / 2 (integer division) then the rest of the string is a palindrome

    int trie_node = 0;
    int kmp_pos = 0;
    int kmp_ind = 0;
    int k = 0;

    for (; k < m / 2; k++) {
        while (kmp_pos > 0 && w[k] != checker[kmp_pos]) {
            kmp_pos = pf[kmp_pos - 1];
        }
        if (w[k] == checker[kmp_pos]) {
            kmp_pos++;
        }
    }

    if (bud.trie[trie_node].end && kmp_pos >= m / 2) {
        if (seen.find(make_tuple(bud.trie[trie_node].mark, i)) == seen.end()) {
            output.push_back({bud.trie[trie_node].mark, i});
            seen.insert(make_tuple(bud.trie[trie_node].mark, i));
        }
        if (seen.find(make_tuple(i, bud.trie[trie_node].mark)) == seen.end()) {
            output.push_back({i, bud.trie[trie_node].mark});
            seen.insert(make_tuple(i, bud.trie[trie_node].mark));
        }
    }

    for (int j = 0; j < m; j++) {
        while (kmp_pos > 0 && kmp_pos > (m - j - 1) / 2) {
            kmp_pos = pf[kmp_pos - 1];
        }
        if (k < (m - j - 1) / 2 + j + 1) {
            while (kmp_pos > 0 &&
                   (kmp_pos >= checker.size() || w[k] != checker[kmp_pos] ||
                    kmp_pos >= (m - j - 1) / 2)) {
                kmp_pos = pf[kmp_pos - 1];
            }
            if (kmp_pos < (m - j - 1) / 2) {
                if (w[k] == checker[kmp_pos]) {
                    kmp_pos++;
                }
            }
            k++;
        }
        trie_node = bud.trie[trie_node].edges[cindex(w[j])];
        if (trie_node == -1)
            break;

        if (bud.trie[trie_node].end && kmp_pos >= (m - j - 1) / 2 &&
            i != bud.trie[trie_node].mark) {
            if (reversed) {
                if (seen.find(make_tuple(bud.trie[trie_node].mark, i)) ==
                    seen.end()) {
                    output.push_back({bud.trie[trie_node].mark, i});
                    seen.insert(make_tuple(bud.trie[trie_node].mark, i));
                }
            } else {
                if (seen.find(make_tuple(i, bud.trie[trie_node].mark)) ==
                    seen.end()) {
                    output.push_back({i, bud.trie[trie_node].mark});
                    seen.insert(make_tuple(i, bud.trie[trie_node].mark));
                }
            }
        }
    }
}

class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string> &words) {

        int n = words.size();
        unordered_set<tuple<int, int>, tuple_hash> seen;
        vector<vector<int>> output;

        Trie bud;
        Trie bud2;
        for (int i = 0; i < n; i++) {
            string add = words[i];
            bud2.add_string(add, i);
            reverse(add.begin(), add.end());
            bud.add_string(add, i);
        }

        for (int i = 0; i < n; i++) {

            int m = words[i].size();
            if (m == 0) {
                continue;
            }
            string w = words[i];
            solve(output, bud, w, i, false, seen);
            reverse(w.begin(), w.end());
            solve(output, bud2, w, i, true, seen);
        }

        return output;
    }
};
