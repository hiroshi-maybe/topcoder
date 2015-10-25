#include <vector>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i>=(b);--i)
#define REP(i,n)  FOR(i,n,0)

class BearDartsDiv2 {
public:
    int64 count(vector<int> const &w) {
      int64 res = 0; 
      REP(di,w.size()-1) {
	int64 d = w[di];
	REP(ci,di-1) {
	  if (w[ci] > d || d % w[ci] != 0) continue;
	  int64 ab = (int64)(d / w[ci]);
	  REP(bi,ci-1) {
	    if (w[bi] > ab || ab % w[bi] != 0) continue;
	    int64 a = (int64)(ab / w[bi]);
	    REP(ai,bi-1) {
	      if (w[ai]==a) ++res;
	    }
	  }
	}
      }
      return res;
    }
};
