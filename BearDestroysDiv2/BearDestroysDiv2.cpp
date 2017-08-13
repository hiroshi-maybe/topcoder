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
typedef pair< int , int > II;
typedef tuple< int, int, int > III;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// debug cout
#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

/**
 
 8/12/2017
 
 11:13-12:26 time up
 12:30-12:53,14:00-14:56 read editorials
 - http://kmjp.hatenablog.jp/entry/2015/10/17/0900
  - O(W^2*H^2*2^(2*W)) time
 - https://apps.topcoder.com/wiki/display/tc/SRM+671
  - O(W^3*H^3*2^W) time
 
 14:56-15:55 passed system test (It took 20 mins to find a bug in bit mask hell)
  - n*dp[r][n][mask] - design mistake
 
 Key:
  - W is small => bit DP
  - { all the states of S/E at current row } x { all the states blocked by previous row } = { all the states blocked in next row }
 
 Summary:
  - tried to solve focusing one cell and neighboring left, top and rop-right though, could not solve
    - this approach is used in div1 hard size though, it's not necessary in div2 size
    - dp[row][col][# of toppled tree][NA/S/E] = cnt
      - many conditions to take care
  - bit DP again...
 
 */

LL dp[51][141][1<<7];
// O(H^2*W^2*4^W) time
class BearDestroysDiv2 {
public:
  int sumUp(int W, int H, int MOD) {
    ZERO(dp);
    dp[0][0][0]=1LL;
    REP(r,H) REP(n,141) REP(m1,1<<W) if(dp[r][n][m1]) {
      REP(mask,1<<W) {
        LL k=0,m2=0,ngmask=m1;
        REP(i,W) if(((ngmask>>i)&1)==0) {
          if((mask>>i)&1) {
            // E
             if(i==W-1 || ((ngmask>>(i+1))&1)==1) {
             if(r<H-1) ++k,m2|=(1<<i); // to S
             } else ++k, ngmask|=1<<(i+1); // to E
          } else {
            // S
            if(r<H-1) ++k,m2|=(1<<i); // to S
            else {
              if(i<W-1&& ((ngmask>>(i+1))&1)==0) ++k, ngmask|=1<<(i+1); // to E
            }
          }
        }
        
        (dp[r+1][n+k][m2]+=dp[r][n][m1])%=MOD;
      }
    }
    
    LL res=0;
    REP(n,141) res+=(LL)n*dp[H][n][0], res%=MOD;
    
    return res;
  }
};

// didn't pass
class BearDestroysDiv2_wrong {
  public:
  int sumUp(int W, int H, int MOD) {
    ZERO(dp);
    dp[0][0][0]=1LL;
    
    REP(r,H) REP(n,145) REP(m1,1<<W) if(dp[r][n][m1]) {
      REP(mask,1<<W) {
        LL k=0,m2=0;
        REP(i,W) if(((m1>>i)&1)==0) {
          if (((mask>>i)&1)==0) {
            // S
            if(r>=H-1) continue;
            if(i==0 || !(((m1>>(i-1))&1)==0 && ((mask>>(i-1))&1)==1)) {
              ++k; m2|=(1<<i);
            }
          } else {
            // E
            if(i==W-1 || ((m1>>(i+1))&1)) {
              if(r>=H-1) continue;
              ++k, m2|=(1<<i);
            } else ++k;
          }
        }
        
        (dp[r+1][n+k][m2]+=dp[r][n][m1])%=MOD;
      }
    }
    
    LL res=0;
    REP(n,145) res+=n*dp[H][n][0], res%=MOD;
    
    return res;
  }
};

// CUT begin
ifstream data("BearDestroysDiv2.sample");

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

bool do_test(int W, int H, int MOD, int __expected) {
    time_t startClock = clock();
    BearDestroysDiv2 *instance = new BearDestroysDiv2();
    int __result = instance->sumUp(W, H, MOD);
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
        int W;
        from_stream(W);
        int H;
        from_stream(H);
        int MOD;
        from_stream(MOD);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(W, H, MOD, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502561572;
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
        cout << "BearDestroysDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
