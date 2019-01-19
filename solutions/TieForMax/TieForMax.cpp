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
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stdout, ##args); putc('\n',stdout); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cout<<*begin<<','; } cout<<endl; } }

/*
 
 1/19/2019
 
 9:26-11:12 AC (201.70 pt)
 
 https://twishort.com/Ekunc
 https://twitter.com/torus711/status/1086679690180317185
 
 Binary distribution
  - https://mathtrain.jp/bin
 
 */

// 10:26-11:12 (201.70 pt)
void choose(LL N, vector<vector<double>> &C) {
  for(int i=0; i<=N; ++i) {
    C[i][0]=1;
    for(int j=1; j<=i; ++j) {
      // i chooses j
      C[i][j] = C[i-1][j]+C[i-1][j-1];
    }
  }
}
double dp[51][51][51][3];
double PW[101];
class TieForMax_org {
  public:
  double getProbability(int T, int P) {
    VV<double> C(51,vector<double>(51,0));
    choose(50,C);
    PW[0]=1; REP(i,100) PW[i+1]=PW[i]*P;
    ZERO(dp);
    dp[0][T][0][0]=1.0;
    REP(i,P)REPE(j,T)REPE(k,T)REP(l,2) {
      REPE(x,j) {
        double p=C[j][x]/PW[x];
        if(x>k) dp[i+1][j-x][x][1]+=dp[i][j][k][l]*p;
        else dp[i+1][j-x][k][l&(x<k)]+=dp[i][j][k][l]*p;
      }
    }
    
    double res=0;
    REPE(i,T) res+=dp[P][0][i][1];
    return 1.0-res;
  }
};

class TieForMax {
public:
  double getProbability(int T, int P) {
    VV<double> C(51,vector<double>(51,0));
    choose(50,C);
    PW[0]=1; REP(i,100) PW[i+1]=PW[i]*P;
    ZERO(dp);
    dp[0][T][0][0]=1.0;
    REP(i,P)REPE(j,T)REPE(k,T)REP(l,3) {
      REPE(x,j) {
        double p=C[j][x]/PW[x];
        int cnt=l;
        if(x>k) cnt=1;
        else if(x==k) cnt=min(2,cnt+1);
        dp[i+1][j-x][max(x,k)][cnt]+=p*dp[i][j][k][l];
      }
    }
    
    double res=0;
    REPE(i,T) res+=dp[P][0][i][2];
    return res;
  }
};

// CUT begin
ifstream data("TieForMax.sample");

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

bool do_test(int t, int p, double __expected) {
    time_t startClock = clock();
    TieForMax *instance = new TieForMax();
    double __result = instance->getProbability(t, p);
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
        int t;
        from_stream(t);
        int p;
        from_stream(p);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(t, p, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1547922345;
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
        cout << "TieForMax (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
