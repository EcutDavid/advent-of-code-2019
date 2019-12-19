#include <bits/stdc++.h>
using namespace std;
typedef int i32;
typedef long long i64;
vector<i32> patternBase = {0, 1, 0, -1};
vector<i32> genPattern(i32 round, i32 len) {
  vector<i32> ret;
  i32 pointer = 0;
  while (ret.size() != (len + 1)) {
    ret.push_back(patternBase[pointer / (round + 1) % patternBase.size()]);
    pointer++;
  }
  reverse(ret.begin(), ret.end());
  ret.pop_back();
  reverse(ret.begin(), ret.end());
  return ret;
}
i32 getPattern(i32 round, i32 len, i32 pos) {
  i32 pointer = pos + 1;
  return patternBase[pointer / (round + 1) % patternBase.size()];
}
int main() {
  // string input = "59758034323742284979562302567188059299994912382665665642838883745982029056376663436508823581366924333715600017551568562558429576180672045533950505975691099771937719816036746551442321193912312169741318691856211013074397344457854784758130321667776862471401531789634126843370279186945621597012426944937230330233464053506510141241904155782847336539673866875764558260690223994721394144728780319578298145328345914839568238002359693873874318334948461885586664697152894541318898569630928429305464745641599948619110150923544454316910363268172732923554361048379061622935009089396894630658539536284162963303290768551107950942989042863293547237058600513191659935";
  string input = "03036732577212944063491565474664";
  cout << input.size() << endl;
  vector<i32> nums;
  for (char d : input) {
    nums.push_back(d - '0');
  }
  for (i32 i = 0; i < 1e4; i++) {
    for (i32 j = 0; j < (1e4 - 1); j++) {
      nums.push_back(nums[j]);
    }
  }
  for (i32 i = 0; i < 100; i++) {
    cout << "Round: " << i << endl;
    vector<i32> tmp(nums.size());
    for (i32 j = 0; j < nums.size(); j++) {
      i32 sum = 0;
      for (i32 k = 0; k < nums.size(); k++) {
        i32 pattern = getPattern(j, nums.size(), k);
        sum += nums[k] * pattern;
      }
      tmp[j] = abs(sum) % 10;
    }
    for (i32 j = 0; j < tmp.size(); j++) {
      nums[j] = tmp[j];
    }
    // for (i32 j = 0; j < 8; j++) {
    //   cout << nums[j];
    // }
    // cout << "*" << endl;
  }
  for (i32 j = 303673; j < (303673 + 8); j++) {
    cout << nums[j];
  }
  cout << endl;
  for (i32 j = 59758034; j < (59758034 + 8); j++) {
    cout << nums[j];
  }
  cout << endl;
}
