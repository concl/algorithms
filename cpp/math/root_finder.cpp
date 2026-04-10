/**
 * Author: concl
 * Status: Untested
 * Tags: root finding, Newton's method, numerical methods
 */

#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1);

/**
 * Finds a root of the differentiable function f, given an initial guess.
 *
 * f: The function where we want to find a root of.
 * f_prime: The derivative of f.
 * init: The initial guess for the root.
 * max_iter: The maximum number of iterations to run.
 * eps: The tolerance for a root. The function will terminate if the current guess ever has absolute value less than eps
 *
 */
double newtons(function<double(double)> f, function<double(double)> f_prime, double init, int max_iter = 100, double eps = 1e-9) {

    double x = init;
    for (int i = 0; i < max_iter; i++) {

        double fx = f(x);
        if (abs(fx) < eps)
            return x;

        double slope = f_prime(x);
        if (abs(slope) < eps)
            cerr << "Slope is very close to 0 at this point" << endl;
        x = x - fx / slope;
    }

    cerr << "Maximum iterations done without convergence" << endl;
    return x;
}

int main() {

    auto f = [](double x) { return sin(x); };
    auto f_prime = [](double x) { return cos(x); };

    double root = newtons(f, f_prime, 1.571);

    cout << setprecision(12) << newtons(f, f_prime, 1.571);
    return 0;
}