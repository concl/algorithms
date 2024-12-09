
#include <bits/stdc++.h>
#define ll long long
#define Poly vector<complex<double>>
#define Comp complex<double>
#define forn(i,n) for(int i=0;(i)<(n);i++) 

template<typename A> ostream& operator<< (ostream &cout, vector<A> const&v) {
    cout << "["; forn(i,(int)v.size()){ if (i) cout << ", "; cout << v[i];} return cout << "]";
}

const double PI = acos(-1);

using namespace std;

// Returns the floor of the base 2 logarithm of x
long long log2_floor(unsigned long long x) {
    // __builtin_clzll is built in count leading zeros for long long
    return x ? __builtin_clzll(1) - __builtin_clzll(x) : -1; 
}

// Returns the number of 1-bits in x
int one_bits(uint32_t x) {
    return __builtin_popcount(x);
}

int next_power_of_two(int n) {
    if (one_bits(n) <= 1) return n << 1;
    else {
        return 1 << (log2_floor(n) + 2);
    }
}


// extends polynomial to next power of two and returns the lookup table
vector<Comp> preprocessing(Poly& polynomial, int new_size) {

    int n = polynomial.size();
    for (int i = n; i < new_size; i++) {
        polynomial.push_back(Comp(0, 0));
    }

    vector<Comp> lookup(new_size);

    double root_angle = 2 * PI / new_size;
    double angle = 0;
    for (int i = 0; i < new_size; i++) {
        lookup[i] = Comp(cos(angle),sin(angle));
        angle = root_angle * (i + 1);
    }

    return lookup;
}
vector<Comp> preprocessing(Poly& polynomial) {
    int n = polynomial.size();
    int new_size = next_power_of_two(n);
    return preprocessing(polynomial, new_size);
}


// input must be of power of 2 size
// lookup is an array of all the roots of unity
// ind is the index of the primitive root of unity for the given dft
Poly dft(Poly& polynomial, vector<Comp>& lookup, int ind) {
    int n = polynomial.size();
    if (n == 1) {
        return {polynomial[0]};
    }

    Poly even;
    Poly odd;

    for (int i = 0; i < n; i+=2) {
        even.push_back(polynomial[i]);
        odd.push_back(polynomial[i + 1]);
    }

    even = dft(even, lookup, ind * 2);
    odd = dft(odd, lookup, ind * 2);

    Poly transformed(n);
    int current = 0;

    for (int i = 0; i < n / 2; i++) {
        transformed[i] = even[i] + odd[i] * lookup[current];
        current += ind + n;
        current %= n;
    }

    current = 0;
    for (int i = n / 2; i < n; i++) {
        transformed[i] = even[i - n / 2] - odd[i - n / 2] * lookup[current];
        current += ind + n;
        current %= n;
    }
    return transformed;    
}

Poly dft(Poly& polynomial, vector<Comp>& lookup) {
    return dft(polynomial, lookup, 1);
}

Poly idft(Poly& transformed, vector<Comp>& lookup) {
    int n = transformed.size();
    Poly polynomial = dft(transformed, lookup, -1);
    for (int i = 0; i < n; i++) {
        polynomial[i] /= n;
    }
    return polynomial;
}




int main() {


    Poly polynomial1 = {1, 2};
    Poly polynomial2 = {2, 3};
    vector<Comp> lookup = preprocessing(polynomial1);
    preprocessing(polynomial2);

    cout << polynomial1 << endl;
    cout << polynomial2 << endl;
    cout << lookup << endl;
    
    
    Poly d1 = dft(polynomial1, lookup);
    Poly d2 = dft(polynomial2, lookup);

    cout << endl;
    cout << d1 << endl;
    cout << d2 << endl;
    
    Poly con;
    for (int i = 0; i < d1.size(); i++) {
        con.push_back(d1[i] * d2[i]);
    }

    Poly test = {2, 7, 6, 0};
    cout << dft(test, lookup) << endl;
    cout << con << endl;

    cout << idft(con, lookup) << endl;



    return 0;
}