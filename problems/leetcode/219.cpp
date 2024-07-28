// 290. Word Pattern
// https://leetcode.com/problems/word-pattern/

#include <bits/stdc++.h>

using namespace std;

vector<string> split(string& str) {
    vector<string> result;
    string word = "";
    
    for (char c : str) {
        if (c == ' ') {
            if (!word.empty()) {
                result.push_back(word);
                word = "";
            }
        } else {
            word += c;
        }
    }
    
    if (!word.empty()) {
        result.push_back(word);
    }
    
    return result;
}

class Solution {
public:
    bool wordPattern(string pattern, string s) {
        
        unordered_map<char, string> conv;
        unordered_set<string> unique;

        vector<string> s_arr = split(s); // splits s by spaces

        if (pattern.size() != s_arr.size()) {
            return false;
        }

        int n = pattern.size(); // same as s_arr.size()
        for (int i = 0; i < n; i++) {

            if (conv.count(pattern[i])) {
                if (s_arr[i] != conv[pattern[i]]) {
                    return false;
                }
            } else {
                conv[pattern[i]] = s_arr[i];
                unique.insert(s_arr[i]);
            }
        }
        
        if (unique.size() != conv.size()) {
            return false;
        }
        return true;

    }
};