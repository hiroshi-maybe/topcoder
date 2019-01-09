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
 
 1/28/2018
 
 17:23-18:08 understand problem and example
 18:08-18:14 analysis
 18:14-18:21 implement and system test passed (380.83 pt)
 
 Editorials:
  - http://apps.topcoder.com/wiki/display/tc/SRM+544
  - http://kmjp.hatenablog.jp/entry/2014/01/02/1130
  - http://area.hateblo.jp/entry/2013/10/28/040141
 
 Summary:
  - Problem statement and samples were not clear 👎
   - 45 mins to understand problem and sample, 13 mins to analyze and implement
 
 */
LL dp[51][51][51][51];
constexpr long long MOD = 1e9+7;
class AliceBobShuffle {
  public:
  int countWays(vector<int> A1, vector<int> B1, vector<int> A2, vector<int> B2) {
    ZERO(dp);
    dp[0][0][0][0]=1;
    int NA1=SZ(A1),NB1=SZ(B1),NA2=SZ(A2),NB2=SZ(B2);
    REPE(a1,NA1)REPE(b1,NB1)REPE(a2,NA2)REPE(b2,NB2) if(dp[a1][b1][a2][b2]) {
      if(a1<NA1&&a2<NA2&&A1[a1]==A2[a2]) (dp[a1+1][b1][a2+1][b2]+=dp[a1][b1][a2][b2])%=MOD;
      if(a1<NA1&&b2<NB2&&A1[a1]==B2[b2]) (dp[a1+1][b1][a2][b2+1]+=dp[a1][b1][a2][b2])%=MOD;
      if(b1<NB1&&a2<NA2&&B1[b1]==A2[a2]) (dp[a1][b1+1][a2+1][b2]+=dp[a1][b1][a2][b2])%=MOD;
      if(b1<NB1&&b2<NB2&&B1[b1]==B2[b2]) (dp[a1][b1+1][a2][b2+1]+=dp[a1][b1][a2][b2])%=MOD;
    }
    return dp[NA1][NB1][NA2][NB2];
  }
};

// CUT begin
ifstream data("AliceBobShuffle.sample");

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

bool do_test(vector<int> AliceStart, vector<int> BobStart, vector<int> AliceEnd, vector<int> BobEnd, int __expected) {
    time_t startClock = clock();
    AliceBobShuffle *instance = new AliceBobShuffle();
    int __result = instance->countWays(AliceStart, BobStart, AliceEnd, BobEnd);
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
        vector<int> AliceStart;
        from_stream(AliceStart);
        vector<int> BobStart;
        from_stream(BobStart);
        vector<int> AliceEnd;
        from_stream(AliceEnd);
        vector<int> BobEnd;
        from_stream(BobEnd);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(AliceStart, BobStart, AliceEnd, BobEnd, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1517188994;
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
        cout << "AliceBobShuffle (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
