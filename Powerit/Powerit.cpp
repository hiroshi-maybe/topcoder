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

LL MOD=1e9+7;

// CLRS 31.6
// compute (a^b) `mod` 1e9+7
// O(lg b)
LL powmod(LL a, LL b) {
  assert(0<=a && a<MOD);
  assert(0<=b);
  
  LL res=1;
  for(LL mask=1; mask<=b; mask<<=1) {
    if(b&mask) res*=a, res%=MOD;
    a*=a; a%=MOD;
  }
  return res;
}

/*
 
 8/27/2017
 
 16:37-16:52 samples passed though, TLE for 1000000,400,1000000000 (7.75 sec)
  - O(N*K) trivial repeated squaring
 17:00 pause
 19:06 look at editorial approach
  - http://kmjp.hatenablog.jp/entry/2015/06/04/0930
 19:30 implement DP by divisor though still TLE for 1000000,400,1000000000 (2.02 sec)
 19:39 system test passed after fixing a bug. recomputation was happening when x mod M == 0 1000000,400,1000000000 (0.96 sec)
 
 If we apply repeated squaring to every number, runtime is O(K*N) K is at most 400.
 However number of divisor of 10^6 is at most 256 from highly composit number
  - http://wwwhomes.uni-bielefeld.de/achim/highly.txt
 Also we know that half of numbers are even. we get result of at least 50% of numbers immediately by f(2)*f(p/2)
 Thus using divisor is more efficient than naiive repeated squaring.
 f(x) = f(p) * f(x/p) where p|x.
 if x is prime, f(x) = powmod(x,2^K-1)
 res = ∑ { f(i) : i=1..N }
 number of prime under 10^6 is 78498 (<10^5). It is more efficient than 10^6 as shown in below editorial.
 http://www.wolframalpha.com/input/?i=number+of+prime+numbers+less+than+1000000
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+660
    - 2^K-1 = ∑ { 2^k : k=0..K-1 }. i^(2^K-1) = i^(∑ { 2^k : k=0..K-1 }) = ∏ { i^2^k : k=0..K-1 }
    - this is actually another proof of repeated squaring. They are equivalent 😄
    - pre-computing first factor by sieve of eratosthenes. this is more efficient.
      - runtime of sieve of erathosthenes is O(N lg lg N) ≈ O(N)
 
 24:13-24:30 add sieve precomputation solution
  - 1000000,400,1000000000 (0.96 -> 0.66 sec)
 
 Key:
  - dividor DP
  - repeated squaring
  - sieve of erathosthenes
   - easier to estimate runtime
   - not mandatory, search of prime on the fly works for test cases too
 
 Summary:
  - nice to apply repeated squaring immediately 👍
  - tried to transform ∑ {i^(2^K-1), i=1..N } to drastically efficient algorithm though, couldn't find a it
  - it turned out that iterating 1..N is solving sub problems. it's typical technique to solve numeric problem
 
 submit solutions
 - on the fly prime search
  - https://community.topcoder.com/stat?c=problem_solution&rm=326438&rd=16463&pm=13802&cr=40089362
 - sieve of erathosthenes
  - https://community.topcoder.com/stat?c=problem_solution&rm=326433&rd=16463&pm=13802&cr=40021483
 
 */

LL dp[1000001];
LL P[1000001];

class Powerit {
public:
  int K,M;
  LL powmod(LL a) {
    LL res=1LL;
    int k=K;
    while(k>0) {
      res*=a,res%=M;
      a*=a,a%=M;
      --k;
    }
    return res;
  }
  
  int calc(int N, int _K, int _M) {
    K=_K; M=_M;
    ZERO(dp);
    FOR(i,2,N+1) P[i]=i;
    FOR(i,2,N+1) if(P[i]==i) {
      for(int p=i+i; p<=N; p+=i) P[p]=i;
    }
    LL res=dp[1]=1LL;
    for(int i=2; i<=N; ++i) {
      if(P[i]==i) dp[i]=powmod(i);
      else dp[i]=(dp[P[i]]*dp[i/P[i]])%M;
      res+=dp[i],res%=M;
    }
    return res;
  }
};

class Powerit_onthefly_prime_search {
public:
  int K,M;
  LL powmod(LL a) {
    LL res=1LL;
    REP(_,K) {
      res*=a,res%=M;
      a*=a,a%=M;
    }
    return res;
  }
  
  int calc(int N, int _K, int _M) {
    K=_K; M=_M;
    ZERO(dp);
    LL res=dp[1]=1LL;
    for(int i=2; i<=N; ++i) {
      LL p=-1;
      for(int j=2; j*j<=i; ++j) if(i%j==0) {
        p=j;
        break;
      }
      if(p>0) dp[i]=dp[p]*dp[i/p],dp[i]%=M;
      else dp[i]=powmod(i);
//      assert(dp[i]>=0);
      res+=dp[i],res%=M;
    }
    return res;
  }
};

class Powerit_TLE {
  public:
  int calc(int N, int K, int M) {
    MOD=M;
    LL res=0;
    for(LL i=1LL; i<=N; ++i) {
      LL x=1,a=i;
      REP(_,K) {
        x*=a,x%=M;
        a*=a,a%=M;
      }
      res+=x,res%=M;
    }
    return res;
  }
};

// CUT begin
ifstream data("Powerit.sample");

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

bool do_test(int n, int k, int m, int __expected) {
    time_t startClock = clock();
    Powerit *instance = new Powerit();
    int __result = instance->calc(n, k, m);
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
        int m;
        from_stream(m);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, k, m, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1503877010;
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
        cout << "Powerit (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
