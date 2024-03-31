#include <bits/stdc++.h>
#define ll long long

using namespace std;
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
  cout << int_sqrt(16) << endl;  // Output: 4
  cout << int_sqrt(25) << endl;  // Output: 5
  cout << int_sqrt(36) << endl;  // Output: 6
  cout << int_sqrt(2) << endl;   // Output: 1
  return 0;
}
