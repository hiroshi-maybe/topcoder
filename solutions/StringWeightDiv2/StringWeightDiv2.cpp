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
 
 11/16/2017
 
 9:36-10:14 analysis
 10:15-10:18 implement
 10:18-10:28 debug, submit and system test passed (416.59 pt)
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+586
  - http://kmjp.hatenablog.jp/entry/2013/07/28/1000
  - https://topcoder.g.hatena.ne.jp/firewood/20130819/1376911103
  - http://emkcsharp.hatenablog.com/entry/SRM586/StringWeightDiv2
 
 As following samples, we can find that some different alphabets need to be used in L<=26.
 
 i) L<=26 (weight=0)
  res = P(26,L) where P(n,k) is permutation n!/(n-k)!
 
 If we look at L=27, we get minimum weight only when alphabet which occurs twice is consecutive like abc..yzz
 Then weight of string is 0*25+1=1
 If L=28, string needs to be abc...yyzz or abc...yzzz (weight=0*24+1*2=0*25+2*1=2).
 So looks like alphabet always need to be in consecutive order. Also min weight for L is L-26.
 
 In L=27 case, we looked at that `abc..yzz` gives weight 1.
 Suppose that we put `z` in different position.
 Then weight cannot be less than or equal to 1.
 Obviously closest position gives us minimum weight.
 
 Next step is how to count possible string patterns. I show two ways here.
 
 1) DP solution
 
 We need to put all 26 alphabets.
 If we count patterns to put each character, total number of possible string is 26!*f(L,26)
 f(L,26) = {number of patterns of 26 characters in length L}
 
 f(x,a) = ∑ { f(y,a-1) : y=0..x-1 }
 f(0,a) = a==0
 f(x,0) = 0
 
 res=26!*f(L,26)
 
 This can be computed in O(26*L^2) time (≈3*10^7)
 
 2) Multi choose solution
 
 H(n,k) shows combinatorics to choose k out of infinite n elements.
 We can think that we have 26 elements for different alphabet from left to right like S={0,0,1,2,2,2,..,26,26}
 Since each alphabet should show up at least once, we want to choose L-26 out of 26 elements.
 In each element, any alphabet can be assigned in one to one mapping.
 Thus res = 26!*H(26,L-26)
 
 H(n,k)=C(k+n-1,k), where C is binomial coefficient.
 H(26,L-26)=C(L-26+26-1,L-26)=C(L-1,L-26)=C(L-1,25).
 Binomial coefficient can be computed by Pascal's triangle with DP.
 
 Multi-choose:
  - https://en.wikipedia.org/wiki/Multiset
 
 Key:
  - Different computation for two separated cases 1) L<=26 2) L>26
  - To achieve min weight in L>26, each alphabet must stay in consecutive order
  - Multi-choose 
 
 Summary:
  - I analyzed that each alphabet needs to be consecutive for L>26
  - Solved by DP without figuring out multi-choose property
  - Analysis is still slow though, process was following right way 👍
 
 */
constexpr int MOD = 1e9+9;

// O(26*L) time
LL C[1001][26];
class StringWeightDiv2 {
public:
  // P(26,L)
  LL perm(int l) {
    LL res=1;
    REP(i,l) {
      res*=26LL-i,res%=MOD;
    }
    return res;
  }
  int countMinimums(int L) {
    if(L<=26) return perm(L);
    for(int i=0; i<=L; ++i) {
      C[i][0]=1;
      for(int j=1; j<=min(i,25); ++j) C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
    }
    return (perm(26)*C[L-1][25])%MOD;
  }
};

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
LL modinv(LL a, LL p=MOD) {
  return powmod(a, p-2);
}
// memoized factorial(n) (`mod` 1e9+9)
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
// O(N) time
LL choose(LL n, LL k) {
  if (n<k) return 0;
  k = min(n-k,k);
  LL res=factmod(n);
  res *= modinv(factmod(n-k)), res%=MOD;
  res *= modinv(factmod(  k)), res%=MOD;
  
  return res;
}

// chooses k out of infinite n elements, O(n+k) time
// H(n,k) = C(k+n-1,k)
LL multichoose(LL n, LL k) {
  if(n==0&&k==0) return 1;
  return choose(n+k-1,k);
}

class StringWeightDiv2_multichoose {
public:
  int countMinimums(int L) {
    if(L<=26) return (factmod(26)*modinv(factmod(26-L)))%MOD;
    return (factmod(26)*multichoose(26,L-26))%MOD;
  }
};

// O(26*L^2) time
int memo[1001][27];
class StringWeightDiv2_dp {
  public:
  LL f(int x, int a) {
    int &res=memo[x][a];
    if(res>=0) return res;
    if(x==0) return (res=(a==0));
    if(a==0) return (res=0);
    
    res=0;
    REP(y,x) res+=f(y,a-1),res%=MOD;
    return res;
  }
  LL fact(int l) {
    LL res=1;
    REP(i,l) {
      res*=26LL-(LL)i,res%=MOD;
    }
    return res;
  }
  int countMinimums(int L) {
    if(L<=26) return fact(L);
    MINUS(memo);
    LL res=fact(26);
    return (res*f(L,26))%MOD;
  }
};

// CUT begin
ifstream data("StringWeightDiv2.sample");

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

bool do_test(int L, int __expected) {
    time_t startClock = clock();
    StringWeightDiv2 *instance = new StringWeightDiv2();
    int __result = instance->countMinimums(L);
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
        int L;
        from_stream(L);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(L, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1510853758;
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
        cout << "StringWeightDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
