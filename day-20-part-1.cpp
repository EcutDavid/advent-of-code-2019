#include <bits/stdc++.h>
using namespace std;
typedef int i32;
typedef long long i64;
typedef pair<i32, i32> Point;
#define all(c) (c).begin(), (c).end()
#define REP(i, a, b) for (auto i = a; i < b; i++)
#define PRINT(x) cout << #x ": " << (x) << endl;

map<Point, string> genPointPortalMap(vector<string>& m) {
  i32 w = m[0].size();
  i32 h = m.size();
  map<Point, string> ret;

  REP(i, 1, h - 1) {
    REP(j, 1, w - 1) {
      if (m[i][j] != '.') continue;
      REP(k, -1, 2) {
        REP(y, -1, 2) {
          if (abs(k) == abs(y)) continue;
          char c = m[i + k][j + y];
          if (c < 'A' || c > 'Z') continue;
          string word = string("") + c + m[i + k * 2][j + y * 2];
          if (k < 0 || y < 0) {
            word = string(1, word[1]) + word[0];
          }
          ret[{i, j}] = word;
        }
      }
    }
  }

  return ret;
}

map<string, vector<Point>> genPortalPointMap(vector<string>& m) {
  i32 w = m[0].size();
  i32 h = m.size();
  map<string, vector<Point>> ret;

  REP(i, 1, h - 1) {
    REP(j, 1, w - 1) {
      if (m[i][j] != '.') continue;
      REP(k, -1, 2) {
        REP(y, -1, 2) {
          if (abs(k) == abs(y)) continue;
          char c = m[i + k][j + y];
          if (c < 'A' || c > 'Z') continue;
          string word = string("") + c + m[i + k * 2][j + y * 2];
          if (k < 0 || y < 0) {
            word = string(1, word[1]) + word[0];
          }
          ret[word].push_back({i, j});
        }
      }
    }
  }

  return ret;
}

vector<Point> dirs = {
  {-1, 0},
  {1, 0},
  {0, -1},
  {0, 1}
};

i32 calcStepCount(map<Point, vector<Point>> & adj, Point start, Point end) {
  map<Point, i32> distance;
  distance[start] = 0;
  queue<Point> q;
  q.push(start);
  while(q.size()) {
    Point item = q.front();
    q.pop();
    if (item == end) return distance[item];

    for (auto d : adj[item]) {
      if (distance.count(d)) continue;
      q.push(d);
      distance[d] = distance[item] + 1;
    }
  }

  return -1;
}

i32 main() {
  vector<string> m;
  string line;
  while (getline(cin, line)) {
    m.push_back(line);
  }

  i32 w = m[0].size();
  i32 h = m.size();
  auto pointPortalMap = genPointPortalMap(m);
  auto portalPointMap = genPortalPointMap(m);

  auto AA = portalPointMap["AA"][0];
  auto ZZ = portalPointMap["ZZ"][0];

  map<Point, vector<Point>> adj;
  REP(i, 1, h - 1) {
    REP(j, 1, w - 1) {
      if (m[i][j] != '.') continue;

      for (auto dir : dirs) {
        if (m[i + dir.first][j + dir.second] != '.') continue;
        adj[{i, j}].push_back({i + dir.first, j + dir.second});
      }

      // Take portal into account.
      if (pointPortalMap.count({i, j})) {
        string target = pointPortalMap[{i, j}];
        if (portalPointMap[target].size() == 1) continue;  // Is the start and end
        i32 index = 0;
        if (portalPointMap[target][1] == Point(i, j)) {
          index = 1;
        }
        auto otherSide = portalPointMap[target][index ? 0 : 1];
        adj[{i, j}].push_back(otherSide);
      }
    }
  }

  PRINT(calcStepCount(adj, AA, ZZ));
}
