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
 
 7/30/2017
 
 13:58-14:38 give up
 
 15:56-16:45 Read editorial
 - https://apps.topcoder.com/wiki/display/tc/SRM+684
 - http://ry0u.github.io/blog/2016/03/15/srm684d2m-divfreed2/
 - http://kmjp.hatenablog.jp/entry/2016/03/09/1000
 
 16:45-17:26 add solution and passed system test
 
 Key
 - convert two conditions to one condition
  - A<=B OR A%B!=0
   1. B is NOT A's divisor
   2. BUT A itself is OK
 - modulo condition
  - A%B!=0
   - B is not divisor of A
   - B does not divide A
   - B !| A
 - Figure out that divisor matters. Then DP is straightforward
 - Inclusive-exclusive principle
 
 summary
 - MISUNDERSTOOD PROBLEM STATEMENT TWICE. READ AND UNDERSTAND PROBLEM CAREFULLY.
 - Analysis was totally messed up. Write down some examples and understand the constraint especially in numeric problem!
 
 */

VI DIV[100001];
LL dp[100001];

constexpr int MOD = 1e9+7;
class DivFreed2 {
  public:
  int count(int N, int K) {
    memset(dp, 0, sizeof dp);
    REP(i,K+1) DIV[i].clear();
    
    FOR(p,1,K+1) {
      int q=p+p;
      while(q<=K) {
        DIV[q].push_back(p);
        q+=p;
      }
    }
    
    FOR(x,1,K+1) dp[x]=1;
    LL sum=K;
    REP(i,N-1) {
      LL sum2=0;
      for(int j=K; j>=1; --j) {
        LL x=0;
        FORR(p,DIV[j]) (x+=dp[p])%=MOD;
        (dp[j]=sum+MOD-x)%=MOD;
        (sum2+=dp[j])%=MOD;
      }
      sum=sum2;
    }
    
    LL res=0;
    FOR(j,1,K+1) (res+=dp[j])%=MOD;
    return res;
  }
};

// CUT begin
ifstream data("DivFreed2.sample");

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

bool do_test(int n, int k, int __expected) {
    time_t startClock = clock();
    DivFreed2 *instance = new DivFreed2();
    int __result = instance->count(n, k);
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
        int n;
        from_stream(n);
        int k;
        from_stream(k);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501448306;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "DivFreed2 (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
