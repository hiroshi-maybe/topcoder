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

/*
 
 11/19/2017
 
 9:47-10:07 analysis
 10:08-10:22 system test passed (516.14 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+584
  - http://emkcsharp.hatenablog.com/entry/SRM584/Excavations2
  - http://torus711.hatenablog.com/entry/20130720/p1
  - https://topcoder.g.hatena.ne.jp/firewood/20130726/1374859460
 
 Key:
  - binomial coefficient DP
  - counting DP
 
 Summary:
  - typical DP
  - good to know that C(n,k) n<=50 does not overflow
   - C(66,33) is maximum in 64-bit signed integer
 
 */

// memoized recursion, O(N^3) time
LL memo[51][51];
LL C[51][51];
class Excavations2_org {
  public:
  VI A,B;
  LL f(int i, int rem) {
    LL &res=memo[i][rem];
    if(res>=0) return res;
    if(i==SZ(B)) return res=(rem==0);
    if(rem==0) return 0;
    res=0;
    int cnt=A[B[i]];
    for(int k=1; k<=rem; ++k) {
      if(cnt<k) continue;
      res+=C[cnt][k]*f(i+1,rem-k);
    }
    return res;
  }
  long long count(vector<int> kind, vector<int> B, int K) {
    MINUS(memo);
    this->B=B;
    REP(i,51) {
      C[i][0]=1LL;
      FOR(j,1,i+1) C[i][j]=C[i-1][j]+C[i-1][j-1];
    }
    VI AA(51,0);
    REP(i,SZ(kind)) ++AA[kind[i]];
    this->A=AA;
    return f(0,K);
  }
};

// iterative dp, O(N^3) time
LL dp[51][51];
class Excavations2 {
public:
  VI A,B;
  long long count(vector<int> kind, vector<int> B, int K) {
    ZERO(dp);
    this->B=B;
    REP(i,51) {
      C[i][0]=1LL;
      FOR(j,1,i+1) C[i][j]=C[i-1][j]+C[i-1][j-1];
    }
    VI AA(51,0);
    REP(i,SZ(kind)) ++AA[kind[i]];
    this->A=AA;
    
    dp[0][0]=1;
    REP(i,SZ(B)) REP(j,K+1) FOR(k,1,K+1) {
      int kind=B[i],cnt=A[kind];
      if(k>cnt) continue;
      dp[i+1][j+k]+=dp[i][j]*C[cnt][k];
    }
    
    return dp[SZ(B)][K];
  }
};

// CUT begin
ifstream data("Excavations2.sample");

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

bool do_test(vector<int> kind, vector<int> found, int K, long long __expected) {
    time_t startClock = clock();
    Excavations2 *instance = new Excavations2();
    long long __result = instance->count(kind, found, K);
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
        vector<int> kind;
        from_stream(kind);
        vector<int> found;
        from_stream(found);
        int K;
        from_stream(K);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(kind, found, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1511113625;
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
        cout << "Excavations2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
