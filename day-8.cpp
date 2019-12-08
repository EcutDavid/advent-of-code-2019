#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef int i32;

// Q1
// i32 main() {
//   string img;
//   cin >> img;
//   i32 w = 25, h = 6;
//   i32 l = w * h;
//   vector<i32> c0, c1, c2;

//   for (i32 i = 0; i < img.size(); i++) {
//     i32 key = i / l;
//     if (c0.size() < (key + 1)) {
//       c0.push_back(0);
//       c1.push_back(0);
//       c2.push_back(0);
//     }
//     c0[key] += img[i] == '0';
//     c1[key] += img[i] == '1';
//     c2[key] += img[i] == '2';
//   }

//   i32 index = 0;
//   i32 best = 1e9;
//   for (i32 i = 0; i < c0.size(); i++) {
//     if (c0[i] < best) {
//       best = c0[i];
//       index = i;
//     }
//   }

//   cout << c1[index] * c2[index] << endl;
// }

i32 main() {
  string img;
  cin >> img;
  i32 w = 25, h = 6;
  i32 l = w * h;
  vector<vector<i32>> layers;

  for (i32 i = 0; i < img.size(); i++) {
    i32 key = i / l;
    if (layers.size() < (key + 1)) {
      layers.push_back({});
    }
    layers[key].push_back(img[i]);
  }

  vector<char> ret;
  for (i32 i = 0; i < l; i++) {
    ret.push_back(2);
    for (i32 j = 0; j < layers.size(); j++) {
      if (layers[j][i] != '2') {
        ret[i] = layers[j][i];
        break;
      }
    }
  }

  for (i32 i = 0; i < l; i++) {
    if (i % w == 0) cout << '\n';
    cout << ret[i];
  }
}
