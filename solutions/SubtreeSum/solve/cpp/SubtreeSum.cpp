#include <vector>
#include <string>
#include <math.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n) FOR(i,0,n)
#define FORR(x,arr) for(auto& x:arr)

#define ZERO(dp) memset(dp, 0, sizeof(dp))
typedef signed long long ll;

class SubtreeSum {
public:
  int getSum(vector<int> const &p,
             vector<int> const &x) {

    ll mo=1000000007;
    int i,j;
    int N=x.size();
    // v -> [v]
    vector<int> E[51];
    REP(i,N-1) E[p[i]].push_back(i+1);

    ll tot=0;
    REP(i,30) { // 30 comes from 32 bit??
      ll ret=0;
      ll num[2][50]={};

      for(j=N-1;j>=0;j--) {
	// i-th bit for node j?
	num[(x[j]>>i)&1][j]=1;
	FORR(r, E[j]) {
	  // r = children
	  // num[0/1][r] is determined
	  ll a0=num[0][j],a1=num[1][j];
	  num[0][j] = a0 * (1+num[0][r]);
	  num[1][j] = a1 * (1+num[0][r] + num[1][r]) + a0 * num[1][r];
	}
	ret += num[1][j];
      }

      tot += ((ret%mo)<<i)%mo;
    }
    return tot % mo;
  }

};
