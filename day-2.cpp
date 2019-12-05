#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef int i32;

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

  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      nums = origin;
      nums[1] = i;
      nums[2] = j;
      i32 pc = 0;
      while (nums[pc] != 99) {
        if (nums[pc] == 1) {
          nums[nums[pc + 3]] = nums[nums[pc + 1]] + nums[nums[pc + 2]];
        } else {
          nums[nums[pc + 3]] = nums[nums[pc + 1]] * nums[nums[pc + 2]];
        }
        pc += 4;
      }
      if (nums[0] == 19690720) {
        cout << nums[1] * 100 + nums[2] << endl;
        return 0;
      }
    }
  }
}
