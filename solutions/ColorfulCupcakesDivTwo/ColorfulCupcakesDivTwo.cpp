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
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 1/13/2018
 
 23:28-23:34 analysis
 23:35-23:55 implement and ACC (561.02 pt)
 
 1/14/2018

 Read editorials and add simpler solution
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+551
  - http://d.hatena.ne.jp/anta1/20120805/1344133054
  - http://kmjp.hatenablog.jp/entry/2013/12/28/1000
  - http://d.hatena.ne.jp/kusano_prog/20120804/1344110701
  - http://area.hateblo.jp/entry/2013/12/17/013250
 
 Summary:
  - 5 mins delay of implementation due to boundary bug 👎
 
 */
const LL MOD=1000000007;
LL dp[51][51][51][3];
class ColorfulCupcakesDivTwo {
  public:
  int N;
  int A,B,C;
  LL solve(int x0) {
    ZERO(dp);
    dp[x0==0][x0==1][x0==2][x0]=1;
    /*
    if(x0==0) dp[1][0][0][0]=1;
    else if(x0==1) dp[0][1][0][1]=1;
    else dp[0][0][1][2]=1;
     */
    
    REPE(a,A) REPE(b,B) REPE(c,C) REP(x,3) if(dp[a][b][c][x]) {
      dump3(a,b,c);
      dump2(x,dp[a][b][c][x]);
      if(x!=0) (dp[a+1][b][c][0]+=dp[a][b][c][x])%=MOD;
      if(x!=1) (dp[a][b+1][c][1]+=dp[a][b][c][x])%=MOD;
      if(x!=2) (dp[a][b][c+1][2]+=dp[a][b][c][x])%=MOD;
      /*
      if(x==0) {
        (dp[a][b+1][c][1]+=dp[a][b][c][x])%=MOD;
        (dp[a][b][c+1][2]+=dp[a][b][c][x])%=MOD;
      } else if(x==1) {
        (dp[a+1][b][c][0]+=dp[a][b][c][x])%=MOD;
        (dp[a][b][c+1][2]+=dp[a][b][c][x])%=MOD;
      } else {
        (dp[a+1][b][c][0]+=dp[a][b][c][x])%=MOD;
        (dp[a][b+1][c][1]+=dp[a][b][c][x])%=MOD;
      }*/
    }
//    dump3(x0,(x0+1)%3,(x0+2)%3);
//    dump2(dp[A][B][C][(x0+1)%3],dp[A][B][C][(x0+2)%3]);
    return (dp[A][B][C][(x0+1)%3]+dp[A][B][C][(x0+2)%3])%MOD;
  }
  int countArrangements(string X) {
    this->N=SZ(X);
    this->A=count(X.begin(),X.end(),'A');
    this->B=count(X.begin(),X.end(),'B');
    this->C=count(X.begin(),X.end(),'C');

    dump3(A,B,C);
    LL res=0;
    REP(i,3) res+=solve(i),res%=MOD;
    return res;
  }
};

// CUT begin
ifstream data("ColorfulCupcakesDivTwo.sample");

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

bool do_test(string cupcakes, int __expected) {
    time_t startClock = clock();
    ColorfulCupcakesDivTwo *instance = new ColorfulCupcakesDivTwo();
    int __result = instance->countArrangements(cupcakes);
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
        string cupcakes;
        from_stream(cupcakes);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(cupcakes, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515914887;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 950 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ColorfulCupcakesDivTwo (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
