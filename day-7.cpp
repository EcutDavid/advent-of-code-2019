#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef int i32;

vector<int> parseModes(int opc) {
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
  auto origin = nums;

  i32 pc;
  vector<i32> seq = {0, 1, 2, 3, 4};
  i64 best = -1e9;
  do {
    i32 pointer = 0;
    i64 output = 0;
     nums = origin;
    for (int l = 0; l < 5; l++) {
      pc = 0;
      while (nums[pc] != 99) {
        int opc = nums[pc];

        if (opc == 3) {
          cout << "in" << endl;
          nums[nums[pc + 1]] = pointer % 2 == 0 ? seq[pointer / 2] : output;
          pointer++;
          pc += 2;
          continue;
        }
        if (opc == 4) {
          cout << "out" << endl;
          // cout << nums[nums[pc + 1]] << endl;
          output = nums[nums[pc + 1]];
          pc += 2;
          if (pointer == 10) {
            cout << output << endl;
            best = max(best, output);
          }
          continue;
        }

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
          if (l)
            pc = r;
          else
            pc += 3;
        } else if (opc % 10 == 6) {
          if (!l)
            pc = r;
          else
            pc += 3;
        } else if (opc % 10 == 7) {
          nums[nums[pc + 3]] = l < r;
          pc += 4;
        } else if (opc % 10 == 8) {
          nums[nums[pc + 3]] = l == r;
          pc += 4;
        } else {
          cout << "?" << opc << endl;
          return 1;
        }
      }
    }
  } while (next_permutation(seq.begin(), seq.end()));

  cout << best << endl;
}
