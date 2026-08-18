/**
 * Author: concl
 * Status: Tested against random numpy data (need to implement convolution for more verification)
 * Tags: FFT, polynomial multiplication, convolution
 * 
 */

#include "math_base.hpp"
#include "../bit_tricks.hpp"
#include <bits/stdc++.h>

using namespace std;

using Complex = complex<double>;

vector<Complex> fft(const vector<double> &a) {
    if (a.size() == 1) {
        return {Complex(a[0], 0)};
    }

    int n = a.size();
    int N = 1 << (log2_floor(n - 1) + 1);
    vector<Complex> A(N, Complex(0, 0));

    for (int i = 0; i < n; i++) {
        A[i] = Complex(a[i], 0);
    }

    vector<Complex> roots(N);
    for (int i = 0; i < N; i += 1) {
        double angle = 2 * PI * i / N;
        roots[i] = polar(1.0, angle);
    }

    for (int jump = N / 2; jump >= 1; jump >>= 1) {
        int fft_size = N / jump;
        vector<Complex> buff(fft_size);

        for (int start = 0; start < jump; start += 1) {
            
            int current_root = 0;
            for (int i = 0; i < fft_size / 2; i += 1) {
                Complex tw = roots[current_root] * A[start + 2 * i * jump + jump];
                buff[i] = A[start + 2 * i * jump] + tw;
                buff[i + fft_size / 2] = A[start + 2 * i * jump] - tw;
                current_root += jump;
            }
            
            for (int i = 0; i < fft_size; i += 1) A[start + i * jump] = buff[i];
        }
    }

    return A;
}