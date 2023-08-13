
#include <bits/stdc++.h>
#define ll long long

using namespace std;

// unfinished by a long shot
const long long MOD = 1000000007;

class CyclicGroup {
private:
    long long value;
    long long mod;

public:
    // Default constructor
    CyclicGroup() : value(0), mod(1000000007) {}

    // Constructor with value and mod
    CyclicGroup(long long value, long long mod = 1000000007) : value(value % mod), mod(mod) {}

    // Overloaded addition operator
    CyclicGroup operator+(const CyclicGroup& other) const {
        return CyclicGroup((value + other.value) % mod, mod);
    }

    // Overloaded subtraction operator
    CyclicGroup operator-(const CyclicGroup& other) const {
        return CyclicGroup((value - other.value + mod) % mod, mod);
    }

    // Overloaded multiplication operator
    CyclicGroup operator*(const CyclicGroup& other) const {
        return CyclicGroup((value * other.value) % mod, mod);
    }

    // Overloaded division operator
    CyclicGroup operator/(const CyclicGroup& other) const {
        long long inv = 1, base = other.value;
        long long exponent = mod - 2;
        while (exponent > 0) {
            if (exponent & 1) inv = (inv * base) % mod;
            base = (base * base) % mod;
            exponent >>= 1;
        }
        return CyclicGroup((value * inv) % mod, mod);
    }

    // Overloaded compound assignment operators
    CyclicGroup& operator+=(const CyclicGroup& other) {
        value = (value + other.value) % mod;
        return *this;
    }

    CyclicGroup& operator-=(const CyclicGroup& other) {
        value = (value - other.value + mod) % mod;
        return *this;
    }

    CyclicGroup& operator*=(const CyclicGroup& other) {
        value = (value * other.value) % mod;
        return *this;
    }

    CyclicGroup& operator/=(const CyclicGroup& other) {
        *this = *this / other;
        return *this;
    }

    // Overloaded stream insertion operator for printing
    friend std::ostream& operator<<(std::ostream& os, const CyclicGroup& group) {
        os << group.value;
        return os;
    }
};

template <typename T>
class Matrix {

    public:
        int n, m;
        vector<vector<T>> mat;

        Matrix() {
            n = 0;
            m = 0;
        }

        Matrix(int n, int m) {
            this->n = n;
            this->m = m;
            mat.resize(n, vector<T>(m));
        }

        Matrix(int n, int m, vector<vector<T>> mat) {
            this->n = n;
            this->m = m;
            this->mat = mat;
        }

        static Matrix column_vector(vector<T> v) {
            Matrix output(v.size(), 1);
            for (int i = 0; i < v.size(); i++) {
                output.mat[i][0] = v[i];
            }
            return output;
        }

        Matrix row_vector(vector<T> v) {
            Matrix output(1, v.size());
            for (int i = 0; i < v.size(); i++) {
                output.mat[0][i] = v[i];
            }
            return output;
        }

        Matrix operator+(Matrix &other) {
            if (n != other.n || m != other.m)
                throw invalid_argument("Matrices are not the same size");

            Matrix output(n, m);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; i++) {
                    output.mat[i][j] = mat[i][j] + other.mat[i][j];
                }
            }
            return output;
        }

        Matrix operator-(Matrix &other) {
            if (n != other.n || m != other.m)
                throw invalid_argument("Matrices are not the same size");

            Matrix output(n, m);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; i++) {
                    output.mat[i][j] = mat[i][j] - other.mat[i][j];
                }
            }
            return output;
        }

        Matrix operator*(Matrix &other) {
            // return output;
            if (m != other.n)
                throw invalid_argument("Matrices are not conformable for multiplication");

            Matrix output(n, other.m);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < other.m; j++) {
                    T item(0);
                    for (int k = 0; k < m; k++) {
                        item += mat[i][k] * other.mat[k][j];
                    }
                    output.mat[i][j] = item;
                }
            }

            return output;
        }

        

        Matrix inverse() {
            if (n != m)
                throw invalid_argument("Matrix is not square");

            Matrix output(n, m);
            for (int i = 0; i < n; i++) {
                output.mat[i][i] = 1;
            }

            for (int i = 0; i < n; i++) {
                int best = i;
                for (int j = i + 1; j < n; j++) {
                    if (abs(mat[j][i]) > abs(mat[best][i])) {
                        best = j;
                    }
                }
                if (best != i) {
                    swap(mat[i], mat[best]);
                    swap(output.mat[i], output.mat[best]);
                }
                if (mat[i][i] == 0) {
                    throw invalid_argument("Matrix is not invertible");
                }
                T div = mat[i][i];
                for (int j = 0; j < n; j++) {
                    mat[i][j] /= div;
                    output.mat[i][j] /= div;
                }
                for (int j = 0; j < n; j++) {
                    if (j != i) {
                        T mult = mat[j][i];
                        for (int k = 0; k < n; k++) {
                            mat[j][k] -= mat[i][k] * mult;
                            output.mat[j][k] -= output.mat[i][k] * mult;
                        }
                    }
                }
            }
            return output;
        }

        Matrix transpose() {
            Matrix output(m, n);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    output.mat[j][i] = mat[i][j];
                }
            }
            return output;
        }

        void print() {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << mat[i][j] << "\t";
                }
                cout << endl;
            }
        }
};

template <typename T>
Matrix<T> pow(Matrix<T> mat, ll p) {
    if (mat.n != mat.m)
        throw invalid_argument("Matrix is not square");

    // identity matrix
    Matrix<T> output(mat.n, mat.n);
    for (int i = 0; i < mat.n; i++) {
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

    Matrix<CyclicGroup> mat(2, 2, {{1, 1}, {1, 0}});

    Matrix<CyclicGroup> mat2 = mat * mat;

    mat2.print();

    Matrix<ll> fib(2, 2, {{1, 1}, {1, 0}});

    for (int i = 0; i < 250; i++) {
        cout << i << endl;
        pow(fib, i).print();
    }
    
    return 0;
}