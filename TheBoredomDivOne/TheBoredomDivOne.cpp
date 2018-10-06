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
 
 10:52-11:05 analysis
 11:16 precision error
 11:18 AC
 
 http://apps.topcoder.com/wiki/display/tc/SRM+488
 This is solving by recurrence relation. Recurrence relation is also a good option to solve expectation of infinite sequence.
 
     f(x) = p0*f(x) + p1*f(x+1) + p2*f(x+2) + 1
 <=> f(x) = (p1*f(x+1) + p2*f(x+2) + 1)/(1-p0), f(N+M)=0,f(N+M+1)=0, res=f(N)
 
 p0 = C(x,2)/C(N+M,2), p1=x*(N+M-x)/C(N+M,2), p2=C(N+M-x,2)/C(N+M,2)
 
 Summary:
  - I wasted several minutes due to missing *0.5 in counting. Keep in mind that you are counting ordered combination or not 😡
  - Precision error again 😡
 
 */
double memo[100];
class TheBoredomDivOne {
public:
  int N,M;
  double f(int x) {
    if(x>=N+M) return 0;
    double &res=memo[x];
    if(res>=0) return res;
    double p0=1.0*x*(x-1)/(N+M)/(N+M-1);
    double p1=2.0*x*(N+M-x)/(N+M)/(N+M-1);
    double p2=1.0*(N+M-x)*(N+M-x-1)/(N+M)/(N+M-1);
    res=(p1*f(x+1)+p2*f(x+2)+1)/(1.0-p0);
    return res;
  }
  double find(int N, int M) {
    this->N=N,this->M=M;
    MINUS(memo);
    return f(N);
  }
};

double dp[10001][50];
class TheBoredomDivOne_org {
  public:
  double find(int N, int M) {
    ZERO(dp);
    dp[0][0]=1.0;
    double P=(N+M)*(N+M-1)*0.5;
    REP(i,10000) REP(x,M) {
      int n1=N+x,n0=N+M-n1;
      if(x+2<=M) dp[i+1][x+2]+=n0*(n0-1)*0.5/P*dp[i][x];
      if(x+1<=M) dp[i+1][x+1]+=n0*n1/P*dp[i][x];
      dp[i+1][x]+=n1*(n1-1)*0.5/P*dp[i][x];
    }
    double res=0;
    REPE(n,10000) res+=n*dp[n][M];
    return res;
  }
};

// CUT begin
ifstream data("TheBoredomDivOne.sample");

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

bool do_test(int n, int m, double __expected) {
    time_t startClock = clock();
    TheBoredomDivOne *instance = new TheBoredomDivOne();
    double __result = instance->find(n, m);
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
        int n;
        from_stream(n);
        int m;
        from_stream(m);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, m, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1538848311;
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
        cout << "TheBoredomDivOne (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
