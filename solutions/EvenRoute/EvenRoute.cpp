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
 
 2/5/2018
 
 8:43-9:24 ACC (238.06 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+538
  - https://apps.topcoder.com/forums/?module=Thread&threadID=740604&start=0&mc=12#1511188
  - http://d.hatena.ne.jp/kusano_prog/20120320/1332265844
  - http://mayokoex.hatenablog.com/entry/2016/03/30/233539
  - http://topcoder.g.hatena.ne.jp/agw/20120321/1332305540
  - http://yaoshimax.hatenablog.com/entry/20120320/1332267696
 
 Let's consider 1-dimension. Suppose we are moving from 0 to X.
 
 a) No detour
 
 Simplest case. If no detour happens, parity of path is X%2
 
 b) Detour after reaching X
 
 After reaching X, if we move back and forth and back to X, parity is still X%2.
 That is because we need to cancel distance that we went away.
 
 c) Detour before reaching X
 
 Even if detour happens before reaching X, that's canceled before reaching X.
 0->b->a->b->X (a<b)
 In this path, we go b-a twice. D = b+(b-a)+(b-a)+X-b = 2*(b-a)+X
 parity of D = (2*(b-a)+X)%2=X%2
 
 d) Going through other places than X
 
 This is same as case c). Thus intermediate places do not affect parity of path 0↝X
 
 The same property holds in y-axis independently.
 Therefore parity of path 0↝P = (abs(P.x)+abs(P.y))%2
 
 19:24- add simpler math solution
 
 Summary:
  - I got ACC though, I was not very sure about correctness 👎
  - Solve simplified version 1-dimension would have been a good start 🤔
 
 */

class EvenRoute {
public:
  string yes="CAN",no="CANNOT";
  string isItPossible(vector<int> X, vector<int> Y, int P) {
    int N=SZ(X);
    REP(i,N) {
      int p=(abs(X[i])+abs(Y[i]))%2;
      if(p==P) return yes;
    }
    return no;
  }
};

class EvenRoute_org {
  public:
  string yes="CAN",no="CANNOT";
  string isItPossible(vector<int> X, vector<int> Y, int P) {
    bool all0=true;
    int N=SZ(X);
    REP(j,N)REP(i,j) {
      int d=abs(X[i]-X[j])+abs(Y[i]-Y[j]);
      all0&=(d%2==0);
    }
    int e0=0,e1=0;
    REP(i,N) {
      int d=abs(X[i])+abs(Y[i]);
      (d%2==0?e0:e1)++;
    }
    if(all0&&e0>0&&e1==0) return P==1?no:yes;
    if(all0&&e0==0&&e1>0) return P==0?no:yes;
    return yes;
  }
};

// CUT begin
ifstream data("EvenRoute.sample");

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

bool do_test(vector<int> x, vector<int> y, int wantedParity, string __expected) {
    time_t startClock = clock();
    EvenRoute *instance = new EvenRoute();
    string __result = instance->isItPossible(x, y, wantedParity);
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
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        int wantedParity;
        from_stream(wantedParity);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, wantedParity, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1517849021;
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
        cout << "EvenRoute (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
