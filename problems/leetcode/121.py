
# brute force

class Solution:
    def maxProfit(self, prices):
        output = 0
        
        for i in range(len(prices)):
            for j in range(i + 1, len(prices)):
                if prices[j] - prices[i] > output:
                    output = prices[j] - prices[i]
                    
        return output
    
# optimized solution

class Solution:
    def maxProfit(self, prices):
        if not prices:
            return 0
        
        output = 0
        current_smallest = prices[0]
        
        for x in prices:
            if x - current_smallest > output:
                output = x - current_smallest
            current_smallest = min(current_smallest, x)
        
        return output