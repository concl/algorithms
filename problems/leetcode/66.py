
# 66. Plus One
# https://leetcode.com/problems/plus-one/

class Solution:
    def plusOne(self, digits):
        n = len(digits)
        output = digits[:]
        for i in range(n - 1, -1, -1):
            output[i] += 1
            if output[i] < 10:
                break
            else:
                output[i] = 0
        if output[0] == 0:
            output.insert(0, 1)
        return output