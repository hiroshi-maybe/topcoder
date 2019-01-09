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

// 10/12/2016 SRM 700 00:00-00:07 accepted
// improved by https://arena.topcoder.com/#/u/viewCode/16821/53652/2/329343/hydra.icpc4/details

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

class Xylophone {
public:
  int countKeys(vector<int> const &keys) {
    set<int> notes;
    FORR(k, keys) {
      notes.insert(k%7);
    }

    return SZ(notes);
  }
};
