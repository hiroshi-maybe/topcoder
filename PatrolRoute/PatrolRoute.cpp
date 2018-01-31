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
 
 1/30/2018
 
 8:19-8:40 analysis
 8:40-8:49 implemented but sample 4 doesn't passa
 8:50 add missing MOD and submit (276.06 pt)
 
 In one dimension, suppose we take x0,x1,x2 s.t. x0<x1<x2
 total distance of x is |x0-x1|+|x1-x2|+|x2-x0| = 2*(x2-x0).
 This means `x1` does not contribute total distance.
 
 I iterated t in range [minT,maxT] and brute-forced dx.
 If dx is fixed, dy is determined.
 Number of route is 6*(X-dx/2)*(dx/2-1)*(Y-dy/2)*(dy/2-1)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+542
  - http://mayokoex.hatenablog.com/entry/2016/04/18/221344
   - simple two nested loops
  - http://topcoder.g.hatena.ne.jp/kojingharang/20120509/1336567000
   - simple two nested loops
  - http://kg86.hatenablog.com/entry/20130723/1374556019
  - http://topcoder.g.hatena.ne.jp/agw/20120523/1337744657
 
 Editorial solution is more efficient.
 We can iterate dx=|x2-x0| and pick up x1 between x0 and x2.
 In y axis, we can iterate dy=|y2-y0| as well.
 If minT<=2*(dx+dy)<=maxT, we can compute combinatorics.
 
 23:11-23:20 add simpler solution in editorial.
 
 Key:
  - Manhattan distance can be computed independently in two dimensions
  - Total distance is determined by minX,maxX,minY,maxY
 
 Summary:
  - Low success rate problem though, I solved by myself in 30 mins 👍
  - I solved by searching t though, searching by dx and dy is more efficient
 
 */

const LL MOD=1000000007;
// O(X*Y) time
class PatrolRoute {
public:
  int countRoutes(int X, int Y, int minT, int maxT) {
    LL res=0;
    FORE(dx,2,X) FORE(dy,2,Y) if(minT<=2*(dx+dy)&&2*(dx+dy)<=maxT) {
      LL a=(X-dx)*(dx-1),b=(Y-dy)*(dy-1);
      LL c=6LL*a*b; c%=MOD;
      res+=c,res%=MOD;
    }
    return res;
  }
};

// O(T*X) time
class PatrolRoute_org {
  public:
  int countRoutes(int X, int Y, int minT, int maxT) {
    LL res=0;
    if(minT%2==1) ++minT;
    for(int t=minT; t<=maxT; t+=2) {
      for(int dx=2; dx<=t-2; dx+=2) {
        int dy=t-dx;
        if(X-dx/2<=0||Y-dy/2<=0) continue;
        dump3(t,dx,dy);
        LL a=(X-dx/2)*(dx/2-1)%MOD,b=(Y-dy/2)*(dy/2-1)%MOD;
        a*=b,a%=MOD;
        a*=6,a%=MOD;
        res+=a,res%=MOD;
      }
    }
    return res;
  }
};

// CUT begin
ifstream data("PatrolRoute.sample");

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

bool do_test(int X, int Y, int minT, int maxT, int __expected) {
    time_t startClock = clock();
    PatrolRoute *instance = new PatrolRoute();
    int __result = instance->countRoutes(X, Y, minT, maxT);
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
        int X;
        from_stream(X);
        int Y;
        from_stream(Y);
        int minT;
        from_stream(minT);
        int maxT;
        from_stream(maxT);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(X, Y, minT, maxT, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1517329151;
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
        cout << "PatrolRoute (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
