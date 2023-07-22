#include <iostream>

// This was written by ChatGPT. It uses Newton's method until it reaches the desired result.

int int_sqrt(int n) {
  // Base case
  if (n < 2) {
    return n;
  }

  // Initialize variables
  int x = n;
  int y = (x + n/x) / 2;

  // Iterate until convergence
  while (y < x) {
    x = y;
    y = (x + n/x) / 2;
  }
  return x;
}

int ceil_sqrt(int n){
    // Base case
  if (n < 2) {
    return n;
  }

  // Initialize variables
  int x = n;
  int y = (x + n/x) / 2;

  // Iterate until convergence
  while (y < x) {
    x = y;
    y = (x + n/x) / 2;
  }
  return x + (int)(x * x < n);
}

int main() {
  std::cout << int_sqrt(16) << std::endl;  // Output: 4
  std::cout << int_sqrt(25) << std::endl;  // Output: 5
  std::cout << int_sqrt(36) << std::endl;  // Output: 6
  std::cout << int_sqrt(2) << std::endl;   // Output: 1
  return 0;
}
