#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

int dp[51][51];

class RepeatStringEasy {
public:
  int maximalLength(string const &s) {
    int maxL = 0;
    int size = s.size();
    REP(i, size-1) {
      maxL = max(maxL, lcs(s.substr(0, i+1), s.substr(i+1, size-i-1)));
    }
    return maxL * 2;
  }

  int lcs(string const &s1, string const &s2) {
    memset(dp, 0, sizeof(dp));

    REP(i, s1.size()) {
      REP(j, s2.size()) {
	if (s1[i]==s2[j]) {
	  dp[i+1][j+1] = max(dp[i][j]+1, max(dp[i][j+1], dp[i+1][j]));
	} else {
	  dp[i+1][j+1] = max(dp[i][j+1], dp[i+1][j]);
	}
      }
    }

    return dp[s1.size()][s2.size()];
  }
};
