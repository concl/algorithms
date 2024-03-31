
// 300. Longest Increasing Subsequence
// https://leetcode.com/problems/longest-increasing-subsequence/

#include <bits/stdc++.h>

using namespace std;

int bs(vector<int>& arr, int x){

    int hi = arr.size();
    int lo = 0;

    int check = (hi + lo) / 2;

    while (hi > lo){
        if (arr[check] >= x){
            hi = check;
        }
        else if (arr[check] < x){
            lo = check + 1;
        }
        check = (hi + lo) / 2;
    }
    return check;

}

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        
        // smallest number for each length
        vector<int> smallest;

        for (int x : nums) {

            int ind = bs(smallest, x);
            if (ind == smallest.size()) {
                smallest.push_back(x);
            } else {
                smallest[ind] = x;
            }
        }

        return smallest.size();

    }
};