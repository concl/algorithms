// 189. Rotate Array
// Link: https://leetcode.com/problems/rotate-array/

#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) {
    while (b % a != 0) {
        b %= a;
        swap(a,b);
    }
    return a;
}

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        
        int n = nums.size();
        k %= n;
        int current = 0;
        int carry;
        int most = gcd(n,k);

        for (int start = 0; start < most; start++) {
            int carry = nums[start];
            int current = (start + k) % n;
            int temp;

            while (current != start) {
                temp = nums[current];
                nums[current] = carry;
                carry = temp;

                current += k;
                current %= n;
            }
            nums[current] = carry;
        }
    }
};