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
typedef unordered_map < int, LL > MAPII;
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
 
 12/23/2017
 
 16:57-18:15 TLE
 23:05-23:25 convert naiive dfs to dp
 23:26-23:36 1WA. fix overflow bug and system test passed.
 
 My original solution:
 
 `H` is large. We cannot keep state about `H`.
 We need to fill exactly `H` slots by devisors.
 Suppose we can make a sequence of divisors whose length is `x`.
 Then we can compute  possible sequence by H(x,H-x-1), H(n,k) is multichoose.
 
 Now problem is reduced to count (l,cnt), `l`: length of sequence, `cnt`: number of sequence whose length is `l`.
 res = ∑ { cnt*H(l,H-l-1) }

 Sequences form tree by divisors. We'll have |D| rooted trees, where D = { divisor of `N` }
 d ∈ D shows up in paths of trees. We can count possible sub trees by tree DP in O(D^2), D is number of divisors of N.
 By highly composite number, number of divisors for N<=1e9 is less than 1440.
 It's possible to count them.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+565
  - http://kmjp.hatenablog.jp/entry/2012/12/22/1100
  - http://topcoder.g.hatena.ne.jp/minus9d/20130115/1355750569
  - http://ekaing.hatenablog.com/entry/2013/04/21/001655
 
 Editorial's solution is smarter.
 Suppose N=∏ { p[i]^k[i] } (prime factorization)
 
 We can look at two slots A[k-1] = ∏ { p[i]^k'[i] }, A[k]= ∏ { p[i]^k''[i] }
 As long as k'[i]>=k''[i], for all `i`, A[k] | A[k-1] holds.
 We can look at k[i] independently.
 Let's define number of possible sequences of p[i]^k as f(i,k).
 f(i,k) = H(k+1,H-1) = C(k+1+H-1-1, H-1) = C(k+H-1,H-1) = C(k+H-1,k)
 
 res = ∏ { H(k[i]+1,H-1) }
 
 12/24/2017
 
 18:20-18:28 add solution by prime factorization.
 
 Summary:
  - Great to have reached multichoose from large H constraint
  - Nice job to solve by DP even though prime factorization did not come up with
  - Solution with prime factorization is simpler. I should look at prime factorization in problem of divisibility
  - There are three major approaches in `divisible`? 🤔
    - modular arithmetic
    - prime factorization
    - divisor enumeration
 
 */
constexpr int MOD = 1e9+9;
vector<LL> divisors(LL N) {
  assert(N>=1);
  vector<LL> res;
  for(LL p=1; p*p<=N; ++p) if(N%p==0) {
    res.push_back(p);
    if(p!=N/p) res.push_back(N/p);
  }
  sort(res.begin(),res.end());
  return res;
}

LL choose(LL n, LL k) {
  if(n<k) return 0;
  k = min(n-k,k);
  
  const int MAXK = 200;
  assert(k<=MAXK);
  static LL inv[MAXK+1],invfact[MAXK+1];
  
  if(inv[1]==0) {
    inv[1]=1;
    for(int i=2;i<=MAXK;i++) inv[i]=inv[MOD%i]*(MOD-MOD/i)%MOD;
    invfact[0]=1;
    for(int i=1;i<=MAXK;i++) invfact[i]=invfact[i-1]*inv[i]%MOD;
  }
  LL res=invfact[k];
  for(int i=0;i<k;++i) res*=(n-i)%MOD,res%=MOD;
  return res;
}

LL multichoose(LL n, LL k) {
  if(n==0&&k==0) return 1;
  return choose(n+k-1,k);
}

unordered_map<int, MAPII> memo;
class DivisibleSequence_org {
  public:
  vector<LL> ds;
  MAPII cnt;
//  SETI viz;
  /*
  void dfs(int n, int l) {
//    dump2(n,l);
    ++cnt[l];
    if(viz.count(n)==0) {
      viz.emplace(n);
      dfs(n,1);
    }
    FORR(d,ds) if(d>1) {
      if(d>n) break;
      if(n%d==0) dfs(n/d,l+1);
    }
  }*/
  
  MAPII f(int n) {
    if(memo.count(n)) return memo[n];
    MAPII &res=memo[n];
    ++res[1];
    FORR(d,ds) if(d>1) {
      if(d>n) break;
      if(n%d==0) {
        MAPII x = f(n/d);
        FORR(kvp,x) (res[kvp.first+1]+=kvp.second)%=MOD;
      }
    }
    FORR(kvp,res) (cnt[kvp.first]+=kvp.second)%=MOD;
    return res;
  }
  
  int count(int N, int H) {
    cnt.clear();
    this->ds=divisors(N);
    if(H==1) return 1;
    memo.clear();
    f(N);
    
//    dump2(SZ(ds),SZ(cnt));
//    FORR(kvp,cnt) dump2(kvp.first,kvp.second);
    
    LL res=0;
    FORR(kvp,cnt) {
      int l=kvp.first;
      LL a=kvp.second;
      
      if(H-l-1<0) continue;
      a*=multichoose(l,H-l-1),a%=MOD;
      res+=a,res%=MOD;
//      dump2(l,res);
    }
    
    return res;
  }
};

// O(√N+𝜔'(N)*𝛺'(N)) time, 𝜔'(N): number of primes (<9), 𝛺'(N): max number of exponent of prime (<30)
// 𝜔'(10^9) = 9, n=223092870, prime factors = {2,3,5,7,11,13,17,19,23}
// 𝛺'(10^9) = 29, n=536870912, prime factors = { 2x29 }
class DivisibleSequence {
public:
  int count(int n, int H) {
    LL res = 1;
    VI ks;
    for(int p=2; p*p<=n; ++p) if(n%p==0) {
      int k=0;
      while(n%p==0) ++k,n/=p;
      ks.push_back(k);
    }
    if(n>1) ks.push_back(1);
    FORR(k,ks) res*=multichoose(k+1,H-1),res%=MOD;
    return res;
  }
};

// CUT begin
ifstream data("DivisibleSequence.sample");

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

bool do_test(int N, int H, int __expected) {
    time_t startClock = clock();
    DivisibleSequence *instance = new DivisibleSequence();
    int __result = instance->count(N, H);
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
        int H;
        from_stream(H);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, H, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1514077064;
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
        cout << "DivisibleSequence (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
