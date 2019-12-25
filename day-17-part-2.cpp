#include <bits/stdc++.h>
using namespace std;
typedef int i32;
typedef long long i64;
typedef pair<i32, i32> Point;
#define all(c) (c).begin(), (c).end()
#define REP(i, a, b) for (auto i = a; i < b; i++)
#define PRINT(x) cout << #x ": " << (x) << endl;

vector<vector<i32>> dirs = {
    {0, -1},
    {1, 0},
    {0, 1},
    {-1, 0},
};

i32 main() {
  vector<string> board;
  string line;
  while(cin >> line) {
    if (line.size() == 0) break;
    board.push_back(line);
  }

  i32 ret = 0;
  i32 h = board.size(), w = board[0].size();
  for (i32 i = 1; i < (h - 1); i++) {
    for (i32 j = 1; j < (w - 1); j++) {
      if (board[i][j] != '#') continue;
      i32 count  = 0;
      for (auto d : dirs) {
        count += board[i + d[0]][j + d[1]] == '#';
      }
      if (count == 4) {
        ret += i * j;
      }
    }
  }

  cout << ret << endl;
}
