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

// type alias
typedef unsigned long ul;
typedef long long ll;
typedef pair< int , int > pii;
typedef vector< int > vi;
typedef vector<pii> vpii;
const int INF = 1e9;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define FORR(x,arr) for(auto& x:arr)

// container util
#define SZ(a) int((a).size())
#define PUSH(s, e) (s).push_back(e)
#define REVERSE(c) reverse((c).begin(),(c).end())
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define SORT(c) sort((c).begin(),(c).end())
#define PB(s, e) sort((c).begin(),(c).end())
#define DEFAULT(s,e,x) if (!EXIST(s, e)) { s[e]=x; }
#define ITER(i,s) for(auto i=s.begin(); i!=s.end(); i++)

// pair
#define MP make_pair
#define FI first 
#define SE second

// binary search
#define LB(a,n,k) lower_bound(a,a+(n),(k))
#define UB(a,n,k) upper_bound(a,a+(n),(k))

// debug
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dumpAR(ar,n) REP(i,(n)) { cerr << ar[i] << ','; } cerr << endl;

// dp
#define DP(dp,i,j) int dp[i][j]
#define FILL(dp,x) memset(dp, x, sizeof(dp))
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
