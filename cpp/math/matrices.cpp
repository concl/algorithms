/**
 * Author: concl
 * Status: RREF is somewhat tested with random matrices.
 * Matrix exponentiation is somewhat tested on Fibonacci numbers.
 * TODO: implement and test inverse, determinant, and RREF with both double and modular arithmetic
 * Tags: matrices, linear algebra, RREF, matrix exponentiation
 */

#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

const double EPS = 1e-9;

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
        mat.resize(rows * cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                get(i, j) = matrix[i][j];
            }
        }
    }

    static Matrix identity(int n) {
        Matrix res(n, n, 0);
        for (int i = 0; i < n; i++) {
            res.get(i, i) = 1;
        }
        return res;
    }

    inline T& get(int i, int j) {
        return mat[i * cols + j];
    }

    inline const T& get(int i, int j) const {
        return mat[i * cols + j];
    }

    Matrix operator+(Matrix &other) const {
        if (rows != other.rows || cols != other.cols)
            throw invalid_argument("Matrices are not the same size");

        Matrix output(rows, cols);
        for (int i = 0; i < rows * cols; i++) {
            output.mat[i] = mat[i] + other.mat[i];
        }
        return output;
    }

    Matrix operator-(Matrix &other) const {
        if (rows != other.rows || cols != other.cols)
            throw invalid_argument("Matrices are not the same size");

        Matrix output(rows, cols);
        for (int i = 0; i < rows * cols; i++) {
            output.mat[i] = mat[i] - other.mat[i];
        }
        return output;
    }

    Matrix matmul(Matrix &other) const {
        if (cols != other.rows)
            throw invalid_argument("Matrices are not conformable for multiplication");

        T base(0);
        Matrix output(rows, other.cols, base);
        for (int i = 0; i < rows; i++) {
            for (int k = 0; k < cols; k++) {
                for (int j = 0; j < other.cols; j++) {
                    output.get(i, j) += get(i, k) * other.get(k, j);
                }
            }
        }

        return output;
    }
    
    /**
     * Concatenates two matrices along the specified dim.
     *
     * dim = 0: concatenate vertically (along the row axis)
     * dim = 1: concatenate horizontally (along the column axis)
     */
    Matrix concat(Matrix& other, int dim=0) const {
        if (dim == 0) {
            if (cols != other.cols)
                throw invalid_argument("Matrices are not conformable for concatenation");

            Matrix output(rows + other.rows, cols);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    output.get(i, j) = get(i, j);
                }
            }
            for (int i = 0; i < other.rows; i++) {
                for (int j = 0; j < other.cols; j++) {
                    output.get(rows + i, j) = other.get(i, j);
                }
            }
            return output;
        } else if (dim == 1) {
            if (rows != other.rows)
                throw invalid_argument("Matrices are not conformable for concatenation");

            Matrix output(rows, cols + other.cols);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    output.get(i, j) = get(i, j);
                }
            }
            for (int i = 0; i < other.rows; i++) {
                for (int j = 0; j < other.cols; j++) {
                    output.get(i, cols + j) = other.get(i, j);
                }
            }
            return output;
        } else {
            throw invalid_argument("Axis must be 0 or 1");
        }
    }
    
    Matrix submatrix(int row_start, int row_end, int col_start, int col_end) const {
        Matrix output(row_end - row_start, col_end - col_start);
        for (int i = row_start; i < row_end; i++) {
            for (int j = col_start; j < col_end; j++) {
                output.get(i - row_start, j - col_start) = get(i, j);
            }
        }
        return output;
    }

    Matrix transpose() const {
        Matrix output(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                output.get(j, i) = get(i, j);
            }
        }
        return output;
    }

    /**
     * Converts the matrix to its row reduced echelon form
     * Useful for computing matrix inverses or solving systems of linear equations
     * Assumes that T = double
     */
    void RREF() {

        for (int ro = 0; ro < rows; ro++) {

            T curr = get(ro, ro);
            int idx = ro;
            for (int lower = ro + 1; lower < rows; lower++) {
                if (abs(get(lower, ro)) > abs(curr)) {
                    curr = get(lower, ro);
                    idx = lower;
                }
            }

            if (abs(curr) < EPS) continue;

            // swap rows
            if (idx != ro) {
                for (int co = 0; co < cols; co++)
                    swap(get(ro, co), get(idx, co));
            }

            for (int other = 0; other < rows; other++) {
                if (other == ro) continue;

                T factor = get(other, ro) / get(ro, ro);
                for (int co = ro; co < cols; co++)
                    get(other, co) -= factor * get(ro, co);
            }

            T pivot = get(ro, ro);
            for (int co = ro; co < cols; co++) {
                get(ro, co) /= pivot;
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &p) {
        for (int i = 0; i < p.rows; i++) {
            for (int j = 0; j < p.cols; j++) {
                cout << p.get(i, j) << "\t";
            }
            cout << endl;
        }
        return os;
    }
};

template <typename T>
Matrix<T> pow(Matrix<T> mat, ll p) {
    if (mat.rows != mat.cols)
        throw invalid_argument("Matrix is not square");

    int n = mat.rows;

    // Identity matrix
    vector<vector<T>> I(n, vector<T>(n, 0));
    for (int i = 0; i < mat.rows; i++)
        I[i][i] = 1;

    Matrix<T> output(I);

    while (p) {
        if (p & 1)
            output = output.matmul(mat);
        
        mat = mat.matmul(mat);
        p >>= 1;
    }

    return output;
}
