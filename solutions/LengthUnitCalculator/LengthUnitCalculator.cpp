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

/**
 
 8/8/2017
 
 8:21-8:36 (197.41 pt)
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+675
 
 23:51 add static transition table solution
 
 23:58 add solution with conversion to canonical unit
  -  1(mi) = 1760(yd) = 1760*3(ft) = 1760*3*12(in)
  - from -> (in) -> to
 
 */

class LengthUnitCalculator {
public:
  unordered_map<string, int> ID = {{"mi",0},{"yd",1},{"ft",2},{"in",3}};
  double T[4] = { 1760.0, 3.0, 12.0, 1.0 };
  double calc(int amount, string fromUnit, string toUnit) {
    double v = amount;
    int from=ID[fromUnit], to=ID[toUnit];
    int u=from;
    while(u<4) v*=T[u++];
    while(u>to) v/=T[--u];
    return v;
  }
};

class LengthUnitCalculator_static_transition {
public:
  unordered_map<string, int> ID = {{"mi",0},{"yd",1},{"ft",2},{"in",3}};
  double T[4][4]={
    {                1.0,       1760.0, 3.0*1760.0, 3.0*12.0*1760.0 },
    {         1.0/1760.0,          1.0,        3.0,        3.0*12.0 },
    {     1.0/1760.0/3.0,      1.0/3.0,        1.0,            12.0 },
    {1.0/1760.0/3.0/12.0, 1.0/3.0/12.0,   3.0/12.0,             1.0 },
  };
  double calc(int amount, string fromUnit, string toUnit) {
    return T[ID[fromUnit]][ID[toUnit]]*amount;
  }
};

class LengthUnitCalculator_org {
  public:
  unordered_set<string> viz;
  double dfs(string cur, string to, double v) {
    if (cur==to) return v;
    viz.insert(cur);
    
    for(auto kvp : M) {
      string f=kvp.first.first, t=kvp.first.second;
      double v2 = kvp.second;
      if (f!=cur) continue;
      if (viz.count(t)) continue;
      double x = dfs(t,to,v*v2);
      if (x!=-1.0) return x;
    }
    return -1.0;
  }
  
  map<pair<string,string>,double>M = { {{"ft","in"},12.0}, {{"yd","ft"},3.0},{{"mi","yd"},1760.0} };
  double calc(int amount, string fromUnit, string toUnit) {
    for(auto kvp : M) {
      string f=kvp.first.first, t=kvp.first.second;
      double v = kvp.second;
      M[{t,f}] = 1.0/v;
    }
    
    return dfs(fromUnit,toUnit,amount);
  }
};

// CUT begin
ifstream data("LengthUnitCalculator.sample");

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

bool do_test(int amount, string fromUnit, string toUnit, double __expected) {
    time_t startClock = clock();
    LengthUnitCalculator *instance = new LengthUnitCalculator();
    double __result = instance->calc(amount, fromUnit, toUnit);
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
        int amount;
        from_stream(amount);
        string fromUnit;
        from_stream(fromUnit);
        string toUnit;
        from_stream(toUnit);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(amount, fromUnit, toUnit, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502205649;
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
        cout << "LengthUnitCalculator (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
