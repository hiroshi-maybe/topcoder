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
 
 12/17/2017
 
 13:16-13:45 analysis
 13:46-14:00 1WA (459.63 pt)
 14:00-14:33 fix overflow bug and save memory by converting to iterative DP. System test passed.
 
 My solution:
 
 DP state for (N,K) is 10^5.
 If we can count all the primes for N!K by going throug the states by DP,
 Result is ∏ { count(p)+1 : p is prime number which is part of N!K }
 
 Thus we can compute result in following steps:
   1) Pre-compute prime factorization of n=2..1000 in O(N*√N) time ≈3*10^4
   2) By DP compute number of primes f(N,K) s.t. f(N,K) = number of primes of N!K in O(N*K*pi(N)) time
    f(0,k)={}
    f(n,0)= result of prime factorization precomputed in step 1
    f(n,k)=merge(f(n-1,k), f(n,k-1)) in O(pi(N)) time
   3) Compute ∏ { count(p)+1 } in O(pi(N)) time
 
 Runtime = O(N*√N+N*K*pi(N)+pi(N)) = O(N*√N+N*K*pi(N)) time <2*10^7
 Note that pi(N)<169 for N<=1000
 
 prime counting function pi(n):
  - https://en.wikipedia.org/wiki/Prime-counting_function
  - https://primes.utm.edu/howmany.html
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+569
   - O(N*K) solution
   - This needs very deep observation of how formula is expanded
  - http://kmjp.hatenablog.jp/entry/2013/02/11/1000
  - http://topcoder.g.hatena.ne.jp/kagamiz/20130207
 
 Summary:
  - It took 30 mins to resolve overflow bug and MLE error
 
 */
typedef map < int, LL > MAPII;
MAPII primef(int n) {
  MAPII res;
  for(int p=2; p*p<=n; ++p) {
    while(n%p==0) res[p]++,n/=p;
  }
  if(n>1) res[n]++;
  return res;
}

// dp, O(N*K*pi(N)) time, O(N*pi(N)) space
// pi(N) is prime-counting function of N (pi(N)<=168 if N<=1000)
constexpr int MOD = 1e9+9;
MAPII dp[2][101];
MAPII M[1001];
class MegaFactorialDiv2 {
public:
  int countDivisors(int N, int K) {
    for(int i=2; i<=N; ++i) M[i]=primef(i);
    REP(n,N+1) {
      int nn=n%2;
      REP(k,K+1) {
        dp[nn][k].clear();
        if(n==0) dp[nn][k]={};
        else if (k==0) dp[nn][k]=M[n];
        else {
          auto m1=dp[nn][k-1],m2=dp[nn^1][k];
          FORR(kvp,m1) (dp[nn][k][kvp.first]+=kvp.second)%=MOD;
          FORR(kvp,m2) (dp[nn][k][kvp.first]+=kvp.second)%=MOD;
        }
      }
    }
    
    MAPII F=dp[N%2][K];
    
    LL res=1;
    //    dump(SZ(F));
    FORR(kvp,F) if(kvp.first>1) {
//      dump2(kvp.first,kvp.second);
      res*=(1LL+(LL)kvp.second),res%=MOD;
    }
    return res;
  }
};

// MLE
MAPII memo[1001][101];
class MegaFactorialDiv2_mle {
  public:
  MAPII f(int n, int k) {
    if(SZ(memo[n][k])) return memo[n][k];
    MAPII res;
    if(n==0) res[1]=1;
    else if(k==0) res=M[n];
    else {
      auto m1=f(n,k-1),m2=f(n-1,k);
      FORR(kvp,m1) res[kvp.first]+=kvp.second,res[kvp.first]%=MOD;
      FORR(kvp,m2) res[kvp.first]+=kvp.second,res[kvp.first]%=MOD;
    }
    return memo[n][k]=res;
  }
  int countDivisors(int N, int K) {
    REP(i,N+1)REP(j,K+1) memo[i][j].clear();
    for(int i=2; i<=N; ++i) M[i]=primef(i);
    MAPII F=f(N,K);
    
    LL res=1;
//    dump(SZ(F));
    FORR(kvp,F) if(kvp.first>1) {
//      dump2(kvp.first,kvp.second);
      res*=(1LL+(LL)kvp.second),res%=MOD;
    }
    return res;
  }
};

// CUT begin
ifstream data("MegaFactorialDiv2.sample");

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
    MegaFactorialDiv2 *instance = new MegaFactorialDiv2();
    int __result = instance->countDivisors(N, K);
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
        int T = time(NULL) - 1513545402;
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
        cout << "MegaFactorialDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
