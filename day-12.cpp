#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef int i32;

#define PRINT(x) cout << #x ": " << (x) << endl;

void simulateStep(vector<i32>& pos, vector<i32>& vel) {
  for (i32 i = 0; i < pos.size(); i++) {
    for (i32 j = 0; j < pos.size(); j++) {
      if (i == j) continue;
      if (pos[j] > pos[i]) vel[i]++;
      if (pos[j] < pos[i]) vel[i]--;
    }
  }
  for (i32 i = 0; i < pos.size(); i++) {
    pos[i] += vel[i];
  }
}

i64 gcd(i64 a, i64 b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

i32 main() {
  vector<i32> px = {3, 4, -10, -3};
  vector<i32> py = {3, -16, -6, 0};
  vector<i32> pz = {0, 2, 5, -13};
  vector<i32> vx(4, 0);
  vector<i32> vy(4, 0);
  vector<i32> vz(4, 0);
  unordered_set<string> hm;

  // Q1
  for (i32 i = 0; i < 1e3; i++) {
    simulateStep(px, vx);
    simulateStep(py, vy);
    simulateStep(pz, vz);
  }

  i64 ret = 0;
  for (i32 i = 0; i < 4; i++) {
    i64 p =
        abs(px[i]) + abs(py[i]) + abs(pz[i]);
    i64 k =
        abs(vx[i]) + abs(vy[i]) + abs(vz[i]);
    ret += p * k;
  }
  PRINT(ret);

  // Q2
  // Observed that
  // X loop every 22958 steps
  // Y loop every 286332 steps
  // Z loop every 231614 steps
  ret = i64(22958) * 286332 / gcd(22958, 286332);
  ret = ret * 231614 / gcd(ret, 231614);

  PRINT(ret);
}
