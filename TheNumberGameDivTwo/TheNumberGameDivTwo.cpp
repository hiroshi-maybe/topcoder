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

/*
 
 12/11/2017
 
 8:43-8:52 system test passed (449.63 pt)
 
 Editorial:
 - https://apps.topcoder.com/wiki/display/tc/SRM+575
 - http://tatsyblog.sakura.ne.jp/wordpress/contests/topcoder/200/
 - http://kujira16.hateblo.jp/entry/2013/04/07/183401
 - http://sucrose.hatenablog.com/entry/2013/04/07/031251
 
 24:37 Add solution with grundy number
 
 Summary:
  - typical game DP
 
 */
VI divs(int n) {
  VI res;
  for(int p=2; p*p<=n; ++p) if(n%p==0) {
    res.push_back(p);
    int q=n/p;
    if(q!=p) res.push_back(q);
  }
  return res;
}

#define

// grundy number, O(N*√N) time
int G[1001];
class TheNumberGameDivTwo {
public:
  string p0= "John",p1="Brus";
  string find(int N) {
    G[1]=0;
    for(int n=2; n<=N; ++n) {
      VI ds=divs(n);
      G[n]=0;
      SETI S;
      FORR(d,ds) S.emplace(G[n-d]);
      int g=0;
      while(S.count(g)!=0) ++g;
      G[n]=g;
    }
//    dump2(N,G[N]);
    return G[N]!=0?p0:p1;
  }
};

// dp, O(N*√N) time
int memo[1001];
class TheNumberGameDivTwo_org {
  public:
  string p0= "John",p1="Brus";
  bool f(int n) {
    int &res=memo[n];
    if(res>=0) return res;
    
    VI ds=divs(n);
    res=0;
    FORR(d,ds) res|=!f(n-d);
    return res;
  }
  string find(int N) {
    MINUS(memo);
    return f(N)?p0:p1;
  }
};

// CUT begin
ifstream data("TheNumberGameDivTwo.sample");

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

bool do_test(int n, string __expected) {
    time_t startClock = clock();
    TheNumberGameDivTwo *instance = new TheNumberGameDivTwo();
    string __result = instance->find(n);
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
        int n;
        from_stream(n);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1513010573;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TheNumberGameDivTwo (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
