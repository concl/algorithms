/**
 * IO harness for fft
 * 
 * Input format:
 * n
 * a_1, a_2, ..., a_n
 * 
 * where a_i is a floating point number.
 * 
 * Output:
 * A line of space-separated bracketed pairs (x, y), each of which representing A_i = x + iy, where A_i
 * is the ith term in the dft of a.
 */

#include "../../cpp/math/fft.cpp"

int main() {
    
    int n;
    cin >> n;
    vector<double> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<Complex> A = fft(a);
    
    cout.precision(17);
    for (const Complex& z : A) {
        cout << z << ' ';
    }
    cout << endl;
}

