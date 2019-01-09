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
 
 2/26/2018
 
 9:43-9:50 analysis
 9:51-10:29 implement, but samples don't pass
 10:30-10:43 bug fix, submit and ACC  (397.03 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+523
  - http://kmjp.hatenablog.jp/entry/2014/01/14/0900
  - http://rsujskf.blog32.fc2.com/blog-entry-2163.html
  - http://d.hatena.ne.jp/kusano_prog/20111115/1321333067
  - http://topcoder.g.hatena.ne.jp/firewood/20111114/1321295768
 
 Summary:
  - It's straightforward to find DP approach though, implementation is not light.
  - Precompute block patterns worked well 👍
 
 */

// dp, O(N*4^N) time
constexpr long long MOD = 1e9+7;
LL dp[11][1<<10];
LL G[11];
LL F[1<<10][1<<10];
class SmallBricks31 {
  public:
  int W,H;
  int on(int mask, int i) {
    return (mask>>i)&1;
  }
  int f(int mask1, int mask2, int l, int r) {
    if(l>=r) return 1;
    FOR(i,l,r) if(!on(mask1,i)&&on(mask2,i)) {
      if(i==l) return 0;
      if(i==r-1) return 0;
      if(on(mask1,i-1)&&on(mask1,i+1)&&on(mask2,i-1)&&on(mask2,i+1)) {
        return f(mask1,mask2,l,i-1)*f(mask1,mask2,i+2,r);
      }
      return 0;
    }
    FOR(i,l,r) if(!on(mask2,i)) return f(mask1,mask2,l,i)*f(mask1,mask2,i+1,r);
    int x=0;
    FOR(i,l,r) x+=on(mask2,i);
    return G[x];
  }
  int countWays(int W, int H) {
    this->W=W,this->H=H;
    ZERO(G);
    G[0]=1;
    REP(i,10) if(G[i]) {
      G[i+1]+=G[i],G[i+2]+=G[i],G[i+3]+=G[i];
    }
    //dump4(G[1],G[2],G[3],G[10]);
    
    ZERO(F);
    REP(mask1,1<<W) REP(mask2,1<<W) {
      F[mask1][mask2]=f(mask1,mask2,0,W);
      /*
      REP(i,W) cout << on(mask2,i);
      cout<<endl;
      REP(i,W) cout << on(mask1,i);
      cout<<endl;
      dump3(mask1,mask2,F[mask1][mask2]);*/
    }

    ZERO(dp);
    dp[0][(1<<W)-1]=1LL;
    REP(i,H) REP(mask,1<<W) if(dp[i][mask]>0) {
      REP(mask2,1<<W) {
        (dp[i+1][mask2]+=dp[i][mask]*F[mask][mask2]%MOD)%=MOD;
      }
    }
    
    LL res=0;
    REP(mask,1<<W) res+=dp[H][mask],res%=MOD;
    return res;
  }
};

// CUT begin
ifstream data("SmallBricks31.sample");

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

bool do_test(int w, int h, int __expected) {
    time_t startClock = clock();
    SmallBricks31 *instance = new SmallBricks31();
    int __result = instance->countWays(w, h);
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
        int w;
        from_stream(w);
        int h;
        from_stream(h);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(w, h, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519667016;
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
        cout << "SmallBricks31 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
