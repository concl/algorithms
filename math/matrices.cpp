
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

        Matrix(int rows, int cols):
            rows(rows), cols(cols)
        {
            mat.resize(rows * cols);
        }

        Matrix(int rows, int cols, T initial):
            rows(rows), cols(cols)
        {
            mat.resize(rows * cols, initial);
        }

        Matrix(int rows, int cols, T initial):
            rows(rows), cols(cols)
        {
            mat.resize(rows * cols, initial);
        }

        Matrix operator+(Matrix &other) {

            Matrix output(rows, cols);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; i++) {
                    output.mat[i][j] = mat[i][j] + other.mat[i][j];
                }
            }
            return output;
        }

        Matrix operator-(Matrix &other) {
            if (rows != other.rows || cols != other.cols)
                throw invalid_argument("Matrices are not the same size");

            Matrix output(rows, cols);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; i++) {
                    output.mat[i][j] = mat[i][j] - other.mat[i][j];
                }
            }
            return output;
        }

        Matrix operator*(Matrix &other) {
            // return output;
            if (cols != other.rows)
                throw invalid_argument("Matrices are not conformable for multiplication");

            T base(0);
            Matrix output(rows, other.cols, base);
            for (int i = 0; i < rows; i++) {
                for (int k = 0; k < cols; k++) {
                    for (int j = 0; j < other.cols; j++) {
                        output.mat[i][j] += mat[i][k] * other.mat[k][j]
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

            // for (int i = 0; i < rows; i++) {
            //     int best = i;
            //     for (int j = i + 1; j < rows; j++) {
            //         if (abs(mat[j][i]) > abs(mat[best][i])) {
            //             best = j;
            //         }
            //     }
            //     if (best != i) {
            //         swap(mat[i], mat[best]);
            //         swap(output.mat[i], output.mat[best]);
            //     }
            //     if (mat[i][i] == 0) {
            //         throw invalid_argument("Matrix is not invertible");
            //     }
            //     T div = mat[i][i];
            //     for (int j = 0; j < rows; j++) {
            //         mat[i][j] /= div;
            //         output.mat[i][j] /= div;
            //     }
            //     for (int j = 0; j < rows; j++) {
            //         if (j != i) {
            //             T mult = mat[j][i];
            //             for (int k = 0; k < rows; k++) {
            //                 mat[j][k] -= mat[i][k] * mult;
            //                 output.mat[j][k] -= output.mat[i][k] * mult;
            //             }
            //         }
            //     }
            // }
            // return output;
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

        friend std::ostream& operator<<(std::ostream& os, const Matrix& p) {
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

    Matrix<ll> fib(2, 2, {{1, 1}, {1, 0}});

    for (int i = 0; i < 250; i++) {
        cout << i << endl;
        pow(fib, i).print();
    }
    
    return 0;
}