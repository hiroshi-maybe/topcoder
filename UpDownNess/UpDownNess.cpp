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

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

/**
 
 7/20/2017
 
 8:37-9:28 give up
 
 18:00-19:00 read editorials
 - https://www.slideshare.net/hirotakaisa5/srm694
 - http://blog.euphonictech.com/entry/2016/07/17/000146
 - http://kmjp.hatenablog.jp/entry/2016/07/16/1100
 
 21:09-21:19 passed system test by insertion DP 1 to N
 
 22:52-23:25 add solution by insertion DP N to 1
 
 Other solutions
 - memoized recursion
  - https://community.topcoder.com/stat?c=problem_solution&rm=329023&rd=16766&pm=14304&cr=40027652
 - other solutions are bottom-up DP
 
 Keys
 - insertion DP
 - keep invariant `P[i]<P[j]>P[k]` by inserting 1 to N
 
 Summary
 - insertion DP is definitely a new useful pattern
 - think about how to force P[i]<P[j]>P[k] in subproblem
  - two patterns
   - search permutation which satisfies specific condition (P[i]<P[j]>P[k] in this problem)
   - keep invariant without search when splitting to sub-problems
 - don't be confused 1. how many tuples and 2. how many distinct permutations which satisfies specific # of tuples
 - K is larger than N. Iterate k correctly
 - `tuple` (NOT distinct permutation) increases by i*(N-i) when new number `n` is added
 
 */

constexpr int MOD = 1e9+7;
int dp[51][5001];

// O(K*N^2) time, insert from N to 1
class UpDownNess {
public:
  int count(int N, int K) {
    memset(dp, 0, sizeof dp);
    
    dp[0][0]=1;
    REP(i,N) REP(j,N-i) REP(k,K+1) if(k>=j*(N-i-j-1)) dp[i+1][k]+=dp[i][k-j*(N-i-j-1)], dp[i+1][k]%=MOD;
    return dp[N][K];
  }
};

// O(K*N^2) time, insert from 1 to N
class UpDownNess_org {
  public:
  int count(int N, int K) {
    memset(dp, 0, sizeof dp);
    
    dp[0][0]=1;
    REP(n,N) {
      REP(i,n+1) {
        REP(k,K+1) if(k>=i*(n-i)) {
          dp[n+1][k]+=dp[n][k-i*(n-i)], dp[n+1][k]%=MOD;
        }
      }
    }
    
    return dp[N][K];
  }
};

// CUT begin
ifstream data("UpDownNess.sample");

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

bool do_test(int N, int K, int __expected) {
    time_t startClock = clock();
    UpDownNess *instance = new UpDownNess();
    int __result = instance->count(N, K);
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
        int N;
        from_stream(N);
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500565051;
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
        cout << "UpDownNess (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
