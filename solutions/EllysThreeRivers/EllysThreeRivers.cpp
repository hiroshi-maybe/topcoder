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
 
 1/29/2018
 
 9:34-10:00 pause
 17:50-18:15 give up
 18:16-18:47 read editorials
 18:48-19:01 implement and ACC
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+543
    - Nice to see proof of nested ternary search (composition of three convex function) 👍
  - http://kmjp.hatenablog.jp/entry/2014/01/04/0900
 
 Graph:
  - http://www.wolframalpha.com/input/?i=x%2F8+%2B+sqrt((10–x)%5E2+%2B5%5E2)%2F5
 
 Convex function calculus:
  - https://en.wikipedia.org/wiki/Convex_function#Convex_function_calculus
  - Nice to learn below properties:
   - f(x)+g(x) or max(f(x),g(x)) is convex function if f and g are convex ✅
   - g(f(x)) is convex if f and g are convex nad g is non-decreasing ✅
 
 Key:
  - sqrt(a+x^2) forms downward-convex function
  - pin each condition one by one and do nested ternary search
 
 Summary:
  - I had search idea by fixing some of distances though, I didn't have any idea about graph shape
  - Nice to learn that sqrt(a+x^2) forms downward-convex function
  - First time to see nested binary/ternary search
  - Solving simpler problem (1 river in this problem) is a good start
 
 */
class EllysThreeRivers {
  public:
  VI W,S;
  double S1;
  
  double time(int i, double d) {
    //return sqrt(1.0*W[i]*W[i]+1.0*d*d)/(1.0*S[i]);
    return hypot(W[i],d)/(1.0*S[i]);
  }
  double f(int i, double rem) {
    if(i>=3) return rem/S1;
    
    double res=1e5;
    double l=0,r=rem;
    REP(_,100) {
      double ll=l+(r-l)/3.0;
      double rr=r-(r-l)/3.0;
      
      double a=time(i,ll)+f(i+1,rem-ll),b=time(i,rr)+f(i+1,rem-rr);
      res=min({res,a,b});
      if(a<b) r=rr;
      else l=ll;
    }
    return res;
  }
  
  double getMin(int L, int S1, vector<int> W, vector<int> S) {
    this->W=W,this->S=S,this->S1=S1;
    return f(0,L);
  }
};

// CUT begin
ifstream data("EllysThreeRivers.sample");

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

bool do_test(int length, int walk, vector<int> width, vector<int> swim, double __expected) {
    time_t startClock = clock();
    EllysThreeRivers *instance = new EllysThreeRivers();
    double __result = instance->getMin(length, walk, width, swim);
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
        int length;
        from_stream(length);
        int walk;
        from_stream(walk);
        vector<int> width;
        from_stream(width);
        vector<int> swim;
        from_stream(swim);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(length, walk, width, swim, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1517247241;
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
        cout << "EllysThreeRivers (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
