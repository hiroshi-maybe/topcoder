#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
using namespace std;

#define FOR(i,a,b) for(int64 i=(a);i>(b);--i)
#define REP(i,n)  FOR(i,n,0)

class BearPaints {
public:
    int64 maxArea(int64 W,
                  int64 H,
                  int64 M) {
      int64 res = 0;

      if (W*H<=M) return W*H;
      
      REP(i,W) {
	int64 j = (int64)floor(M/i);
	int64 x = i*j;
	if (x>res && j<=H) {
	  res = x;
	}
      }      
      return res;
    }
};
