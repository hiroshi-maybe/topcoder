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
 
 6/9/2018
 
 23:50-24:10 pause
 
 6/11/2018
 
 10:25-10:50 give up
 11:00-12:47 read editorials and add solution
 
 Editorials:
  - http://suikaba.hatenablog.com/entry/2017/08/24/224445
  - http://kmjp.hatenablog.jp/entry/2017/08/27/0900
  - http://fluffyowl.hatenablog.com/entry/2017/09/29/225844
  - https://ei1333.hateblo.jp/entry/2017/08/25/010750
  - https://kimiyuki.net/writeup/algo/topcoder/srm-720-easy/
  - http://hamko.hatenadiary.jp/entry/2017/10/04/140759
 
 Tweets:
  - https://togetter.com/li/1143543
 
 Independnece of each column must be leveraged.
 Suppose digit `x` is at `i`-th in A and `y` is at `j`-th in B.
 
 res = ∑ { x*10^i*y*10^j*f(x,y) : i=0..N1-1, j=0..N2-1, x∈D, y∈D }
 
 f(x,y) can be solved by dp(# of candidate digits from 0 to 9, # of determined columns)
 
 dp[i+1][j+k] = dp[i][j] * C(N1+N2-2-j,k)
 f(x,y) = dp[10][N1+N2-2]
 
 Key:
  - Fix two digits first for A and B respectively
  - Position of fixed digits does not matter to count possible patterns (=f(x,y))
 
 Summary:
  - Very tough problem for Div1 easy
  - I couldn't reduce problem to subproblem of i-th `x` and j-th `y`
  - Fixing one digit and computing is popular in counting problem as seen in recent CSA problem
   - https://github.com/k-ori/csacademy/blob/master/solutions/AllNumbers.cpp
  - If permutation or binomial coefficient seems to be related, dp may be a good choice
 
 */
const LL MOD=1e9+7;
const int MAX_N=200;
LL P10[MAX_N+1];
LL C[MAX_N+1][MAX_N+1];
LL dp[11][MAX_N+1];
class SumProduct {
  public:
  int findSum(vector<int> D, int N1, int N2) {
    P10[0]=1LL;
    REP(i,MAX_N) (P10[i+1]=P10[i]*10LL)%=MOD;
    REPE(i,MAX_N) {
      C[i][0]=1;
      FORE(j,1,i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
    }
    LL res=0;
    REP(d1,10)REP(d2,10) {
      D[d1]--,D[d2]--;
      if(D[d1]>=0&&D[d2]>=0) {
        ZERO(dp);
        dp[0][0]=1LL;
        int L=N1+N2-2;
        REP(i,10) REPE(j,L) REPE(k,D[i]) if(j+k<=L) {
          LL a=dp[i][j]*C[L-j][k]%MOD;
          (dp[i+1][j+k]+=a)%=MOD;
        }
        REP(i,N1)REP(j,N2) {
          LL a=P10[i]*d1%MOD,b=P10[j]*d2%MOD;
          res+=a*b%MOD*dp[10][L]%MOD,res%=MOD;
        }
      }
      D[d1]++,D[d2]++;
    }
    return res;
  }
};

// CUT begin
ifstream data("SumProduct.sample");

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

bool do_test(vector<int> amount, int blank1, int blank2, int __expected) {
    time_t startClock = clock();
    SumProduct *instance = new SumProduct();
    int __result = instance->findSum(amount, blank1, blank2);
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
        vector<int> amount;
        from_stream(amount);
        int blank1;
        from_stream(blank1);
        int blank2;
        from_stream(blank2);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(amount, blank1, blank2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1528555826;
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
        cout << "SumProduct (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
