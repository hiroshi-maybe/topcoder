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
#define MAXS(a,b) a = max(a,b)
#define MINS(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 1/26/2018
 
 8:26-8:45 analysis
 8:45-8:53 implement and submit (300.14 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+547
  - http://kg86.hatenablog.com/entry/20130819/1376907566
  - http://topcoder.g.hatena.ne.jp/agw/20120701/1341109310
  - http://d.hatena.ne.jp/kusano_prog/20120629/1340989286
 
 O(N) solution suggested in editorial:
 
 Suppose that below heights:
 
 1) [a+b+1,b+1,1]
   Total length of rope f(A1) = sqrt(a^2+w^2)+sqrt(b^2+w^2)
 2) [a+b+1,1,1]
   Total length of rope f(A2) = sqrt( (a+b)^2+w^2 )

 It's possible to show f(A1)<=f(A2). So we take only H[i] or 1.
 Now DP is simpler by keeping state true/false which shows H[i] or 1.
 
 18:55 add O(N) solution
 
 Key:
  - H[i] is small. DP works.
 
 Summary:
  - I tried to go through greedy though, fell back to dp
 
 */

// dp, O(N) time
class PillarsDivTwo {
public:
  double dp[50][2];
  double maximalLength(vector<int> H, int W) {
    int N=SZ(H);
    ZERO(dp);
    FOR(i,1,N) REP(x1,2) REP(x2,2) {
      double h1=x1==0?1:H[i-1],h2=x2==0?1:H[i];
      MAXS(dp[i][x2],dp[i-1][x1]+hypot(h1-h2,W));
    }
    return max(dp[N-1][0],dp[N-1][1]);
  }
};

// dp, O(N*H^2) time
double dp[50][100];
class PillarsDivTwo_org {
  public:
  double W;
  double area(int h1, int h2) {
//    return sqrt(pow(abs(h1-h2),2)+pow(W,2));
    return hypot(h1-h2,W);
  }
  double maximalLength(vector<int> H, int W_) {
    this->W=W_;
    int N=SZ(H);
    ZERO(dp);
    FOR(i,1,N) FORE(h1,1,H[i-1]) FORE(h2,1,H[i]) {
      MAXS(dp[i][h2],dp[i-1][h1]+area(h1,h2));
    }
    double res=0;
    FORE(h,1,H.back()) MAXS(res,dp[N-1][h]);
    return res;
  }
};

// CUT begin
ifstream data("PillarsDivTwo.sample");

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

bool do_test(vector<int> height, int w, double __expected) {
    time_t startClock = clock();
    PillarsDivTwo *instance = new PillarsDivTwo();
    double __result = instance->maximalLength(height, w);
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
        vector<int> height;
        from_stream(height);
        int w;
        from_stream(w);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(height, w, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1516983982;
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
        cout << "PillarsDivTwo (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
