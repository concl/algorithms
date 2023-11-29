
#include <bits/stdc++.h>

using namespace std;

bool is_power_of_two(unsigned long long n) {
    return (n & (n - 1)) == 0;
}

unsigned int next_power_of_two(unsigned int n) {
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

unsigned long long next_power_of_two(unsigned long long n) {
    if (n <= 1) return 2;

    // Set all bits after the highest set bit
    n |= (n >> 1);
    n |= (n >> 2);
    n |= (n >> 4);
    n |= (n >> 8);
    n |= (n >> 16);
    n |= (n >> 32);

    // Increment to get the next power of two
    return n + 1;
}

// Returns the floor of the base 2 logarithm of x
int log2_floor(unsigned long long x) {
    return x ? __builtin_clzll(1) - __builtin_clzll(x) : -1;
}


// Returns the number of 1-bits in x
int one_bits(uint32_t x) {
    return __builtin_popcount(x);
}