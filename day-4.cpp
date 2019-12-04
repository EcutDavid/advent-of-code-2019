#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef int i32;

bool hasSameAdj(vector<int> & p) {
  for (int i = 0; i < p.size(); i++) {
    int d = p[i];
    int counter = 0;
    while(i < p.size() && (p[i] == d)) {
      counter++;
      i++;
    }
    if (counter == 2) return true;
    i--;
  }
  return false;
}

bool isInc(vector<int>& p) {
  for (int i = 1; i < p.size(); i++) {
    if (p[i - 1] < p[i]) return false;
  }
  return true;
}

i32 main() {
  int counter = 0;

  for (int i = 172930; i <= 683082; i++) {
    vector<int> parts = {};
    int num = i;
    while (num) {
      parts.push_back(num % 10);
      num /= 10;
    }
    if (hasSameAdj(parts) && isInc(parts)) counter++;
  }

  cout << counter << endl;
}
