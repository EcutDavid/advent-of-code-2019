#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef int i32;

i32 main() {
  i64 sum = 0, mass;
  while (cin >> mass) {
    while (mass / 3 > 2) {
      mass = mass / 3 - 2;
      sum += mass;
    }
  }

  cout << sum << endl;
}
