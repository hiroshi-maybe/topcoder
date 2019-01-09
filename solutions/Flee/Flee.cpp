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
// https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
double sign(II p1, II p2, II p3) {
  return (p1.first - p3.first) * (p2.second - p3.second) - (p2.first - p3.first) * (p1.second - p3.second);
}

bool pointInTriangle(II pt, II v1, II v2, II v3) {
  bool b1, b2, b3;
  
  b1 = sign(pt, v1, v2) < 0.0;
  b2 = sign(pt, v2, v3) < 0.0;
  b3 = sign(pt, v3, v1) < 0.0;
  
  return ((b1 == b2) && (b2 == b3));
}*/

/*
 
 8/23/2017
 
 8:52-9:26 design done
 9:26-9:40 implemented, submit and system test failed (434.05 pt)
 found out a case where origin is not surrounded by three points
 10:07 failed system test by intersect
 10:13 found point in triangle algorithm and passed system test
  - https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
 
 editorial:
   - http://kmjp.hatenablog.jp/entry/2015/07/11/1030
   - https://apps.topcoder.com/wiki/display/tc/SRM+662
 
 Key:
   - detailed analysis
     - if origin is NOT surrounded, res = min { dist(p[i], origin) : i=0..N }
     - if origin is surrounded, res = min { dist(p[i], origin) : i=0..N } ∪ { dist(p[i], origin) : i=0..N }
   - use cross product to check if origin is surrounded or not

 Summary:
   - analysis issue 👎
     - should not have missed not-surrounded case
   - knowledge issue 👎
     - should be more familiar with cross product
     - surrounded or not? => cross product helps
   - anyway solved 👍
 
 */

int det(II a, II b) {
  return a.first*b.second-a.second*b.first;
}

bool surrounded(II a, II b, II c) {
  int d1=det(a,b)>0,d2=det(b,c)>0,d3=det(c,a)>0;
  return d1==d2&&d2==d3;
}

class Flee {
  public:
  double dist(II a, II b) {
    int dx=a.first-b.first,dy=a.second-b.second;
    return sqrt(dx*dx+dy*dy);
  }
  double maximalSafetyLevel(vector<int> X, vector<int> Y) {
    set<II> G;
    REP(i,SZ(X)) G.emplace(X[i],Y[i]);
    vector<II> gs(G.begin(),G.end());
    II O={0,0};
    
    double res=numeric_limits<double>::max();
    REP(i,SZ(gs)) res=min(res,dist(O,gs[i]));
    if(SZ(gs)>=3 && surrounded(gs[0],gs[1],gs[2])) {
      double x=0;
      REP(i,3) {
        auto p1=gs[i],p2=gs[(i+1)%3];
        x=max(x, dist(p1,p2)/2.0);
      }
      res=min(res, x);
    }

    return res;
  }
};

// CUT begin
ifstream data("Flee.sample");

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

bool do_test(vector<int> x, vector<int> y, double __expected) {
    time_t startClock = clock();
    Flee *instance = new Flee();
    double __result = instance->maximalSafetyLevel(x, y);
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
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1503503512;
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
        cout << "Flee (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
