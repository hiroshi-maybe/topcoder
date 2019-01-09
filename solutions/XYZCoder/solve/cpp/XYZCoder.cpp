#include <iostream>
#include <algorithm> // max,min
#include <vector>
#include <string>
#include <sstream>
#include <map>
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

typedef long long ll;
// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define FORR(x,arr) for(auto& x:arr)

// dp
#define DP(dp,i,j) ll dp[i][j]
#define FILL(dp,x) memset(dp, x, sizeof(dp))

// debug 1
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dumpAR(ar,n) REP(i,(n)) { cerr << ar[i] << ','; } cerr << endl;

long mod = 1000000007;
DP(dp,10001,101);

class XYZCoder {
public:
  int countWays(int room,
                int size) {
    FILL(dp,0);

    int n = room * size;
    dp[0][0] = 1;
    FOR(i,1,n+1) {
      REP(j,room+1) {
	if (j>0 && i>=j*size) {
	  dp[i][j] = (dp[i-1][j] + dp[i-1][j-1]) % mod;
	} else {
	  dp[i][j] = dp[i-1][j];
	}
      }
    }

    ll ans = dp[n][room];
    FOR(i,1,room+1) {
      ans = (ans * i) % mod;
    }

    return (int)ans;
  }
};
