#include <bits/stdc++.h>
using namespace std;
typedef int i32;
typedef long long i64;
typedef pair<i32, i32> Point;
#define all(c) (c).begin(), (c).end()
#define REP(i, a, b) for (auto i = a; i < b; i++)
#define PRINT(x) cout << #x ": " << (x) << endl;

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
  if (mode == 0)
    return mem[offset];
  return mem[baseAddr + offset];
}

i64 readValue(vector<i64> &mem, i64 baseAddr, i64 addr, i64 mode) {
  i64 directValue = mem[addr];
  if (mode == 1)
    return directValue;

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

i32 run(i32 x, i32 y, vector<i64> mem) {
  i64 pc = 0;
  i64 baseAddr = 0;
  bool feedX = true;

  while (mem[pc] != 99) {
    i64 opc = mem[pc];
    vector<i64> m = parseModes(opc);
    i64 next = mem[pc + 1];
    if (opc % 10 == 3) {
      i64 addr = next + (m[0] == 2 ? baseAddr : 0);
      mem[addr] = feedX ? x : y;
      feedX = !feedX;

      pc += 2;
      continue;
    }

    if (opc % 10 == 4) {
      i64 output = readValue(mem, baseAddr, pc + 1, m[0]);
      return output;
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
  return -1;
}

void printBoard(vector<vector<i32>> &board) {
  i32 xMin = 0;
  i32 xMax = board[0].size();
  i32 yMin = 0;
  i32 yMax = board.size();

  for (i32 i = yMin; i < yMax; i++) {
    for (i32 j = xMin; j < xMax; j++) {
      cout << (board[i][j] ? '#' : '.');
    }
    cout << "\n";
  }
}

i32 main() {
  auto mem = parseProgram();
  mem.resize(1e5);  // The program needs extra memory.

  i32 rowCount = 5000;
  vector<pair<i32, i32>> board(rowCount);
  board[0] = {0, 0};
  vector<i32> rMove;
  vector<i32> lMove;
  for (i32 i = 0; i < 30; i++) {
    lMove.push_back(i);
    rMove.push_back(i);
  }
  i32 maxL = 0;
  i32 maxR = 0;

  for (i32 i = 1; i < rowCount; i++) {
    i32 prevL = board[i - 1].first, prevR = board[i - 1].second;
    i32 newL = 0;
    i32 newR = 0;

    for (i32 diff : lMove) {
      if (run(prevL + diff, i, mem)) {
        maxL = max(maxL, diff);
        newL = prevL + diff;
        break;
      }
    }

    for (i32 j = 0; j < rMove.size(); j++) {
      i32 diff = rMove[rMove.size() - 1 - j];
      if (run(prevR + diff, i, mem)) {
        maxR = max(maxR, diff);
        newR = prevR + diff;
        break;
      }
    }

    board[i] = { newL, newR };
  }

  PRINT(maxL);
  PRINT(maxR);

  i32 best = 1e9;

  for (i32 i = 0; i < rowCount; i++) {
    for (i32 j = board[i].first; j <= board[i].second - 100; j++) {
      i32 rel = i + 100;
      if ((board[rel].first <= j) && (board[rel].second >= (j + 100))) {
        best = min(best, i + j * 10000);
        PRINT(best);
        // return 0;
      }
    }
  }
}
