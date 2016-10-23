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
typedef unsigned long UL;
typedef long long LL;
typedef vector < int > VI;
typedef vector < vector < int > > VVI;
const int INF = 1e9;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
#define REPS(i,arr)  for(int i=0; i<(arr).size(); ++i)

// vector
#define PUSH(s, e) (s).push_back(e)
#define POP(s) (s).pop_back()
#define REVERSE(c) reverse((c).begin(),(c).end())
#define SORT(c) sort((c).begin(),(c).end())
#define CONCAT(a,b) (a).insert((a).begin(), (b).begin(),(b).end())
#define ERASE(arr,i) (arr).erase((arr).begin()+i)

#define EXIST(s,e) ((s).find(e)!=(s).end())
#define DEFAULT(s,e,x) if (!EXIST(s, e)) { s[e]=x; }
#define ITER(i,s) for(auto i=s.begin(); i!=s.end(); i++)

// pair
typedef pair< int , int > PII;
typedef vector<PII> VPII;
#define MP make_pair
#define _1 first
#define _2 second

// priority queue
#define MAX_PQ(T) priority_queue<T>
#define MIN_PQ(T) priority_queue<T,vector<T>,greater<T>>

// binary search
#define LB(a,n,k) lower_bound(a,a+(n),(k))
#define UB(a,n,k) upper_bound(a,a+(n),(k))

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cerr << x << ','; } cerr << endl;
// debug cout
#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

// dp
#define DP(dp,i,j) int dp[i][j]
#define FILL(dp,x) memset(dp, x, sizeof(dp))
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
