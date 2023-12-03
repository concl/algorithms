
#include <bits/stdc++.h>
#define ll long long
#define Poly vector<complex<double>>
#define Comp complex<double>

const double PI = acos(-1);

using namespace std;

int next_power_of_two(int n) {
    if (n <= 1) return 2;

    // Set all bits after the highest set bit
    n |= (n >> 1);
    n |= (n >> 2);
    n |= (n >> 4);
    n |= (n >> 8);
    n |= (n >> 16);

    // Increment to get the next power of two
    return n + 1;
}

void preprocessing(Poly& polynomial, vector<Comp>& lookup) {

    int n = polynomial.size();
    int new_size = next_power_of_two(n);

    for (int i = n; i < new_size; i++) {
        polynomial.push_back(Comp(0, 0));
    }

    double angle = 0;
    for (int i = 0; i < new_size; i++) {
        lookup[i] = Comp(cos(angle),sin(angle));
        angle += 2 * PI / new_size;
    }
}

Poly dft(Poly polynomial) {
    int n = polynomial.size();
    
}

Poly idft(Poly transformed) {
    int n = transformed.size();
    
}


int main() {

    return 0;
}