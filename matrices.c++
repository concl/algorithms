#include <bits/stdc++.h>
#define ll long long
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vll vector<ll>
#define vvi vector<vi>
#define vvl vector<vll>
#define all(x) (x).begin(), (x).end()
#define elif else if
using namespace std;

// unfinished by a long shot

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
            // if (m != other.n)
            //     throw invalid_argument("Matrices are not the same size");

            // Matrix output(n, other.m);
            // for (int i = 0; i < other.m; i++) {
            //     for (int j = 0; j < n; j++) {
            //         T item(0);
            //         for (int k = 0; k < m; k++) {
            //             item += mat[j][k] * other.mat[k][i];
            //         }
            //         output.mat[j][i] = item;
            //     }
            // }


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

        void print() {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << mat[i][j] << "\t";
                }
                cout << endl;
            }
        }
};



int main() {

    Matrix<double> x(
        3, 3,
        vector<vector<double>> {
            {1,2,4},
            {2,1,53},
            {51,2,1}
        }
    );

    Matrix<double> y = x.inverse();

    y.print();
    

    Matrix<double> z = x * y;
    z.print();


    
    return 0;
}