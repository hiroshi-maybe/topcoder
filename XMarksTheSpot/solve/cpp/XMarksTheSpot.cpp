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

// 10/12/2016 SRM 700 00:07-00:57 accepted
// improved by https://arena.topcoder.com/#/u/viewCode/16821/53653/2/329343/hydra.icpc4/details

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair< int , int > pii;
typedef vector< int > vi;
typedef vector<pii> vpii;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
#define PB(s, e) (s).push_back(e)

// pair
#define MP make_pair
#define FI first 
#define SE second

class XMarksTheSpot {
public:
  int countArea(vector<string> const &board) {
    vpii ws;

    int cl = 60;
    int cu = -1;
    int rl = 60;
    int ru = -1;
    REP(r,SZ(board)) {
      REP(c,SZ(board[r])) {
	if (board[r][c]=='?') {
	  PB(ws, MP(r,c));
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
    int wcount = SZ(ws);
    REP(mask, 1 << wcount) {
      int cl2 = cl;
      int cu2 = cu;
      int rl2 = rl;
      int ru2 = ru;
      REP(bi, wcount) {
	if (mask & (1<<bi)) {
	  cl2 = min(cl2, ws[bi].SE);
	  rl2 = min(rl2, ws[bi].FI);
	  cu2 = max(cu2, ws[bi].SE);
	  ru2 = max(ru2, ws[bi].FI);
	}
      }

      ans += (ru2 - rl2 + 1) * (cu2 - cl2 + 1);
    }

    return ans;
  }
};
