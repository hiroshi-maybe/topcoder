#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <utility>
#include <set>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define FORR(x,arr) for(auto& x:arr)

class Xylophone {
public:
  int countKeys(vector<int> const &keys) {
    vector<int> notes(7, 0);
    REP(i, keys.size()) {
      int k = keys[i];
      notes[note(k)] = 1;
    }

    int sum = 0;
    REP(i, notes.size()) {
      int n = notes[i];
      if (n) { sum += 1; }
    }

    return sum;
  }

  int note(int key) {
    return key % 7;
  }
};
