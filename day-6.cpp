#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef int i32;
typedef unordered_map<string, unordered_set<string>> adjMap;

vector<string> split(string &l, char s) {
  vector<string> vs;

  string cur = "";
  for (int i = 0; i < l.size(); i++) {
    if (l[i] == s) {
      vs.push_back(cur);
      cur = "";
      continue;
    }
    cur += l[i];
  }
  vs.push_back(cur);

  return vs;
}

void walk(adjMap &adj, unordered_set<string> &visited, string node, int level, int &sum) {
  for (string n : adj[node]) {
    if (visited.count(n)) continue;
    sum += level;
    visited.insert(n);
    walk(adj, visited, n, level + 1, sum);
  }
}

i32 main() {
  i32 sum = 0;
  adjMap adj;
  unordered_set<string> visited;
  visited.insert("COM");

  string line;
  while (cin >> line) {
    auto parts = split(line, ')');
    for (auto p : parts) {
      if (!adj.count(p)) adj[p] = unordered_set<string>();
    }

    adj[parts[0]].insert(parts[1]);
    adj[parts[1]].insert(parts[0]);
  }

  // walk(adj, visited, "COM", 1, sum); // calc the orbit sum.
  // cout << sum << endl;

  unordered_map<string, i32> dist;
  dist["YOU"] = 0;
  queue<string> q;
  q.push("YOU");
  while(q.size()) {
    string item = q.front();
    q.pop();

    if (item == "SAN") break;

    for (auto d : adj[item]) {
      if (dist.count(d)) continue;
      dist[d] = dist[item] + 1;
      q.push(d);
    }
  }
  cout << dist["SAN"] - 2 << endl;
}
