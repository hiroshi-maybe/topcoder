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
 
 2/4/2018
 
 18:34-19:15 analysis
 19:19-19:28 implement and ACC (412.13 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+539
  - http://d.hatena.ne.jp/simezi_tan/20120419/1334834921
  - http://kmjp.hatenablog.jp/entry/2014/01/05/0930
  - http://hamko.hatenadiary.jp/entry/2017/03/03/175247
 
 [Odd]
 O
 XOX
 OXO
 
 [Even]
 XO
 OX
 OXOX
 ...
 
 Editorial solution is counting XO and OX as well to simplify solutions.
 They eventually contribute to even patterns though.
 Two patterns by counting "|O|X" and "O|X|"
 
 Key:
  - Only 3 cases satisfies odd pattern:
 
 Summary:
  - Deep observation was needed though, I solved by myself 👍
  - We just need to check three areas. Brute-forcing those boundaris is sufficient (no need of DP)
 
 */

// brute-force, O(N^2) time
class CaptureFish {
public:
  int getParity(string X) {
    int N=SZ(X);
    int res=0;
    REP(i,N) FORE(j,i+1,N) {
      int inx=0,ino=0,outx=0,outo=0;
      REP(k,N) {
        if(i<=k&&k<j) {
          // in
          if(X[k]=='O') ++ino;
          if(X[k]=='X') ++inx;
        } else {
          // out
          if(X[k]=='O') ++outo;
          if(X[k]=='X') ++outx;
        }
      }
      // both patterns in area
      if(ino&&inx) continue;
      if(outo&&outx) continue;
      // same pattern in two areas
      if(ino&&outo) continue;
      if(inx&&outx) continue;
      ++res;
    }
    return res%2;
  }
};

// dp, O(N) time
int memo[51][3][2];
class CaptureFish_org {
  public:
  string X;
  int f(int i,int ph,int lx) {
    int &res=memo[i][ph][lx];
    if(res>=0) return res;
    if(i==SZ(X)) {
      return res=(ph==2);
    }
    if(i==SZ(X)-1&&ph<=1) return res=0;
    
    char exp=((ph&1)^lx)==0?'X':'O';
    if(X[i]!='*'&&exp!=X[i]) return res=0;
    
    res=f(i+1,ph,lx);
    if(ph==2) return res;
    
    res+=f(i+1,ph+1,lx),res%=2;
    return res;
  }
  int getParity(string X) {
    this->X=X;
    MINUS(memo);
    int p1=count(X.begin(),X.end(),'X')==0;
    int a=f(0,0,0),b=f(0,0,1);
    return (a+b+p1)%2;
  }
};

// CUT begin
ifstream data("CaptureFish.sample");

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

bool do_test(string fish, int __expected) {
    time_t startClock = clock();
    CaptureFish *instance = new CaptureFish();
    int __result = instance->getParity(fish);
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
        string fish;
        from_stream(fish);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(fish, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1517798061;
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
        cout << "CaptureFish (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
