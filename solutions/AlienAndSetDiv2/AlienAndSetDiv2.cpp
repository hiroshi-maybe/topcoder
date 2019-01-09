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
 
 10/27/2017
 
 9:27-10:15 pause
 18:10-18:34 give up
 18:35-18:59 read editorial
  - http://kmjp.hatenablog.jp/entry/2014/01/22/1000
   - keeping |A| and |B| separatedly
   - implementation is a bit verbose
  - https://apps.topcoder.com/wiki/display/tc/SRM+605
   - reducing state leveraging symmetry property
   - canceling bit in matching. it simplifies code much.
 
 19:00-20:28 sysmte test passed after fixing tons of bugs

 Key:
  - K is small
  - Recent K matches give us enough information to check if adding x to A or B is invalid
 
 Summary:
  - just a bit DP. K IS SMALL 👎
   - I always miss to leverage small size constraint
  - I didn't have idea to keep both size of sets A and B
  - tons of bug in implementation
   - boundary condition K+1
   - +1 not &1
   - wrong check of A[i] and B[i]
 
 */

// O(N^2*K*2^K) time
constexpr int MOD = 1e9+7;
LL dp[51][51][1<<10];
class AlienAndSetDiv2 {
  public:
  int getNumber(int N, int K) {
    ZERO(dp);
    dp[0][0][0]=1;
    int fmask=(1<<K)-1;
    REP(A,N+1) REP(B,N+1) REP(mask,1<<K) if(dp[A][B][mask]) {
      int mask2=(mask<<1)&fmask;
      int n=A+B+1;

      // A
      bool ok=A>=B;
      if(!ok) {
        int BB=B,b=n;
        REP(i,K+1) {
          --b;
          if((mask&(1<<i))==0) {
            if(A==--BB) break;
          }
        }
        ok=n-b<=K;
      }
      if(ok&&A+1<=N) (dp[A+1][B][mask2+1]+=dp[A][B][mask])%=MOD;
      
      // B
      ok=B>=A;
      if(!ok) {
        int AA=A,a=n;
        REP(i,K+1) {
          --a;
          if(mask&(1<<i)) {
            if(B==--AA) break;
          }
        }
        ok=n-a<=K;
      }
      if(ok&&B+1<=N) (dp[A][B+1][mask2]+=dp[A][B][mask])%=MOD;
    }
    
    LL res=0;
    REP(mask,1<<K) res+=dp[N][N][mask],res%=MOD;
    return res;
  }
};

// CUT begin
ifstream data("AlienAndSetDiv2.sample");

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
    AlienAndSetDiv2 *instance = new AlienAndSetDiv2();
    int __result = instance->getNumber(N, K);
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
        int T = time(NULL) - 1509121645;
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
        cout << "AlienAndSetDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
