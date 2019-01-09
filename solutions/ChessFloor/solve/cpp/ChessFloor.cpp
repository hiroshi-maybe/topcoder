#include <vector>
#include <string>
#include <map>
#include <math.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

bool myfunction (pair<char, int> i,pair<char, int> j) { return (i.second < j.second); }

class ChessFloor {
public:
   /**
     56 cases checked, 0 failures, 0 errors
             Total time taken: 228 ms
           Average time taken: 4 ms
         Slowest running case: 10 ms (case 29)
     56 cases checked, 0 failures, 0 errors
             Total time taken: 539 ms
           Average time taken: 9 ms
         Slowest running case: 19 ms (case 14)
     */
    int minimumChanges(vector<string> const &floor) {
      int minCount = 401;
      for(char c1='a'; c1<='z'; c1++) {
	for(char c2='a'; c2<='z'; c2++) {
	  if (c1==c2) continue;
	  int changeCount = 0;
	  REP(i,floor.size()) {
	    REP(j,floor[i].size()) {
	      char curChar = floor[i][j];
	      if ((!(i % 2) && !(j % 2)) || ((i % 2) && (j % 2))) {
		if (curChar != c1) changeCount++;
	      } else {
		if (curChar != c2) changeCount++;
	      }
	    }
	  }
	  minCount = min(minCount, changeCount);
	}
      }

      return minCount;
    }
};
