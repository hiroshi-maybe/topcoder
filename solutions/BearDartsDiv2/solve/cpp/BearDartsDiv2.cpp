#include <vector>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

int64 dp[1000001];
typedef unsigned long ul;

class BearDartsDiv2 {
public:
    int64 count(vector<int> const &w) {
      int64 res = 0;

      REP(i,1000001) dp[i]=0;

      REP(c,w.size()) {
	FOR(d,c+1,w.size()) if (w[d]%w[c]==0) res+=dp[w[d]/w[c]];
	int b = c;
	REP(a,b) if ((ul)w[a]*(ul)w[b]<1000001) dp[w[a]*w[b]]++;
      }
      return res;
    }
};
