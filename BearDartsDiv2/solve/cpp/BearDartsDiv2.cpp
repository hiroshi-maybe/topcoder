#include <vector>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

class BearDartsDiv2 {
public:
    int64 count(vector<int> const &w) {
      int64 res = 0; 
      REP(ai,w.size()) {
	int64 a = w[ai];
	FOR(bi,ai+1,w.size()) {
	  int64 ab = a * w[bi];
	  FOR(ci,bi+1,w.size()) {
	    int64 abc = ab * w[ci];
	    FOR(di,ci+1,w.size()) {
	      if (w[di]==abc) ++res;
	    }
	  }
	}
      }
      return res;
    }
};
