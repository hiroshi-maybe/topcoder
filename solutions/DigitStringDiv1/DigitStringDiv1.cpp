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
#define dumpf(args...) if(TRACE) { fprintf(stdout, ##args); putc('n',stdout); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cout<<*begin<<','; } cout<<endl; } }

/*
 
 11/30/2018 SRM 741
 
 18:00-19:15 submit and hacked
 
 11/5/2018
 
 10:40-11:00 I got another WA after overflow bug fix. I fixed dp transition again. Now topcoder is down 🖕
 
 https://www.topcoder.com/blog/single-round-match-741-editorials/
 
 This seemed to be a problem for digit dp. However this problem is slightly different in some points
 
 1. Digits are picked from `S` instead of 0-9 (data and condition)
 2. We want `greater than` instead of `less than or equal to` (condition)
 
 Those difference confused me. Eventually my solution got very complicated. I couldn't solve during the contest 👎
 
 #1 => We should manage length of prefix of `S` that we evaluated.
 #2 => Flag for two states is not sufficient to represent state. We need three states {<,=,>}.
       State transition is DAG.
 
 Summary:
  - Look at condition and data carefully. Even if you find related problem previously solved, don't rush into it. You may reuse its method or concept. However you should still focus on how to connect data and unknown.
 
 11/6/2018
 
 System test passed
 
 */

// 19:14 (91.16 pt)
const int MAX_N=51;
LL dp[MAX_N][15];
LL dp2[MAX_N][MAX_N][3];
class DigitStringDiv1 {
public:
  long long count(string S, int X) {
    ZERO(dp2);
    int N=SZ(S);
    string T=to_string(X);
    int M=SZ(T);
    REP(i,N) dp2[i][0][1]=1;
    REP(i,N)REP(j,N)REP(st,3) {
      if(j>0)dp2[i+1][j][st]+=dp2[i][j][st];
      if(j==0&&S[i]=='0') continue;
      
      if(j>=M) dp2[i+1][j+1][2]+=dp2[i][j][st];
      else {
        if(st==1) {
          int st2=1;
          if(S[i]<T[j]) st2=0;
          if(S[i]>T[j]) st2=2;
          dp2[i+1][j+1][st2]+=dp2[i][j][st];
        } else {
          dp2[i+1][j+1][st]+=dp2[i][j][st];
        }
      }
    }
    LL res=0;
    FORE(l,M,N) res+=dp2[N][l][2];
    return res;
  }
};

class DigitStringDiv1_org {
  public:
  LL f(string S, string X, int M) {
    ZERO(dp);
    int N=SZ(S),P=SZ(X);
    REP(i,N) dp[i][0]=1;
    REP(i,N)REPE(l,M) {
      if(l<P-1) {
        if(X[l]==S[i]) {
//          if(dp[i][l]) dump3(i,l,dp[i][l]);
          dp[i+1][l+1]+=dp[i][l];
        }
      } else if(l==P-1) {
        if(X[l]<S[i]) {
//          if(dp[i][l]) dump3(i,l,dp[i][l]);
          dp[i+1][l+1]+=dp[i][l];
        }
      } else {
//        if(dp[i][l])dump3(i,l,dp[i][l]);
        dp[i+1][l+1]+=dp[i][l];
      }
      if(l!=0)dp[i+1][l]+=dp[i][l];
    }
    return dp[N][M];
  }
  LL g(string S, string X, int M) {
    ZERO(dp2);
    int N=SZ(S),P=SZ(X);
    assert(P==1);
    REP(i,N) dp2[i][0][0]=1;
    REP(i,N)REP(l,N)REP(st,3) {
      if(l==0) {
        if(S[i]>X[0]) dp2[i+1][l+1][1]+=dp2[i][l][st];
        if(S[i]!='0'&&S[i]<=X[0]) dp2[i+1][l+1][2]+=dp2[i][l][st];
      } else {
        dp2[i+1][l+1][st]+=dp2[i][l][st];
        dp2[i+1][l][st]+=dp2[i][l][st];
      }
    }
    LL res=0;
    FORE(i,M,N) {
      res+=dp2[N][i][1];
//      dump2(i,dp2[N][i][1]);
    }
    FORE(i,M+1,N){
      res+=dp2[N][i][2];
//      dump2(i,dp2[N][i][2]);
    }
    return res;
  }
  long long count(string S, int XX) {
    LL res=0;
    string X=to_string(XX);
    int M=SZ(X);
    FORE(l,1,M) {
//      if(L<=0) continue;
      string x=X.substr(0,l);
      LL a=l==1?g(S,x,M):f(S,x,M);
//      dump4(l,S,x,a);
      res+=a;
    }
    return res;
  }
};

// CUT begin
ifstream data("DigitStringDiv1.sample");

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

bool do_test(string S, int X, long long __expected) {
    time_t startClock = clock();
    DigitStringDiv1 *instance = new DigitStringDiv1();
    long long __result = instance->count(S, X);
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
        string S;
        from_stream(S);
        int X;
        from_stream(X);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, X, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1540947606;
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
        cout << "DigitStringDiv1 (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
