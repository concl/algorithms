

// 2976. Minimum Cost to Convert String I
// https://leetcode.com/problems/minimum-cost-to-convert-string-i/


#include <bits/stdc++.h>

using namespace std;

unordered_map<char,int> create(vector<unordered_map<char,int>>& graph, char source) {

    unordered_map<char,int> output;

    priority_queue<pair<int, char>, vector<pair<int,char>>, greater<pair<int,char>>> pq;
    pq.push({0, source});

    while (pq.size() > 0) {

        auto f = pq.top();
        pq.pop();

        if (output.count(f.second)) {
            continue;
        }
        output[f.second] = f.first;

        for (auto& kv : graph[f.second - 'a']) {
            pq.push({f.first + kv.second, kv.first});
        }
    }
    return output;

}

class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost_input) {
        vector<unordered_map<char,int>> cost(26);
        vector<unordered_map<char,int>> graph(26);

        for (int i = 0; i < original.size(); i++) {
            if (graph[original[i] - 'a'].count(changed[i])) {
                graph[original[i] - 'a'][changed[i]] = min(graph[original[i] - 'a'][changed[i]], cost_input[i]);
            } else {
                graph[original[i] - 'a'][changed[i]] = cost_input[i];
            }
        }

        for (int i = 0; i < 26; i++) {
            cost[i] = create(graph, i + 'a');
        }
         
        long long output = 0;
        for (int i = 0; i < source.size(); i++) {
            if (cost[source[i] - 'a'].count(target[i])) {
                output += cost[source[i] - 'a'][target[i]];
            } else {
                return -1;
            }
        }
        return output;
    }
};