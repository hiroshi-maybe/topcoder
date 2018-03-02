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
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 2/28/2018
 
 22:32-22:47 analysis
 22:48-23:32 implement, some of bugfixes and ACC (393.21 pt)
 
 3/1/2018
 
 18:00-18:22 read editorial and add simplified solution
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+520
  - http://kmjp.hatenablog.jp/entry/2014/01/15/0900
  - http://d.hatena.ne.jp/kusano_prog/20111004/1317754973
   - defining a score = 3p-c+3 is cool
  - http://area.hateblo.jp/entry/2014/03/27/014940
 
 Key:
  - dp
 
 Summary:
  - Analysis was straightforward though, it took much time to submit due to bugs 👎
   - implementation bug of duplicated variable name
   - design bug of challenge condition handling
 
 */
const LL MOD=1000000007;
LL memo[51][4][4];
class SRMSystemTestPhase {
public:
  vector<string> R;
  LL f(int i, int P, int C) {
    if(i==SZ(R)) return 1;
    LL &res=memo[i][P][C];
    if(res>=0) return res;
    
    res=0;
    REP(a,4) REP(b,4) REP(c,4) {
      int r[3]={a,b,c};
      bool ok=true;
      int pp=0,cc=0;
      REP(j,3) {
        if(R[i][j]=='Y'&&r[j]==3) { ok=false; break; }
        if(R[i][j]=='N'&&r[j]<=2) { ok=false; break; }
        pp+=r[j]==0;
        cc+=r[j]==2;
      }
      if(!ok) continue;
      if(pp>P) continue;
      if(pp==P&&C>cc) continue;
      res+=f(i+1,pp,cc),res%=MOD;
    }
    return res;
  }
  int countWays(vector<string> R) {
    this->R=R;
    MINUS(memo);
    return f(0,3,0);
  }
};

class SRMSystemTestPhase_org {
  public:
  vector<string> R;
  LL f(int i, int P, int C) {
    if(i==SZ(R)) return P==0;
    LL &res=memo[i][P][C];
    if(res>=0) return res;
    
    res=0;
    REP(a,4) REP(b,4) REP(c,4) {
      int r[3]={a,b,c};
      bool ok=true;
      int pp=0,cc=0;
      REP(j,3) {
        if(R[i][j]=='Y'&&r[j]==3) { ok=false; break; }
        if(R[i][j]=='N'&&r[j]<=2) { ok=false; break; }
        pp+=r[j]==0;
        cc+=r[j]==2;
      }
      if(!ok) continue;
      if(pp!=P) continue;
      if(pp==P&&C>cc) continue;
      REPE(p,pp) res+=f(i+1,p,p==pp?cc:0),res%=MOD;
    }
    return res;
  }
  int countWays(vector<string> R) {
    this->R=R;
    MINUS(memo);
    LL res=0;
    REP(i,4) res+=f(0,i,0),res%=MOD;
    return res;
  }
};

// CUT begin
ifstream data("SRMSystemTestPhase.sample");

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

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
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

bool do_test(vector<string> description, int __expected) {
    time_t startClock = clock();
    SRMSystemTestPhase *instance = new SRMSystemTestPhase();
    int __result = instance->countWays(description);
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
        vector<string> description;
        from_stream(description);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(description, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519885911;
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
        cout << "SRMSystemTestPhase (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
