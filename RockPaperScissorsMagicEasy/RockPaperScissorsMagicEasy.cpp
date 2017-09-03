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

constexpr int MOD = 1e9+7;

/*
 
 9/3/2017
 
 17:44-18:06 system test passed (333.83 pt)

 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+653
  - http://kmjp.hatenablog.jp/entry/2015/03/20/0930
 
 res = C(N,s) * 2^(n-s)
 
 12:10-12:35 add solution without DP
 
 key:
  - card doesn't matter
 
 summary:
  - due to typo, I wasted 10 mins to debug :(
 
 submit solutions:
  - dp
   - https://community.topcoder.com/stat?c=problem_solution&rm=325561&rd=16317&pm=13686&cr=23308488
   - https://community.topcoder.com/stat?c=problem_solution&rm=325571&rd=16317&pm=13686&cr=40127362
   - https://community.topcoder.com/stat?c=problem_solution&rm=325555&rd=16317&pm=13686&cr=40134070
   - https://community.topcoder.com/stat?c=problem_solution&rm=325561&rd=16317&pm=13686&cr=23081646
 
 */

LL powmod(int a, int n) {
  LL base=a,res=1;
  while(n>0) {
    if(n&1) res*=base,res%=MOD;
    base*=base,base%=MOD;
    n>>=1;
  }
  return res;
}

LL C[2001][2001];
class RockPaperScissorsMagicEasy {
public:
  int count(vector<int> cards, int s) {
    ZERO(C);
    int N=SZ(cards);
    REP(i,N+1) {
      C[i][0]=1;
      FOR(j,1,i+1) (C[i][j]=C[i-1][j]+C[i-1][j-1])%=MOD;
    }
    return (C[N][s]*powmod(2,N-s))%MOD;
  }
};

LL dp[2005][2005];
class RockPaperScissorsMagicEasy_dp {
  public:
  int count(vector<int> C, int score) {
    ZERO(dp);
    int N=SZ(C);
    dp[0][0]=1LL;
    REP(i,N+2) REP(p,score+2) if(dp[i][p]>0) {
      (dp[i+1][p+1]+=dp[i][p])%=MOD;
      (dp[i+1][p]+=2*dp[i][p])%=MOD;
    }
    return dp[N][score];
  }
};

// CUT begin
ifstream data("RockPaperScissorsMagicEasy.sample");

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

bool do_test(vector<int> card, int score, int __expected) {
    time_t startClock = clock();
    RockPaperScissorsMagicEasy *instance = new RockPaperScissorsMagicEasy();
    int __result = instance->count(card, score);
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
        vector<int> card;
        from_stream(card);
        int score;
        from_stream(score);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(card, score, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1504399458;
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
        cout << "RockPaperScissorsMagicEasy (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
