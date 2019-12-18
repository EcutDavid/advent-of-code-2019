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

vector<vector<i32>> dirs = {
    {0, -1},
    {1, 0},
    {0, 1},
    {-1, 0},
};

i32 calcDistance(Point x, Point y) {
  return abs(x.first - y.first) + abs(x.second - y.second);
}

vector<Point> getRoute(map<Point, i32> &m, Point x, Point y) {
  set<Point> visited;
  visited.insert(x);
  queue<Point> q;
  map<Point, Point> parentM;
  q.push(x);
  bool foundRoute = false;

  while (q.size()) {
    auto item = q.front();
    if (item == y) {
      foundRoute = true;
      break;
    }
    q.pop();

    if (m[item] == 1) continue;  // The wall

    for (auto d : dirs) {
      Point newLoc = {item.first + d[0], item.second + d[1]};
      if (visited.count(newLoc) || (newLoc != y && m[newLoc] != 2)) continue;

      visited.insert(newLoc);
      q.push(newLoc);
      parentM[newLoc] = item;
    }
  }

  vector<Point> ret;
  if (!foundRoute) return ret;
  Point cur = y;
  while (cur != x) {
    cur = parentM[cur];
    ret.push_back(cur);
  }
  ret.pop_back();
  reverse(all(ret));

  return ret;
}

i32 parseDirCmd(Point x, Point y) {
  Point diff = {y.first - x.first, y.second - x.second};

  if (diff.first == 1 && diff.second == 0) return 4;
  if (diff.first == -1 && diff.second == 0) return 3;
  if (diff.first == 0 && diff.second == -1) return 1;

  return 2;
}

void printBoard(map<Point, i32> &boardMap, Point cur) {
  i32 xMin = 1e9;
  i32 xMax = -1e9;
  i32 yMin = 1e9;
  i32 yMax = -1e9;

  for (auto p : boardMap) {
    xMin = min(xMin, p.first.first);
    xMax = max(xMax, p.first.first);
    yMin = min(yMin, p.first.second);
    yMax = max(yMax, p.first.second);
  }

  for (i32 i = yMin; i <= yMax; i++) {
    for (i32 j = xMin; j <= xMax; j++) {
      Point pos = {j, i};
      if (pos == cur)
        cout << "!";
      else if (boardMap[pos] == 0)
        cout << "?";
      else if (boardMap[pos] == 1)
        cout << "*";
      else if (boardMap[pos] == 2)
        cout << ".";
    }
    cout << "\n";
  }
}

i32 main() {
  auto mem = parseProgram();
  mem.resize(1e5);  // The program needs extra memory.

  i64 pc = 0;
  i64 baseAddr = 0;

  map<Point, i32> boardMap;
  deque<Point> q;
  Point pos = {0, 0};
  boardMap[pos] = 2;
  Point targetPos;
  Point oxgPos;
  q.push_front({-1, 0});
  q.push_front({1, 0});
  q.push_front({0, -1});
  q.push_front({0, 1});
  set<Point> visited = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  auto r = getRoute(boardMap, {0, 1}, {3, 2});

  while (mem[pc] != 99) {
    i64 opc = mem[pc];
    vector<i64> m = parseModes(opc);
    i64 next = mem[pc + 1];
    if (opc % 10 == 3) {
      i64 addr = next + (m[0] == 2 ? baseAddr : 0);
      while (q.front() == pos || calcDistance(pos, q.front()) > 1) {
        if (q.size() == 0) break;
        if (q.front() == pos) {
          q.pop_front();
          continue;
        }
        auto r = getRoute(boardMap, pos, q.front());
        if (r.size() == 0) {
          q.pop_front();
          continue;
        }
        reverse(all(r));
        for (auto d : r) {
          q.push_front(d);
        }
        break;
      }
      if (q.size() == 0) break;
      auto goal = q.front();
      q.pop_front();
      mem[addr] = parseDirCmd(pos, goal);
      targetPos = goal;

      pc += 2;
      continue;
    }

    if (opc % 10 == 4) {
      i64 output = readValue(mem, baseAddr, pc + 1, m[0]);
      // Testing a move
      if (output == 0) {
        boardMap[targetPos] = 1;
      } else if (output == 2) {
        boardMap[targetPos] = 3;
        oxgPos = targetPos;
        pos = targetPos; // missed this line cost me a lot of time
        printBoard(boardMap, oxgPos);
      } else {
        boardMap[targetPos] = 2;
        pos = targetPos;

        for (auto d : dirs) {
          Point newLoc = {pos.first + d[0], pos.second + d[1]};
          if (visited.count(newLoc)) continue;
          visited.insert(newLoc);
          q.push_back(newLoc);
        }
      }

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

  // Q1
  // pos = { 0, 0 };
  // cout << oxgPos.first << " " << oxgPos.second << endl;
  // auto route = getRoute(boardMap, pos, oxgPos);
  // for (auto d : route) {
  //   cout << d.first << " " << d.second << endl;
  // }
  // PRINT(route.size() + 1);

  // i32 xMin = 1e9;
  // i32 xMax = -1e9;
  // i32 yMin = 1e9;
  // i32 yMax = -1e9;

  // for (auto p : boardMap) {
  //   xMin = min(xMin, p.first.first);
  //   xMax = max(xMax, p.first.first);
  //   yMin = min(yMin, p.first.second);
  //   yMax = max(yMax, p.first.second);
  // };

  // printBoard(boardMap, oxgPos);

  // i32 ret = 0;
  // for (i32 i = yMin; i <= yMax; i++) {
  //   for (i32 j = xMin; j<= xMax; j++) {
  //     Point target = { j, i };
  //     if (target == oxgPos || boardMap[target] != 2) continue;
  //     ret = max(ret, i32(getRoute(boardMap, oxgPos, target).size() + 1));
  //   }
  // }

  // cout << ret << endl;
}
