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
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stdout, ##args); putc('\n',stdout); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cout<<*begin<<','; } cout<<endl; } }

/*
 
 11/8/2018
 
 21:05-21:40 give up
 
 Square root is the blocker of this problem. I couldn't resolve it.
 
 My approaches
  - V[X] = E[X^2]-E[X]^2
  - Linearity of expectation
  - Formula transformation

 http://apps.topcoder.com/wiki/display/tc/SRM+547
 
 The third approach was closest. However I couldn't come up with an idea to focus on delta of height...
 Geometry figure should have helped. However I didn't dig it deeply.
 
 Auxiliary problem is clear.
 
 ∑ { abs(x-y) : x=1..a, y=1..b }
 
 If I don't know how to solve this in O(max(a,b)), it would be hard to come up with the solution.
 Keep attention to accumulation derived from "uniform range".
 
 22:16 got AC
 
 Key:
  - computation based on uniform range <=> cumulative sum
 
 Summary:
  - Don't be confused about expected value. If probability is equivalent, expectated value may not be main point
  - Summation of uniform values is a sign of cumulative sum. We don't need to sum many times
  - Evaluate number of possible values. If it's small, we may be able to precompute, accumulate and query in O(1)
 
 */
class Pillars {
  public:
  
  vector<double> f(int W, int X, int Y) {
    vector<double> res(X);
    FORE(a,1,X) {
      FORE(b,1,Y) {
        res[a-1]+=hypot(W,abs(a-b));
      }
    }
    return res;
  }
  
  double getExpectedLength(int W, int X, int Y) {
    if(X>Y) swap(X,Y);
//    vector<double> as=f(W,X,Y);
    
    vector<double> cum(Y+1,0);
    REP(i,Y) cum[i]+=hypot(W,i),cum[i+1]+=cum[i];
    double res=0;
    REP(i,X) {
      double x=cum[Y-1-i],y=cum[i]-cum[0];
      res+=x+y;
    }
    return res/(double)X/(double)Y;
  }
};

// CUT begin
ifstream data("Pillars.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(int w, int x, int y, double __expected) {
    time_t startClock = clock();
    Pillars *instance = new Pillars();
    double __result = instance->getExpectedLength(w, x, y);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        int x;
        from_stream(x);
        int y;
        from_stream(y);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(w, x, y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1541739793;
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
        cout << "Pillars (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
