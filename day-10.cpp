#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef int i32;

i32 checkTotal(vector<vector<bool> >& space, i32 x, i32 y, bool solveQ2 = false) {
  i32 w = space[0].size();
  i32 h = space.size();
  i32 ret = 0;
  map<i64, i64> rMap;
  map<i64, i64> lMap;
  map<i64, i64> o;
  for (i32 i = 0; i < h; i++) {
    for (i32 j = 0; j < w; j++) {
      if (j == x && i == y) continue;
      if (!space[i][j]) continue;

      i64 d = 1e15 * (y > i ? -1 : 1);
      if (j != x)
        d = (i - y) * 1e9 / (j - x);

      map<i64, i64>* s = &rMap;
      if (j < x) s = &lMap;
      i64 weight = pow((j - x), 2) + pow((i - y), 2);
      if (s->count(d) && ((*s)[d] < weight)) continue;
      ret -= s->count(d);
      (*s)[d] = weight;

      if (j < x) {
        o.erase(d);
        o[d] = j * 100 + i;
      }
      ret++;
    }
  }

  if (solveQ2) {
    auto oI = o.begin();
    for (i32 i = 0; i < 199 - rMap.size(); i++) {
      oI++;
    }
    cout << "Q2: " << oI->second << endl;
  }

  return ret;
}
i32 main() {
  string l;
  vector<vector<bool> > space;
  while (cin >> l) {
    vector<bool> line;
    for (auto c : l) {
      line.push_back(c == '#');
    }
    space.push_back(line);
  }

  i32 w = space[0].size();
  i32 h = space.size();
  i32 best = 0;
  i32 bestI = -1;
  i32 bestJ = -1;
  for (i32 i = 0; i < h; i++) {
    for (i32 j = 0; j < w; j++) {
      if (!space[i][j]) continue;
      i32 t = checkTotal(space, j, i);
      if (t > best) {
        bestI = i;
        bestJ = j;
        best = t;
      }
    }
  }
  cout << "Q1: " << best << endl;

  checkTotal(space, bestJ, bestI, true);
}
