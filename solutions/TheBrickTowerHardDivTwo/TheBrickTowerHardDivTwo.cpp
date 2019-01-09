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
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define MAXS(a,b) a = max(a,b)
#define MINS(a,b) a = min(a,b)
// debug cout
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 1/9/2018
 
 9:48-10:00 analysis
 10:01-10:14 implementation
 10:14-10:18 debug (568.89 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+554
  - http://kmjp.hatenablog.jp/entry/2013/11/09/0930
  - http://d.hatena.ne.jp/kusano_prog/20120902/1346616067
  - http://ekaing.hatenablog.com/entry/2013/03/30/223228
  - http://area.hateblo.jp/entry/2013/12/31/002122
 
 If we remember colors in previous level, we can compute number of pairs of same color.
 Straightforward DP by state `dp[i][mask][k]`.
 
 Summary:
  - I solved by myself in 30 mins 👍
  - Hmmmmm I want to solve more quickly problem such that I can analyze immediately 🤔
   - Understand problem more quickly. Should I look at samples first to figure out input and output?
   - I spent 4 mins to fix a bug. Keep focusing during implementation too.
  - Look at dependency carefully when designing nested loops
   - k-loop should be inner to save duplicated computation in this problem
 
 */

// O(C^8*K*H) time
const LL MOD=1234567891;
LL dp[50][256][8];
class TheBrickTowerHardDivTwo {
  public:
  int find(int C, int K, int H) {
    ZERO(dp);
    REP(mask,C*C*C*C) {
      int m=mask;
      int X[4]={};
      REP(i,4) X[i]=m%C,m/=C;
      int k=(X[0]==X[1])+(X[0]==X[2])+(X[1]==X[3])+(X[2]==X[3]);
      dp[0][mask][k]=1LL;
      if(k==0) dump2(mask,dp[0][mask][k]);
    }
    
    /*
    // This is my original implementation.
    // Computation of same color does not depend on `k`
    // Thus we can move it out of iteration of `k`
    // This optimization reduces running time of large input from 800(ms) to 300(ms)
    REP(i,H) REP(mask,C*C*C*C) REPE(k,K) if(dp[i][mask][k]) {
      int y=mask;
      int Y[4]={};
      REP(i,4) Y[i]=y%C,y/=C;
      REP(mask2,C*C*C*C) {
        int x=mask2;
        int X[4]={};
        REP(i,4) X[i]=x%C,x/=C;
        int kk=k+(X[0]==X[1])+(X[0]==X[2])+(X[1]==X[3])+(X[2]==X[3]);
        REP(i,4) kk+=(X[i]==Y[i]);
        if(kk<=K) (dp[i+1][mask2][kk]+=dp[i][mask][k])%=MOD;
      }
    }*/
    
    // Optimized iteration:
    REP(i,H) REP(mask,C*C*C*C) {
      int y=mask;
      int Y[4]={};
      REP(i,4) Y[i]=y%C,y/=C;
      REP(mask2,C*C*C*C) {
        int x=mask2;
        int X[4]={};
        REP(i,4) X[i]=x%C,x/=C;
        int d=(X[0]==X[1])+(X[0]==X[2])+(X[1]==X[3])+(X[2]==X[3]);
        REP(i,4) d+=(X[i]==Y[i]);
        REPE(k,K) if(k+d<=K&&dp[i][mask][k]) {
          (dp[i+1][mask2][k+d]+=dp[i][mask][k])%=MOD;
        }
      }
    }
    
    LL res=0;
    REP(i,H) REP(mask,C*C*C*C) REPE(k,K) if(dp[i][mask][k]) {
      if(i==0) dump4(i,mask,k,dp[i][mask][k]);
      res+=dp[i][mask][k],res%=MOD;
    }
    return res;
  }
};

// CUT begin
ifstream data("TheBrickTowerHardDivTwo.sample");

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

bool do_test(int C, int K, int H, int __expected) {
    time_t startClock = clock();
    TheBrickTowerHardDivTwo *instance = new TheBrickTowerHardDivTwo();
    int __result = instance->find(C, K, H);
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
        int C;
        from_stream(C);
        int K;
        from_stream(K);
        int H;
        from_stream(H);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(C, K, H, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515520095;
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
        cout << "TheBrickTowerHardDivTwo (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
