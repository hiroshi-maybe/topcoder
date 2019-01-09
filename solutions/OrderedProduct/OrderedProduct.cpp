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

constexpr int MOD = 1e9+7;

/**
 
 7/5/2017
 
 22:51-23:25 time up
 
 8:35 read editorials
 http://kmjp.hatenablog.jp/entry/2017/03/26/0930
 https://kimiyuki.net/blog/2017/03/27/srm-711-med/
 
 8:50-9:50 combination with repetition, multi-choose
 http://www24.atpages.jp/venvenkazuya/mathA/outcomes5.php
 https://ja.wikipedia.org/wiki/重複組合せ
 https://en.wikipedia.org/wiki/Stars_and_bars_(combinatorics)
 https://en.wikipedia.org/wiki/Multiset#Counting_multisets
 https://en.wikipedia.org/wiki/Stars_and_bars_(combinatorics)
 https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
 
 23:42-25:00 passed system test
 
 7/8/2017
 
 15:50 add solution with combination computation which uses modular multiplicative inverse by Euler's theorem
 23:40 add faster combination dp solution inspired by https://www.topcoder.com/blog/single-round-match-711-editorials/
 
 */

/*
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

// https://en.wikipedia.org/wiki/Modular_multiplicative_inverse#Computation
// Modular multiplicative inverse by Euler's theorem
// a^-1 (`mod` mod) = a^(mod-2), a should be coprime to mod, mod=1e9+7
// O(lg m)
LL modinv(LL a) {
  return powmod(a, MOD-2);
}

// memoized factorial(n) (`mod` 1e9+7)
// O(n) before cache warmup
LL factmod(LL n) {
  static vector<LL> memo(1,1);
  if(memo.size()<=n) {
    LL l=memo.size();
    memo.resize(n+1);
    for(LL i=l; i<=n; ++i) memo[i]=memo[i-1]*i, memo[i]%=MOD;
  }
  return memo[n];
}

// n chooses k
// C(n,k) = n!/((n-k)!*k!)
LL choose(LL n, LL k) {
  if (n<k) return 0;
  k = min(n-k,k);
  LL res=factmod(n);
  res *= modinv(factmod(n-k)), res%=MOD;
  res *= modinv(factmod(  k)), res%=MOD;
  
  return res;
}

// multichoose
// H(n,k) = C(n+k-1,k)
LL multichoose(LL n, LL k) {
  if(n==0&&k==0) return 1;
  
  return choose(n+k-1,k);
}*/

LL dp[2505];
LL C[5010][5010];
// Populate n chooses k (n={1..N},k={1..N}) (accumulate by DP)
// C(n,k) = C(n-1,k)+C(n-1,k-1)
// O(N^2) time
void choose(LL N) {
  C[0][0]=1;
  // i chooses j
  for(int i=1; i<=N; ++i) {
    C[i][0]=1;
    for(int j=1; j<=i; ++j) {
      C[i][j] = C[i-1][j]+C[i-1][j-1], C[i][j]%=MOD;
    }
  }
}

/*
LL dp2[2505];
class OrderedProduct_ord {
public:
  int count(vector<int> a) {
    memset(dp2,0,sizeof(dp2));
    
    LL sum=accumulate(a.begin(),a.end(),0LL);
    
    LL res=0;
    // res = ∑{dp[L],L=1..sum}
    FOR(l,1,sum+1) {
      
      // dp[L] = ∏{H(L,a[i]),i=1..N}-∑{C(n,k)*dp[k],k=1..L}
      dp2[l]=1;
      FORR(ai,a) {
        dp2[l] *= (multichoose(l,(LL)ai)%MOD);
        dp2[l] %= MOD;
      }
      for(LL k=1; k<l; ++k) {
        dp2[l] += MOD;
        dp2[l] -= ((choose(l,k)%MOD)*(dp2[k]%MOD))%MOD;
        dp2[l] += MOD;
        dp2[l] %= MOD;
      }
      res += dp2[l];
      res %=MOD;
    }
    
    return res;
  }
};*/

class OrderedProduct {
public:
  int count(vector<int> a) {
    memset(dp,0,sizeof(dp));
    
    LL sum=accumulate(a.begin(),a.end(),0LL);
    
    choose(5009);
    
    LL res=0;
    // res = ∑{dp[L],L=1..sum}
    FOR(l,1,sum+1) {
      
      // dp[L] = ∏{H(L,a[i]),i=1..N}-∑{C(n,k)*dp[k],k=1..L}
      dp[l]=1;
      FORR(ai,a) {
        dp[l] *= (C[l+ai-1][ai]%MOD);
        dp[l] %= MOD;
      }
      for(LL k=1; k<l; ++k) {
        dp[l] += MOD;
        dp[l] -= ((C[l][k]%MOD)*(dp[k]%MOD))%MOD;
        dp[l] += MOD;
        dp[l] %= MOD;
      }
      res += dp[l];
      res %=MOD;
    }
    
    return res;
  }
};

// CUT begin
ifstream data("OrderedProduct.sample");

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

bool do_test(vector<int> a, int __expected) {
    time_t startClock = clock();
    OrderedProduct *instance = new OrderedProduct();
    int __result = instance->count(a);
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
        vector<int> a;
        from_stream(a);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499320298;
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
        cout << "OrderedProduct (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
