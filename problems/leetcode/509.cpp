// 509. Fibonacci Number
// Link: https://leetcode.com/problems/fibonacci-number/

#include <bits/stdc++.h>

using namespace std;

// Define the type for a 2x2 matrix
typedef vector<vector<int>> Matrix;

// Function to multiply two 2x2 matrices
Matrix multiply(const Matrix &a, const Matrix &b) {
    Matrix result = {{0, 0}, {0, 0}};
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

Matrix matrix_power(Matrix base, int exp) {
    Matrix result = {{1, 0}, {0, 1}}; // Identity matrix
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = multiply(result, base);
        }
        base = multiply(base, base);
        exp /= 2;
    }
    return result;
}

// Function to calculate the n-th Fibonacci number using matrix exponentiation

class Solution {
public:
    int fib(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;

        Matrix fib_matrix = {{1, 1}, {1, 0}};
        Matrix result = matrix_power(fib_matrix, n - 1);

        // The (0, 0) element of the result matrix is F(n)
        return result[0][0];
    }

};
