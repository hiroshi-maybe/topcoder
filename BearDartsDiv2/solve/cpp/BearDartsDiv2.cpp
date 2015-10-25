#include <vector>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

int64 dp[3][1000001];
typedef unsigned long ul;

class BearDartsDiv2 {
public:
    int64 count(vector<int> const &w) {
      int64 res = 0;

      REP(i,3) REP(j,1000001) dp[i][j]=0;

      REP(i,w.size()) {
	int val = w[i];

	res += dp[2][val];
	for(int p=1; p>=0; p--) {
	  REP(q,1000001) {
	    ul next = (ul)q*(ul)val;
	    if (next<1000001) dp[p+1][next]+=dp[p][q];
	  }
	}
	dp[0][val]++;
      }
      return res;
    }
};
