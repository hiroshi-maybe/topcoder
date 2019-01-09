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
 
 9/3/2018
 
 12:57-13:06 analysis
 13:07-13:21 (161.50 pt)
 
 Clean implementation: http://community.topcoder.com/stat?c=problem_solution&rm=298923&rd=13512&pm=10104&cr=7446789
 
 Summary:
  - Poor implementation. Tons of bugs before submit 😡
   - Wrong distance formula for right points
   - Binary search condition
  - Put absolute position in binary search so that distance between X[i] can be computed directly
 
 */

// 12:57-13:06 analysis
// 13:21 (161.50 pt)
class EquilibriumPoints {
  public:
  int N;
  VI X,M;
  double ok(double x, int p) {
    double lv=0,rv=0;
    double d=x;
    for(int i=p; i>=0; --i) {
//      dump3(i,M[i],d);
      lv+=M[i]/d/d;
      if(i>0)d+=X[i]-X[i-1];
    }
    FOR(i,p+1,N) {
      d=X[i]-x-X[p];
//      dump3(i,M[i],d);
      rv+=M[i]/d/d;
      if(i<N-1)d+=X[i+1]-X[i];
    }
//    dump3(x,lv,rv);
    return lv>=rv;
  }
  // clumsy implementation 👎
  double f_org(int i) {
    double good=1e-10,bad=X[i+1]-X[i];
    REP(_,100) {
      double mid=(good+bad)*0.5;
      (ok(mid,i)?good:bad)=mid;
    }
    return X[i]+good;
  }
  
  double f(int p) {
    double good=X[p],bad=X[p+1];
    REP(_,100) {
      double mid=(good+bad)*0.5;
      
      double x=0;
      REPE(i,p) x-=M[i]/(X[i]-mid)/(X[i]-mid);
      FOR(i,p+1,N) x+=M[i]/(X[i]-mid)/(X[i]-mid);
      (x<0?good:bad)=mid;
    }
    return good;
  }
  
  vector<double> getPoints(vector<int> X, vector<int> M) {
    this->X=X,this->M=M,this->N=SZ(X);
    vector<double> res(N-1);
    REP(i,N-1)res[i]=f(i);
    return res;
  }
};

// CUT begin
ifstream data("EquilibriumPoints.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool double_vector_equal (const vector<double> &expected, const vector<double> &received) {
    if (expected.size() != received.size()) return false;
    int n = expected.size();
    for (int i = 0; i < n; ++i)
        if (!double_equal(expected[i], received[i])) return false;
    return true;
}

bool do_test(vector<int> x, vector<int> m, vector<double> __expected) {
    time_t startClock = clock();
    EquilibriumPoints *instance = new EquilibriumPoints();
    vector<double> __result = instance->getPoints(x, m);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_vector_equal(__expected, __result)) {
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
        vector<int> m;
        from_stream(m);
        next_line();
        vector<double> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, m, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1536004617;
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
        cout << "EquilibriumPoints (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
