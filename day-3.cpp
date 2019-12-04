#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef int i32;

i32 readNum(string& line, int& pc) {
  i32 num = 0;
  while (pc != line.size() && line[pc] != ',') {
    num = num * 10 + (line[pc++] - '0');
  }
  return num;
}

i32 main() {
  string l1, l2;
  cin >> l1 >> l2;
  unordered_map<char, pair<int, int>> dirMap = {
      {'L', {-1, 0}},
      {'R', {1, 0}},
      {'U', {0, 1}},
      {'D', {0, -1}},
  };

  i32 pc = 0;
  pair<int, int> pos = {0, 0};
  map<pair<int, int>, int> counterMap;
  i32 counter = 0;
  while (pc != l1.size()) {
    char dir = l1[pc++];
    i32 num = readNum(l1, pc);
    if (pc != l1.size()) pc++;

    while (num--) {
      counter++;
      pos = {pos.first + dirMap[dir].first, pos.second + dirMap[dir].second};
      counterMap[pos] = counter;
    }
  }

  pc = 0;
  pos = {0, 0};
  i32 bestComb = 1e9;
  counter = 0;

  while (pc != l2.size()) {
    char dir = l2[pc++];
    i32 num = readNum(l2, pc);
    if (pc != l2.size()) pc++;

    while (num--) {
      counter++;
      pos = {pos.first + dirMap[dir].first, pos.second + dirMap[dir].second};
      if (counterMap.count(pos)) {
        bestComb = min(bestComb, counterMap[pos] + counter);
      }
    }
  }

  cout << bestComb << endl;
}
