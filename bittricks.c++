
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


