/**
 * 
 * 10/23/2016
 * 
 * 15:51 start
 * 16:18 wrong for "110"
 * 16:23 wrong for "17"
 * 16:28 accepted
 */

typedef vector < int > VI;
typedef vector < vector < int > > VVI;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
#define REPS(i,arr)  for(int i=0; i<(arr).size(); ++i)

#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

class Solution {
public:
  int numDecodings(string s) {
    int L = SZ(s);
    if (L==0) return 0;
    VI dp(L+10, 0);

    dp[0] = 1<=(s[0]-'0') && (s[0]-'0')<=9 ? 1 : 0;

    FOR(i,0,L) {
      if(s[i]-'0'>=7 && (i==0 || (s[i-1]-'0'!=1))) {
	// 7, 27...
	dp[i+1] = dp[i];
	continue;
      }

      if (s[i]-'0'==0) {
	if (i==0 || (s[i-1]-'0'!=1) && (s[i-1]-'0'!=2)) return 0;
	dp[i+1] = dp[i-1];
	continue;
      }

      // s[i] = 1...6
      if (i==0 || (s[i-1]-'0'!=1) && (s[i-1]-'0'!=2)) {
	// 1..6, 36..
	dp[i+1] = dp[i];
      } else {
	// 11...26
	dp[i+1] = dp[i] + dp[i-1];
      }
    }
    //dumpAR(dp);
    return dp[L];
  }

  int numDecodingsV2(string s) {
    int L = SZ(s);
    if (L==0) return 0;

    VI dp(L, 0);

    dp[0] = 1<=(s[0]-'0') && (s[0]-'0')<=9 ? 1 : 0;

    FOR(i,1,L) {
      int n = (s[i-1]-'0')*10 + (s[i]-'0');
      if (n<1) {
	// "00"
	return 0;
      }
      if (n<10) {
	dp[i] = dp[i-1];
	continue;
      }
      if (n==10 || n==20) {
	dp[i] = i==1 ? 1 : dp[i-2];
	continue;
      }
      if (11<=n && n<=26) {
	dp[i] = dp[i-1] + (i==1 ? 1 : dp[i-2]);
	continue;
      }

      // 30,40...
      if (n % 10==0) return 0;

      if (27<=n) {
	dp[i] = dp[i-1];
      }
    }
    //dumpAR(dp);
    return dp[L-1];
  }
};
