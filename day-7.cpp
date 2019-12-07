#include <bits/stdc++.h>
using namespace std;

typedef int i32;

vector<i32> parseModes(i32 opc) {
  vector<i32> modes;
  opc /= 100;
  for (i32 i = 0; i < 3; i++) {
    modes.push_back(opc % 10);
    opc /= 10;
  }
  return modes;
}

i32 prevAmp(i32 cur) {
  if (cur == 0) return 4;
  return cur - 1;
}

void runCalc(int *mem, i32& pc) {
  i32 opc = mem[pc];
  auto m = parseModes(opc);
  i32 lv = mem[pc + 1];
  i32 l = m[0] == 0 ? mem[lv] : lv;
  i32 rv = mem[pc + 2];
  i32 r = m[1] == 0 ? mem[rv] : rv;

  if (opc % 10 == 1) {
    mem[mem[pc + 3]] = l + r;
    pc += 4;
  } else if (opc % 10 == 2) {
    mem[mem[pc + 3]] = l * r;
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
    mem[mem[pc + 3]] = l < r;
    pc += 4;
  } else if (opc % 10 == 8) {
    mem[mem[pc + 3]] = l == r;
    pc += 4;
  } else {
    cout << "?" << opc << endl;
  }
}

i32 main() {
  char c;
  i32 num;
  vector<i32> mem;
  while (cin >> c) {
    if (c == ',') {
      mem.push_back(num);
      num = 0;
      continue;
    }
    num = num * 10 + (c - '0');
  }
  mem.push_back(num);
  auto origin = mem;

  vector<i32> seq;
  for (i32 i = 5; i < 10; i++) {
    seq.push_back(i);
  }

  i32 best = -1e9;
  do {
    i32 pointer = 0;
    i32 rounds = 0;

    vector<vector<i32>> memArr;
    vector<i32> pcArr;
    i32 output = 0;
    i32 eOutput = 0;
    for (i32 i = 0; i < 5; i++) {
      memArr.push_back(origin);
      pcArr.push_back(0);
    }

    while (memArr[4][pcArr[4]] != 99) {
      i32 i = rounds % 5;
      auto mem = &memArr[i][0];
      i32 pc = pcArr[i];

      while (mem[pc] != 99) {
        i32 opc = mem[pc];

        if (opc == 3) {
          if (pointer < 10) {
            mem[mem[pc + 1]] = pointer % 2 == 0 ? seq[pointer / 2] : output;
          } else {
            mem[mem[pc + 1]] = output;
          }
          pointer++;
          pc += 2;
          continue;
        }
        if (opc == 4) {
          output = mem[mem[pc + 1]];
          pc += 2;
          if (i == 4) {
            eOutput = output;
          }
          rounds++;
          break;
        }
        runCalc(mem, pc);
      }
      best = max(best, eOutput);
      pcArr[i] = pc;
    }
  } while (next_permutation(seq.begin(), seq.end()));

  cout << best << endl;
}
