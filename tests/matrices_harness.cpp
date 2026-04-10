#include "../cpp/math/matrices.cpp"
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 1;
    }

    vector<vector<double>> A(n, vector<double>(n));
    vector<vector<double>> B(n, vector<double>(1));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> B[i][0];
    }

    Matrix<double> a(A);
    Matrix<double> b(B);

    Matrix<double> augmented_system = a.concat(b, 1);
    augmented_system.RREF();

    Matrix<double> identity = Matrix<double>::identity(n);
    Matrix<double> augmented_inverse = a.concat(identity, 1);
    augmented_inverse.RREF();

    cout << setprecision(17);

    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << augmented_system.get(i, n);
    }
    cout << "\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j) cout << ' ';
            cout << augmented_inverse.get(i, n + j);
        }
        cout << "\n";
    }

    return 0;
}
