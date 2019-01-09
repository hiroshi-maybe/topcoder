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
 
 3/19/2018
 
 8:30-8:39 analysis
 8:40-8:43 ACC (426.76 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+509
  - http://purple-jwl.hatenablog.com/entry/20130329/1364549085
  - http://d.hatena.ne.jp/kusano_prog/20110608/1307540396
  - http://tatuyan-edson.blogspot.com/2011/06/topcoder-srm509div2.html
  - http://topcoder.g.hatena.ne.jp/firewood/20110618
 
 Informal proof why element shows up 2^(N-1) times.
 Suppose we have S = {1,2,3,4} and want to know how many times `1` shows up.
 1 is mandatory in the subset of S. So wanting set S' is below:
 
 S' = {1} ∪ PowerSet({2,3,4})
 
 Thus |S'| = |PowerSet({2,3,4})| = 2^3
 
 Generally |S'| = |PowerSet(S - {x})| = 2^(N-1)
 
 20:47-20:49 add simpler solution
 
 Summary:
  - I quickly figured out 10^x%9=1 property. Implementation could be cleaner.
  - I didn't have proof of 2^(N-1) before submit though, now I get it.
  - x*2^n <=> x<<=n and proof of 2^(N-1) are good to know.
 
 */

class LuckyRemainder {
public:
  int getLuckyRemainder(string X) {
    LL res=0;
    int N=SZ(X);
    REP(i,N) res+=X[i]-'0';
    res<<=(N-1);
    return res%9;
  }
};

class LuckyRemainder_org {
  public:
  int getLuckyRemainder(string X) {
    int pow2[55]={};
    pow2[0]=1;
    REP(i,55) pow2[i+1]=(pow2[i]*2)%9;
    int res=0;
    int N=SZ(X);
    REP(i,N) {
      int d=X[i]-'0';
      res+=d*pow2[N-1],res%=9;
    }
    return res;
  }
};

// CUT begin
ifstream data("LuckyRemainder.sample");

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

bool do_test(string X, int __expected) {
    time_t startClock = clock();
    LuckyRemainder *instance = new LuckyRemainder();
    int __result = instance->getLuckyRemainder(X);
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
        string X;
        from_stream(X);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(X, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1521473446;
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
        cout << "LuckyRemainder (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
