/**
 * Author: concl
 * Status: Untested
 */

#include <bits/stdc++.h>

using namespace std;

bool is_power_of_two(uint64_t n) {
    return (n & (n - 1)) == 0;
}

uint32_t next_power_of_two(uint32_t n) {
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

uint64_t next_power_of_two(uint64_t n) {
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
int64_t log2_floor(int64_t x) {
    // __builtin_clzll is built in count leading zeros for long long
    return x ? __builtin_clzll(1) - __builtin_clzll(x) : -1; 
}


// Returns the number of 1-bits in x
int bit_count(uint32_t x) {
    return __builtin_popcount(x);
}