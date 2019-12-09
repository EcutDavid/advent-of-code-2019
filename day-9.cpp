#include <bits/stdc++.h>
using namespace std;
typedef int i32;
typedef long long i64;

vector<i64> parseModes(i64 opc) {
  vector<i64> modes;
  opc /= 100;
  for (i64 i = 0; i < 3; i++) {
    modes.push_back(opc % 10);
    opc /= 10;
  }
  return modes;
}

i64 readMem(vector<i64> &mem, i64 baseAddr, i64 offset, i64 mode) {
  if (mode == 0) return mem[offset];
  return mem[baseAddr + offset];
}

i64 readValue(vector<i64> &mem, i64 baseAddr, i64 addr, i64 mode) {
  i64 directValue = mem[addr];
  if (mode == 1) return directValue;

  return readMem(mem, baseAddr, directValue, mode);
}

void runCalc(vector<i64> &mem, i64 &pc, i64 baseAddr) {
  i64 opc = mem[pc];
  auto m = parseModes(opc);
  i64 l = readValue(mem, baseAddr, pc + 1, m[0]);
  i64 r = readValue(mem, baseAddr, pc + 2, m[1]);
  i64 targetAddr = mem[pc + 3] + (m[2] == 2 ? baseAddr : 0);

  if (opc % 10 == 1) {
    mem[targetAddr] = l + r;
    pc += 4;
  } else if (opc % 10 == 2) {
    mem[targetAddr] = l * r;
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
    mem[targetAddr] = l < r;
    pc += 4;
  } else if (opc % 10 == 8) {
    mem[targetAddr] = l == r;
    pc += 4;
  } else {
    cerr << "Unexpected operation code" << opc << endl;
    exit(0);
  }
}

vector<i64> parseProgram() {
  char c;
  i64 num = 0;
  bool isNeg = false;
  vector<i64> mem;
  while (cin >> c) {
    if (c == ',') {
      mem.push_back(isNeg ? -num : num);
      num = 0;
      isNeg = false;
      continue;
    }
    if (c == '-') {
      isNeg = true;
      continue;
    }
    num = num * 10 + (c - '0');
  }
  mem.push_back(num);

  return mem;
}

i32 main() {
  auto mem = parseProgram();
  mem.resize(1e5);  // The program needs extra memory.

  i64 pc = 0;
  i64 baseAddr = 0;
  while (mem[pc] != 99) {
    i64 opc = mem[pc];
    vector<i64> m = parseModes(opc);
    i64 next = mem[pc + 1];
    if (opc % 10 == 3) {
      i64 pos = next + (m[0] == 2 ? baseAddr : 0);  // Maybe call it read addr.
      mem[pos] = 2;                                 // The value would be 1 at Q1.
      pc += 2;
      continue;
    }

    if (opc % 10 == 4) {
      i64 output = readValue(mem, baseAddr, pc + 1, m[0]);
      cout << "Output: " << output << endl;
      pc += 2;
      continue;
    }
    if (opc % 10 == 9) {
      baseAddr += m[0] == 1 ? next : readMem(mem, baseAddr, next, m[0]);
      pc += 2;
      continue;
    }
    runCalc(mem, pc, baseAddr);
  }
}
