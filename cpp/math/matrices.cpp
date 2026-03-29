/**
 * Author: concl
 * Status: Untested
 */

#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

// unfinished by a long shot
const long long MOD = 1000000007;

template <typename T>
class Matrix {
public:
    int rows, cols;
    vector<T> mat;

    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        mat.resize(rows * cols);
    }

    Matrix(int rows, int cols, T initial) : rows(rows), cols(cols) {
        mat.resize(rows * cols, initial);
    }

    Matrix(vector<vector<T>> matrix) {
        rows = matrix.size();
        cols = matrix[0].size();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                mat[i * rows + j] = matrix[i][j];
            }
        }
    }

    Matrix operator+(Matrix &other) {
        if (rows != other.rows || cols != other.cols)
            throw invalid_argument("Matrices are not the same size");
        
        Matrix output(rows, cols);
        for (int i = 0; i < rows * cols; i++) {
            output.mat[i] = mat[i] + other.mat[i];
        }
        return output;
    }

    Matrix operator-(Matrix &other) {
        if (rows != other.rows || cols != other.cols)
            throw invalid_argument("Matrices are not the same size");

        Matrix output(rows, cols);
        for (int i = 0; i < rows * cols; i++) {
            output.mat[i] = mat[i] - other.mat[i];
        }
        return output;
    }

    Matrix operator*(Matrix &other) {
        if (cols != other.rows)
            throw invalid_argument("Matrices are not conformable for multiplication");

        T base(0);
        Matrix output(rows, other.cols, base);
        for (int i = 0; i < rows; i++) {
            for (int k = 0; k < cols; k++) {
                for (int j = 0; j < other.cols; j++) {
                    output.mat[i * rows + j] += mat[i * rows + k] * other.mat[k * other.rows + j];
                }
            }
        }

        return output;
    }

    Matrix inverse() {
        if (rows != cols)
            throw invalid_argument("Matrix is not square");

        Matrix output(rows, cols);
        for (int i = 0; i < rows; i++) {
            output.mat[i][i] = 1;
        }

        // TODO
    }

    Matrix transpose() {
        Matrix output(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                output.mat[j][i] = mat[i][j];
            }
        }
        return output;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &p) {
        for (int i = 0; i < p.rows; i++) {
            for (int j = 0; j < p.cols; j++) {
                cout << mat[i][j] << "\t";
            }
            cout << endl;
        }
    }
};

template <typename T>
Matrix<T> pow(Matrix<T> mat, ll p) {
    if (mat.rows != mat.cols)
        throw invalid_argument("Matrix is not square");

    // identity matrix
    Matrix<T> output(mat.rows, mat.rows);
    for (int i = 0; i < mat.rows; i++) {
        output.mat[i][i] = 1;
    }

    while (p) {
        if (p & 1) {
            output = output * mat;
        }
        mat = mat * mat;
        p >>= 1;
    }

    return output;
}

int main() {

    Matrix<int> mat(2, 2);
    Matrix<int> mat2 = mat * mat;

    Matrix<ll> fib({{1, 1}, {1, 0}});

    for (int i = 0; i < 250; i++) {
        cout << i << endl;
        cout << pow(fib, i) << endl;
    }

    return 0;
}