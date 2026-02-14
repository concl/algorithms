
#include <bits/stdc++.h>

const double PI = acos(-1);
using namespace std;

double newtons(function<double(double)> f, function<double(double)> f_prime, double init, int max_iter = 100, double eps=1e-9) {

    double x = init;
    for (int i = 0; i < max_iter; i++) {

        double fx = f(x);
        double slope = f_prime(x);

        if (slope < eps) {
            std::cerr << "Warning: Derivative is too small at iteration " << i << ". No convergence.\n";
            return x;
        }

        double next = x - fx / slope;

        if (abs(next - x) < eps) {
            return next;
        }
        x = next;
    }

    std::cerr << "Warning: Reached maximum iterations without convergence.\n";
    return x;
}



int main() {

    cout << setprecision(12) << newtons([](double x){return sin(x);}, [](double x){return cos(x);}, 1.571);
    return 0;
}