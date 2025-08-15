
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

// unfinished by a long shot
const long long MOD = 1000000007;

template <typename T>
class Matrix {

    public:
        int rows, cols;
        vector<vector<T>> mat;

        Matrix() {
            rows = 0;
            cols = 0;
        }

        Matrix(int rows, int cols) {
            this->rows = rows;
            this->cols = cols;
            mat.resize(rows, vector<T>(cols));
        }

        Matrix(int rows, int cols, T initial) {
            this->rows = rows;
            this->cols = cols;
            mat.resize(rows, vector<T>(cols, initial));
        }

        Matrix(int rows, int cols, vector<vector<T>> mat) {
            this->rows = rows;
            this->cols = cols;
            this->mat = mat;
        }

        static Matrix column_vector(vector<T> v) {
            Matrix output(v.size(), 1);
            for (int i = 0; i < v.size(); i++) {
                output.mat[i][0] = v[i];
            }
            return output;
        }

        static Matrix row_vector(vector<T> v) {
            Matrix output(1, v.size());
            for (int i = 0; i < v.size(); i++) {
                output.mat[0][i] = v[i];
            }
            return output;
        }

        Matrix operator+(Matrix &other) {
            if (rows != other.rows || cols != other.cols)
                throw invalid_argument("Matrices are not the same size");

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

        void print() {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
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

    Matrix<int> mat(2, 2, {{1, 1}, {1, 0}});

    Matrix<int> mat2 = mat * mat;

    mat2.print();

    Matrix<ll> fib(2, 2, {{1, 1}, {1, 0}});

    for (int i = 0; i < 250; i++) {
        cout << i << endl;
        pow(fib, i).print();
    }
    
    return 0;
}