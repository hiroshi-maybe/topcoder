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
 
 9/26/2018
 
 22:10-22:49 AC (121.69 pt)
 
 http://apps.topcoder.com/wiki/display/tc/SRM+470
 
 Greedy part in the editorial is nice to learn
 
 */
int memo[1<<16];
class DoorsGame {
  public:
  int offset=50;
  int N,T;
  string A;
  bool lreach(int mask) {
    bool ok=true;
    REP(i,T) {
      int c=A[i]-'A';
      if((mask>>c)&1) continue;
      ok=false;
      break;
    }
    return ok;
  }
  bool rreach(int mask) {
    bool ok=true;
    for(int i=N-1; i>=T; --i) {
      int c=A[i]-'A';
      if((mask>>c)&1) continue;
      ok=false;
      break;
    }
    return ok;
  }
  int f(int mask) {
    int &res=memo[mask];
    if(res>=0) return res-offset;
    int t=__builtin_popcount(mask);
    
    bool lw=lreach(mask),rw=rreach(mask);
//    dump4(t,mask,lw,rw);
    if(lw&&rw) {
      res=offset;
      return res-offset;
    } else if(lw) {
      res=t%2==0?t:-t;
      res+=offset;
      return res-offset;
    } else if(rw) {
      res=t%2==1?t:-t;
      res+=offset;
      return res-offset;
    }
    
    VI W,L; int D=0;
    REP(i,16) if(!((mask>>i)&1)) {
      int a=-f(mask|(1<<i));
      if(a>0)W.push_back(a);
      else if(a==0) ++D;
      else if(a<0) L.push_back(a);
    }
    sort(W.begin(),W.end()),sort(L.begin(),L.end());
    if(SZ(W)) res=W.front();
    else if(D) res=0;
    else res=L.front();
    res+=offset;
//    dump3(t,mask,res-offset);
    return res-offset;
  }
  int determineOutcome(string A, int T) {
    MINUS(memo);
    this->A=A,this->T=T,this->N=SZ(A);
    return f(0);
  }
};

// CUT begin
ifstream data("DoorsGame.sample");

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

bool do_test(string doors, int trophy, int __expected) {
    time_t startClock = clock();
    DoorsGame *instance = new DoorsGame();
    int __result = instance->determineOutcome(doors, trophy);
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
        string doors;
        from_stream(doors);
        int trophy;
        from_stream(trophy);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(doors, trophy, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1538025033;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "DoorsGame (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
