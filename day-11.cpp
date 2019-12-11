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

vector<vector<i32>> dirs = {
  { 0, -1 },
  { 1, 0 },
  { 0, 1 },
  { -1, 0 },
};

i32 main() {
  auto mem = parseProgram();
  mem.resize(1e5);  // The program needs extra memory.

  map<pair<i32, i32>, i32> panel;
  set<pair<i32, i32>> sQ;
  pair<i32, i32> location;
  panel[location] = 1;
  i32 xMin = 1e9;
  i32 xMax = -1e9;
  i32 yMin = 1e9;
  i32 yMax= -1e9;

  i64 pc = 0;
  i64 baseAddr = 0;
  bool colorFlag = true;
  i32 dir = 0;
  while (mem[pc] != 99) {
    i64 opc = mem[pc];
    vector<i64> m = parseModes(opc);
    i64 next = mem[pc + 1];
    if (opc % 10 == 3) {
      i64 pos = next + (m[0] == 2 ? baseAddr : 0);
      mem[pos] = panel.count(location) ? panel[location] : 0;
      pc += 2;
      continue;
    }

    if (opc % 10 == 4) {
      i64 output = readValue(mem, baseAddr, pc + 1, m[0]);
      cout << "Output: " << output << endl;
      if (colorFlag) {
        sQ.insert(location);
        panel[location] = output;
      } else {
        i32 diff = output == 1 ? 1 : -1;
        if (diff == -1 && dir == 0) dir = 3;
        else dir = (dir + diff) % 4;
        location = { location.first + dirs[dir][0], location.second + dirs[dir][1] };
        xMin = min(xMin, location.first);
        xMax = max(xMax, location.first);
        yMin = min(yMin, location.second);
        yMax = max(yMax, location.second);
      }
      colorFlag = !colorFlag;
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

  cout << panel.size() << endl;

  for (i32 i = yMin; i <= yMax; i++) {
    for (i32 j = xMin; j <= xMax; j++) {
      cout << (panel[{j, i}] ? "#" : ".");
    }
    cout << "\n";
  }
}
