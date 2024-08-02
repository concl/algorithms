class Solution:
    def generate(self, numRows):
        output = [[1]]  # define the first row
        
        # the first row is already defined, so we only need to create numRows - 1 more rows
        for i in range(1, numRows):
            previous_row = output[-1]
            current_row = [1]
            # the front and the back of the row is 1, so we only need to generate i - 1 elements.
            for j in range(i - 1):
                current_row.append(previous_row[j] + previous_row[j + 1])
            current_row.append(1)
            output.append(current_row)
        
        return output