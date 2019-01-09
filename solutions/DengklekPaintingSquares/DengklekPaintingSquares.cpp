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
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 2/12/2018
 
 9:14-9:18 analysis
 9:58-10:12 debug, submit and TLE (379.64 pt). Did minor optimization and ACC.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+532
    - O(N*M*3^M) solution
  - http://d.hatena.ne.jp/simezi_tan/20120210/1328865766
    - O(N*M*3^M) solution
  - http://kmjp.hatenablog.jp/entry/2014/01/06/1030
    - O(N*M*4^M) solution
  - http://topcoder.g.hatena.ne.jp/firewood/20120223/1330012087
 
 I was trying to remember 2*M cells though, actually only M cells matter as shown below:
 Assume we are looking at cell filled with `?`
 
 ...12012
 010?....
 
 Key:
  - Remembering recent M cells suffices to determine state transition
 
 Summary:
  - Due to small M, this was obviously bit DP though, I should have paid more attention to runtime complexity
   - I went back and forth between 4^M vs 3^M
   - How to validate each tile by making sure number of adjacent cells is even
  - I should have spent more time for analysis. However I was upset about previous problem. I tried to solve this too quickly
  - I cannot believe that variable to be `int` was declared as `bool`. I wasted at least 5 mins 👎👎👎👎👎👎👎👎👎👎
  - It's not always optimal in row-wise state. Always keep in mind to remember as little state as possible
 
 */

// O(N*M*3^M*2^M) time
const LL MOD=1000000007;
LL dp[101][8][6561];
class DengklekPaintingSquares {
public:
  int numSolutions(int N, int M) {
    ZERO(dp);
    dp[0][0][0]=1;
    int pow3[9];
    pow3[0]=1;
    REP(i,8) pow3[i+1]=pow3[i]*3;
    REP(i,N) REP(j,M) REP(mask1,pow3[M]) if(dp[i][j][mask1]>0) {
      REPE(k,1) {
        // 0: no paint, 1: painted with odd adjacent cells, 2: even adjacent cells
        int pre=mask1/pow3[M-1]%3,left=mask1%3;
        if(pre==1&&k==0) continue;
        if(pre==2&&k==1) continue;
        
        int mask2=mask1-left;
        
        bool pre1=pre>0,left1=j==0?0:left>0;
        
        int cur=k==0?0:2-(pre1+left1)%2;
        if(j!=0&&left>0) left=2-((left%2==0?2:1)+k)%2;
        
        mask2+=left;
        mask2=mask2*3%pow3[M]+cur;
        (dp[i+(j+1)/M][(j+1)%M][mask2]+=dp[i][j][mask1])%=MOD;
      }
    }
    LL res=0;
    REP(mask,pow3[M]) {
      bool ok=true;
      REP(i,M) ok&=((mask/pow3[i]%3)!=1);
      if(!ok) continue;
      (res+=dp[N][0][mask])%=MOD;
    }
    return res;
  }
};

class DengklekPaintingSquares_org {
  public:
  LL dp[101][6561];
  int numSolutions(int N, int M) {
    ZERO(dp);
    dp[0][0]=1;
    LL pow3=1;
    REP(i,M) pow3*=3;
    REP(i,N) REP(mask1,pow3) if(dp[i][mask1]>0) {
      VI pres(M,0);
      pres[0]=mask1;
      FOR(j,1,M) pres[j]=pres[j-1]/3,pres[j-1]%=3;
      
      REP(mask2,1<<M) {
//        int pmask=mask1;
        bool ok=true; int nmask=0;
        REP(j,M) {
//          int pre=pmask%3; pmask/=3;
          int pre=pres[j];
          int p1=pre;
          if(p1>0) {
            p1=(p1+((mask2>>j)&1))&1;
          }
          ok&=((p1&1)==0);
          // Without this, TLE
          if(!ok) break;
          
          int next=0;
          if((mask2>>j)&1) {
            next=pre>0;
            if(j>0) next+=(mask2>>(j-1))&1;
            if(j<M) next+=(mask2>>(j+1))&1;
            next=next&1;
            if(next==0) next=2;
//            dump2(pre>0,next);
          }
          nmask=nmask*3+next;
        }
//        dump3(i,mask1,mask2);
//        dump2(ok,nmask);
        if(ok) (dp[i+1][nmask]+=dp[i][mask1])%=MOD;
      }
    }
    LL res=0;
    REP(mask,pow3) if(dp[N][mask]) {
      int cur=mask;
      bool ok=true;
      REP(j,M) {
        int pre=cur%3; cur/=3;
        ok&=(pre%2==0);
      }
      if(ok) (res+=dp[N][mask])%=MOD;
    }
    return res;
  }
};

// CUT begin
ifstream data("DengklekPaintingSquares.sample");

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

bool do_test(int N, int M, int __expected) {
    time_t startClock = clock();
    DengklekPaintingSquares *instance = new DengklekPaintingSquares();
    int __result = instance->numSolutions(N, M);
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
        int N;
        from_stream(N);
        int M;
        from_stream(M);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, M, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1518455671;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 950 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "DengklekPaintingSquares (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
