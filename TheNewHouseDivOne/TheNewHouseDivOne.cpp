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
 
 9/11/2018
 
 12:54-13:15 analysis
 13:35 1WA. give up.
 
 http://apps.topcoder.com/wiki/display/tc/SRM+445
 http://apps.topcoder.com/forums/?module=Thread&threadID=647115&start=0
 https://ameblo.jp/utmath/entry-10987262688.html
 http://rsujskf.blog32.fc2.com/blog-entry-471.html
 http://touyoubuntu.hatenablog.com/entry/20120617/1339899141
 
 Suppose we found that x=1.12345 is minimal point for k-th distance X2=10.
 Also (k-1)-th point is X1=-7
 
  -7              1 2               10
 -|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|->
  ^                ^                ^
  X1               x=1.12345        X2
 
 However we can obtain better value by moving it to right.
 How far can we move? `2` may be too much move because X1 becomes k-th distance point and it's 9.
 The optimal point in such a case is 1.5 which keeps both X1 and X2 k-th distance with 8.5.
 
 Thus we can see that a.5 points are sufficient to find optimal position.
 This is the same scheme of proof as min sum of distances.
 
 x = -12.00, y = 36.50, A[K-1] = 29.50
 
 x = 3.00, y = 35.50, A[K-1] = 28.50
 
 My original algorithm passed samples. However it's wrong.
 I took optimal min points for X and Y axis independently.
 However those candidates are NOT generally optimal.
 it's optimal ONLY when we picked k-neighbor points.
 Thus this does not always give optimal points.
 
 I came up with this idea from different problem in which brute-force of all the points gave optimal solution.
 In the problem, median of K points, which is one of the given pointes, was sufficient. Thus brute-forcing all the x and y positions should give optimal solution.
 
 However that's not the case in this problem. There is no guarantee that middle of K-neighbored x and y positions are sufficient.
 
 14:41 add solution
 
 */

class TheNewHouseDivOne {
public:
  double distance(vector<int> X, vector<int> Y, int K) {
    int N=SZ(X);
    double res=1e8;
    for(double x=-110; x<110; x+=0.5) for(double y=-110; y<110; y+=0.5) {
      vector<double> A;
      REP(k,N) A.push_back(abs(1.0*X[k]-x)+abs(1.0*Y[k]-y));
      sort(A.begin(),A.end());
//      if(A[K-1]<res) dump3(x,y,A[K-1]);
      SMIN(res,A[K-1]);
    }
    return res;
  }
};

class TheNewHouseDivOne_wrong {
  public:
  double distance(vector<int> X, vector<int> Y, int K) {
    int N=SZ(X);
    double res=1e8;
    VI XX(X),YY(Y);
    sort(XX.begin(),XX.end()),sort(YY.begin(),YY.end());
    dumpAR(XX);
    dumpAR(YY);
    vector<double> xs,ys;
    REP(i,N) if(i+K-1<N) {
      xs.push_back(0.5*(XX[i]+XX[i+K-1]));
      ys.push_back(0.5*(YY[i]+YY[i+K-1]));
    }
//    REP(i,N) xs.push_back(XX[i]);
//    REP(i,N) ys.push_back(YY[i]);

    dumpAR(xs);
    dumpAR(ys);
    REP(i,SZ(xs)) REP(j,SZ(ys)) {
      double x=xs[i],y=ys[j];
      vector<double> A;
      REP(k,N) A.push_back(abs(1.0*X[k]-x)+abs(1.0*Y[k]-y));
      sort(A.begin(),A.end());
      if(A[K-1]<res) dump3(x,y,A[K-1]);
      SMIN(res,A[K-1]);
    }
    return res;
  }
};

// CUT begin
ifstream data("TheNewHouseDivOne.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<int> x, vector<int> y, int k, double __expected) {
    time_t startClock = clock();
    TheNewHouseDivOne *instance = new TheNewHouseDivOne();
    double __result = instance->distance(x, y, k);
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
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        int k;
        from_stream(k);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1536695675;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 275 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TheNewHouseDivOne (275 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
