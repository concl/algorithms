
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        
        vector<vector<int>> output = {{},{}};

        unordered_set<int> never_lost;
        unordered_set<int> lost_once;
        unordered_set<int> loser;

        for (auto x : matches) {
            if (!never_lost.count(x[0]) && !lost_once.count(x[0]) && !loser.count(x[0])) {
                never_lost.insert(x[0]);
            }
            if (!never_lost.count(x[1]) && !lost_once.count(x[1]) && !loser.count(x[1])) {
                lost_once.insert(x[1]);
            } else if (never_lost.count(x[1])) {
                lost_once.insert(x[1]);
                never_lost.erase(x[1]);
            } else if (lost_once.count(x[1])) {
                loser.insert(x[1]);
                lost_once.erase(x[1]);
            }
        }

        for (int x : never_lost) {
            output[0].push_back(x);
        }
        for (int x : lost_once) {
            output[1].push_back(x);
        }

        sort(output[0].begin(),output[0].end());
        sort(output[1].begin(),output[1].end());
        return output;


    }
};