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
#define SZ(a) int((a).size())

class XMarksTheSpot {
public:
  int countArea(vector<string> const &board) {
    vector<int> wrs;
    vector<int> wcs;

    int cl = 60;
    int cu = -1;
    int rl = 60;
    int ru = -1;
    REP(r,board.size()) {
      REP(c,board[r].size()) {
	if (board[r][c]=='?') {
	  wrs.push_back(r);
	  wcs.push_back(c);
	}
	if (board[r][c]=='O') {
	  cl = min(cl, c);
	  rl = min(rl, r);
	  cu = max(cu, c);
	  ru = max(ru, r);
	}
      }
    }

    ull bset = 0;
    int ans = 0;
    int wcount = wrs.size();
    int bsetmax = (1 << wcount) - 1;
    while (bset <= bsetmax) {
      int cl2 = cl;
      int cu2 = cu;
      int rl2 = rl;
      int ru2 = ru;
      REP(bi, wcount) {
	if ((bset >> bi) & 1) {
	  cl2 = min(cl2, wcs[bi]);
	  rl2 = min(rl2, wrs[bi]);
	  cu2 = max(cu2, wcs[bi]);
	  ru2 = max(ru2, wrs[bi]);
	}
      }

      ans += (ru2 - rl2 + 1) * (cu2 - cl2 + 1);

      bset++;
    }

    return ans;
  }
};
