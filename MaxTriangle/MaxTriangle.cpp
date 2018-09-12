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
 
 14:14-14:31 submit but got WA
 14:58 got AC after 3WA

 /\ is NOT exhaustive AT ALL 😡
 |_ and /_ and |/ should be covered too
 
 http://apps.topcoder.com/wiki/display/tc/SRM+449
 Actually my case classification is not general or exhaustive enough.
 Suppose both sides sqrt(A) and sqrt(B) are connected at origin (0,0).
 Then we can make (±x,±y) for both A and B, which is general enough.
 
 Area = 1/2*|cross product of A and B|
 
 Summary:
  - Evaluate if idea is sufficent and necessary
 
 */

class MaxTriangle {
public:
  LL sqroot(LL x) {
    for(int d=-2; d<=2; ++d) {
      LL q=sqrt(x)+d;
      if(q*q==x) return abs(q);
    }
    return -1;
  }
  vector<pair<LL,LL>> f(LL A) {
    vector<pair<LL,LL>> res;
    for(LL p=0LL; p*p<=A; ++p) {
      LL qq=A-p*p;
      LL q=sqroot(qq);
      if(q<0) continue;
      res.emplace_back(p,q);
      res.emplace_back(-p,q);
      res.emplace_back(p,-q);
      res.emplace_back(-p,-q);
    }
    return res;
  }
  double calculateArea(int A, int B) {
    double res=-1;
    vector<pair<LL,LL>> SA=f(A),SB=f(B);
    FORR(pa,SA)FORR(pb,SB) {
      double a=0.5*abs(pa.first*pb.second-pa.second*pb.first);
//      dump4(pa.first,pa.second,pb.first,pb.second);
      if(a>0) SMAX(res,a);
    }
    return res;
  }
};

class MaxTriangle_org {
  public:
  LL sqroot(LL x) {
    for(int d=-2; d<=2; ++d) {
      LL q=sqrt(x)+d;
      if(q<0) continue;
      if(q*q==x) return q;
    }
    return -1;
  }
  set<double> f(LL A) {
    set<double> res;
    for(LL p=1LL; p*p<=A; ++p) {
      LL qq=A-p*p;
      LL q=sqroot(qq);
      if(q<=0) continue;
//      dump3(A,p,q);
      res.emplace(atan2(p,q));
      res.emplace(atan2(q,p));
    }
    return res;
  }
  double calculateArea(int A, int B) {
    double res=-1;
    set<double> SA=f(A),SB=f(B);
    FORR(ra,SA)FORR(rb,SB) {
      double a=0.5*sqrt(A)*sqrt(B)*sin(ra+rb);
      SMAX(res,a);
    }
    LL p=sqroot(A),q=sqroot(B);
//    dump2(p,q);
    if(p>0&&q>0) SMAX(res,p*q*0.5);
    if(p>0) FORR(rb,SB) {
      double a=0.5*sqrt(A)*sqrt(B)*sin(rb);
      SMAX(res,a);
    }
    if(q>0) FORR(ra,SA) {
      double a=0.5*sqrt(A)*sqrt(B)*sin(ra);
      SMAX(res,a);
    }
    return res;
  }
};

// CUT begin
ifstream data("MaxTriangle.sample");

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

bool do_test(int A, int B, double __expected) {
    time_t startClock = clock();
    MaxTriangle *instance = new MaxTriangle();
    double __result = instance->calculateArea(A, B);
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
        int A;
        from_stream(A);
        int B;
        from_stream(B);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1536786827;
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
        cout << "MaxTriangle (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
