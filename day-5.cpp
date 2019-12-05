#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef int i32;

vector<int> parseModes(int opc){
    vector<int> modes;
    opc /= 100;
    for (int i = 0; i < 3; i++) {
      modes.push_back(opc % 10);
      opc /= 10;
    }
    return modes;
}

i32 main() {
  char c;
  i64 num;
  vector<i64> nums;
  while (cin >> c) {
    if (c == ',') {
      nums.push_back(num);
      num = 0;
      continue;
    }
    num = num * 10 + (c - '0');
  }
  nums.push_back(num);

  i32 pc = 0;
  while (nums[pc] != 99) {
    int opc = nums[pc];

    if (opc == 3) {
      // nums[nums[pc + 1]] = 1; // From the Q1 spec.
      nums[nums[pc + 1]] = 5; // From the Q2 spec.
      pc += 2;
      continue;
    }
    if (opc == 4) {
      cout << nums[nums[pc + 1]] << endl;
      nums[nums[pc + 1]] = 0;
      pc += 2;
      continue;
    }

    // Parameters that an instruction writes to will never be in immediate mode,
    // so actually we only need to worry about 2 digits, but, whatever.
    auto m = parseModes(opc);
    int lv = nums[pc + 1];
    int l = m[0] == 0 ? nums[lv] : lv;
    int rv = nums[pc + 2];
    int r = m[1] == 0 ? nums[rv] : rv;

    if (opc % 10 == 1) {
      nums[nums[pc + 3]] = l + r;
      pc += 4;
    } else if (opc % 10 == 2) {
      nums[nums[pc + 3]] = l * r;
      pc += 4;
    } else if (opc % 10 == 5) {
      if (l) pc = r;
      else pc += 3;
    } else if (opc % 10 == 6) {
      if (!l) pc = r;
      else pc += 3;
    } else if (opc % 10 == 7) {
      nums[nums[pc + 3]] = l < r;
      pc += 4;
    } else if (opc % 10 == 8) {
      nums[nums[pc + 3]] = l == r;
      pc += 4;
    } else {
      cout << "?" << opc << endl;
    }
  }
}
