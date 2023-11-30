
// 1611. Minimum One Bit Operations to Make Integers Zero [hard]
// Link: https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero/

// Author: Luke Zeng

class Solution {
public:
    int minimumOneBitOperations(int n) {
        if (n <= 1) {
            return n;
        }

        int out = 0;
        bool paired = false;

        for (int i = 31; i >= 0; i--) {
            if (n & (1 << i)) {
                if (!paired) {
                    out += 1 << i;
                    paired = true;
                } else {
                    paired = false;
                }
            } else {
                if (paired) {
                    out += 1 << i;
                }
            }
        }
        return out;
    }
};

