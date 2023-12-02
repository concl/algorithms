
// 1611. Minimum One Bit Operations to Make Integers Zero [hard]
// Link: https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero/

// Notice that the minimum number of operations to obtain n starting from 0 is the same as the minimum number of operations to obtain 0 starting from n.
// For the highest bit, in position i, the smallest number of operations to obtain it from 0 is 2^i
// Obtaining the highest bit creates another residual bit that can be used to obtain the next highest bit
// The smallest bit that doesn't have a pair with another bit takes 2^(i + 1) - 1 operations to obtain

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

