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
 
 11/18/2017
 
 9:32-10:15 tried to solve by divide and conquer though, I could not.
 
 11/27/2017
 
 21:15-21:30 read editorial

 Editorial:
  - http://kmjp.hatenablog.jp/entry/2017/11/21/1000
 
 11/28/2017
 
 18:30-19:00 understand trick of res*n^2
 22:00-24:00 calculate formula
 24:00-25:10 implement and bug fixes
 
 1. Manhattan distance

 Distance in x-axis and y-axis are independent each other.
 So we can calculate in one dimension and double it.
 
 2. Compress horizontal n-blocks
 
 We can compute vertical distance for each row in n=2 maze (distance * cnt in r[i] * cnt in r[j]):
   ..   r[0]
   ..   1*n*n  r[1]
 ...... 2*n*3n 1*n*3n r[2]
 ...... 3*n*3n 2*n*3n 1*3n*3n r[3]
   ..   4*n* n 3*n* n 2*3n* n 1*3n*n r[4]
   ..   5*n* n 4*n* n 3*3n* n 2*3n*n 1*n*n
 
 If we remove `n`, it's actually calculating sum of distances of compressed maze
   .
   .
  ...
  ...
   .
   .
 
 Thus we can compute of this compressed maze and multiply n*n later.
 
 columns: bac
           .
           .
          ...
          ...
           .
           .
 
 We can calculate vertical distance separatedly for column pairs.
 1. (a,a)
 2. (b,(b,c)) and (c,(b,c))
 3. (a,b) and (a,c)
 
 1. (a,a)
 
 A
 = f(a)
 = ∑{ ∑{k:k=1..l} : l=1..3n-1}
 = 3n*(3n-1)*(3n+1)/6

 2. (b,(b,c)) and (c,(b,c))
 
 B
 = f(b,(b,c))+f((c,(b,c))
 = 2*f(b,(b,c)) (symmetry)
 = 2*∑{ ∑{2k:k=1..l} : l=1..n-1}
 = 4n*(n-1)*(n+1)/6
 
 3. (a,b) and (a,c)
 
 C
 = f(a,b)+f(a,c)
 = 4*∑{ ∑{k:k=1..l} : l=n..2n-1}
 = 4*∑{ ∑{k:k=1..l} : l=1..2n-1} - 4*∑{ ∑{k:k=1..l} : l=1..n-1}
 = n*(7n^2-1)/6
 
 res = (A+B+C)*2*n^2
 
 Key:
  - Using symmetry property, result can be calculated in O(1)
  - Manhattan distance
   - distance in x-axis and y-axis are independent. It can be calculated separatedly
  -
 
 Summary:
  - I tried to solve by divide and conquer though, no luck in the contest
  - very tough problem for current my level
  - even if I found O(1) approach, calculation of formula on paper is not small
  - complex formula needs to be reduced to code without overflow
 
 */

constexpr LL MOD = 1e9+7;

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

LL inv6=modinv(6LL,MOD);
LL inv2=modinv(2LL,MOD);

class SimpleMazeEasy {
  public:
  // sum of square series a*∑{k^2:k=1..n}
  LL S2(LL a, LL n) {
    LL res=n*(n+1)%MOD;
    (res*=2LL*n+1LL)%=MOD;
    (res*=inv6)%=MOD;
    (res*=a)%=MOD;
    return res;
  }
  // sum of series a*∑{k:k=1..n}
  LL S1(LL a, LL n) {
    LL res=n*(n+1)%MOD;
    (res*=inv2)%=MOD;
    (res*=a)%=MOD;
    return res;
  }
  // sum of constant a*∑{1:k=1..n}
  LL S0(LL a, LL n) {
    LL res=n;
    (res*=a)%=MOD;
    return n;
  }
  
  int findSum(long long n) {
    // n%MOD first to avoid overflow
    n%=MOD;
    LL A=S2(inv2,3LL*n-1LL);
    (A+=S1(inv2,3LL*n-1LL))%=MOD;
    
//    LL x1=(3*n)%MOD*(3*n+1)%MOD*(3*n+MOD-1)%MOD*inv6%MOD;
//    if(x1!=res1) dump2(res1,x1);
//    assert(x1==res1);
    
    LL B=S2(1LL,n-1);
    B+=S1(1LL,n-1);
    B*=2LL,B%=MOD;
    
//    LL x2=4*n%MOD*(n+MOD-1)%MOD*(n+1)%MOD*inv6%MOD;
//    if(x2!=res2) dump2(res2,x2);
//    assert(x2==res2);
    
    LL n1=(2LL*n+MOD-1)%MOD,n2=(MOD+n-1)%MOD;
    LL C=S1(inv2,n1);
    (C+=S2(inv2,n1))%=MOD;
    C+=MOD-S1(inv2,n2),C%=MOD;
    C+=MOD-S2(inv2,n2),C%=MOD;
    (C*=4LL)%=MOD;
    
//    LL x3=4*n*((7*n%MOD)*n%MOD+MOD-1)%MOD*inv6%MOD;
//    if(x3!=res2) dump2(res3,x3);
//    assert(x3==res3);
    
    LL res=(A+B)%MOD;
    (res+=C)%=MOD;
    (res*=n)%=MOD;
    (res*=n)%=MOD;
    (res*=2)%=MOD;
    
    return res;
  }
  /*
  int findSum(long long n) {
    n = n % mod;
    long long x = 1;
    long long ans = 0;
    for (int i = 0; i < 5; i++)
    {
      x *= n;
      x %= mod;
      if (i == 2)
        ans -= (x * 11ll) % mod;
      if (i == 4)
        ans += (x * 59ll) % mod;
    }
    ans += mod;
    ans %= mod;
    ans *= 333333336;
    ans %= mod;
    return ans;
  }*/
};

// CUT begin
ifstream data("SimpleMazeEasy.sample");

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

bool do_test(long long n, int __expected) {
    time_t startClock = clock();
    SimpleMazeEasy *instance = new SimpleMazeEasy();
    int __result = instance->findSum(n);
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
        long long n;
        from_stream(n);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1511026341;
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
        cout << "SimpleMazeEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
