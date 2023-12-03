
// 122. Best Time to Buy and Sell Stock II [medium]
// Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        
        int output = 0;
        int bought = INT_MAX;
        int prev = INT_MAX;
        for (int x : prices) {
            if (x < prev) {
                output += prev - bought;
                bought = x;
            }
            prev = x;
        }

        return output + prev - bought;

    }
};