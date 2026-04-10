#include "../cpp/math/matrices.cpp"
#include <bits/stdc++.h>

/**
 * Tests a simple linear system.
 * 
 * The system is:
 * Ax = b
 * where A = [[2, 1], [1, 1]] and b = [[5], [3]]
 * 
 * The solution is x = [[2], [1]]
 */
void test_linear_system_1() {
    vector<vector<double>> A = {{2, 1}, {1, 1}};
    vector<vector<double>> B = {{5}, {3}};
    
    Matrix<double> a(A);
    Matrix<double> b(B);
    
    Matrix<double> c = a.concat(b, 1);
    
    c.RREF();
    
    assert(abs(c.get(0, 2) - 2) < EPS);
    assert(abs(c.get(1, 2) - 1) < EPS);
}

/**
 * Tests finding the inverse of a simple matrix with RREF.
 * 
 * The matrix is A = [[2, 1], [1, 1]]
 * The inverse is A^-1 = [[1, -1], [-1, 2]]
 */
void test_inverse_1() {
    vector<vector<double>> A = {{2, 1}, {1, 1}};
    
    Matrix<double> a(A);
    Matrix<double> identity = Matrix<double>::identity(2);
    
    Matrix<double> augmented = a.concat(identity, 1);
    
    augmented.RREF();
    
    Matrix<double> inverse = augmented.submatrix(0, 2, 2, 4);
    
    assert(abs(inverse.get(0, 0) - 1) < EPS);
    assert(abs(inverse.get(0, 1) + 1) < EPS);
    assert(abs(inverse.get(1, 0) + 1) < EPS);
    assert(abs(inverse.get(1, 1) - 2) < EPS);
}

void run_tests() {
    cout << "Running tests..." << endl;
    
    cout << "Testing linear system..." << endl;
    test_linear_system_1();
    
    cout << "Testing matrix inverse..." << endl;
    test_inverse_1();
    
    cout << "All tests passed!" << endl;
}

int main() {
    
    run_tests();
    
    return 0;
}
