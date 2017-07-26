#include <fstream> // for greed plugin
#include <iostream>
#include <algorithm> // max,min
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
using namespace std;

// type alias
typedef long long LL;

typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

/**
 
 8:53-9:02, 9:20-10:03 passed system test 👏
 
 Recursion relation of my solution:
 dp[mask|submask][c] += dp[mask][c-1], submask&mask==0 && popcount(submask)==SZ(G[i]==c)
  - insert chars in 'a'-'z' order in all the possible places by bitmask
  - avoid adjacent chars and duplicated strings by handling the same character at the same time
 
 22:28-23:10 read editorial
 - http://kmjp.hatenablog.jp/entry/2016/04/24/0930
 - http://suigingin.hatenablog.com/entry/2016/04/30/183731
  - insert chars from to right
  - avoid adjacent chars by remembering the last char
  - avoid counting duplicated string by using only leftmost char out of the same ones
   - current flowers: ***, G="**aaa***"
   - in this case, only the first `a` should be used to produce "***a"
   - do NOT create "***a" three times!!
 
 dp[mask|(1<<j)][j] += dp[mask][last] ... if G[last]!=G[j] && G[j]!=F[popcount(mask)] && G[j] is left most unused char
 
 23:10-23:30 add kmjp solution
 
 Other solutions
 - memoized DP
  - https://community.topcoder.com/stat?c=problem_solution&rm=328614&rd=16710&pm=14247&cr=40102659
  - https://community.topcoder.com/stat?c=problem_solution&rm=328618&rd=16710&pm=14247&cr=40179542
  - https://community.topcoder.com/stat?c=problem_solution&rm=328600&rd=16710&pm=14247&cr=23296935
 
 Summary
 - easy for div2 hard though, good job to solve by myself by counting up without violating constraint
 - basic strategy is brute-foce search. research how to reduce search space by keeping invariant constraint
 
 Keys
 - how to overcome constraint?
  - put the same chars at once (my approach)
  - remember the last character
 - it's possible to avoid duplicated pattern by skipping subsequent same chars. It's a popular and useful way in counting problem.
 
 */

constexpr int MOD = 1e9+7;

// O(N^2*2^N) time
class ColorfulGardenHard {
public:
  int dp[1<<15][15];
  int count(string G, string NG) {
    int N=SZ(G);
    memset(dp, 0, sizeof dp);
    sort(G.begin(),G.end());
    
    REP(i,N) if(i==0||G[i]!=G[i-1]) if(G[i]!=NG[0]) dp[1<<i][i]=1;
    FOR(mask,1,1<<N) {
      int pos=__builtin_popcount(mask);
      REP(last,N) if((mask&(1<<last))!=0&&dp[mask][last]) {
        REP(j,N) {
          if((mask&(1<<j))) continue;
          if(G[last]==G[j]) continue;
          if(NG[pos]==G[j]) continue;
          if(j!=0&&((1<<(j-1))&mask)==0&&G[j-1]==G[j]) continue;
          
          (dp[mask|(1<<j)][j] += dp[mask][last])%=MOD;
        }
      }
    }
    
    LL res=0;
    REP(i,N) (res+=dp[(1<<N)-1][i])%=MOD;
    return res;
  }
};

// O(26*2^2N) time, O(2^N) space
class ColorfulGardenHard_twoBitMasks {
  public:
  int CS[26]={0};
  int N;
  bool ok(int c, int mask, string &forb) {
    REP(i,N-1) if((mask&(1<<i))!=0&&(mask&(1<<(i+1)))!=0) return false;
    REP(i,N) if((mask&(1<<i))!=0&&forb[i]=='a'+c) return false;
    return true;
  }
  
  int count(string garden, string forbid) {
    N=SZ(garden);
    unordered_map<int,LL> dp;
    dp[0]=1;
    FORR(c,garden) ++CS[c-'a'];
    REP(c,26) if(CS[c]>0) {
      unordered_map<int,LL> dp2;
      int cnt = CS[c];
      REP(mask,1<<N) if(__builtin_popcount(mask)==cnt && ok(c,mask,forbid)) {
        FORR(kvp,dp) if((kvp.first&mask)==0) {
          int mask2=kvp.first|mask;
          dp2[mask2]+=kvp.second, dp2[mask2]%=MOD;
        }
      }
      dp = dp2;
    }
    
    LL res=0;
    FORR(kvp,dp) res+=kvp.second, res%=MOD;
    return res;
  }
};

// CUT begin
ifstream data("ColorfulGardenHard.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(string garden, string forbid, int __expected) {
    time_t startClock = clock();
    ColorfulGardenHard *instance = new ColorfulGardenHard();
    int __result = instance->count(garden, forbid);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        string garden;
        from_stream(garden);
        string forbid;
        from_stream(forbid);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(garden, forbid, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500997971;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "ColorfulGardenHard (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
