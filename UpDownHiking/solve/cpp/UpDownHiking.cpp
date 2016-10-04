#include <vector>
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

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define FORR(x,arr) for(auto& x:arr)

class UpDownHiking {
public:
  int maxHeight(int N,
                int A,
                int B) {
    int mh = 0;
    REP(i, N) {
      int ud = i;
      int dd = N-i;

      mh = max(mh, min(ud * A, dd * B));
    }

    return mh;
  }
};
