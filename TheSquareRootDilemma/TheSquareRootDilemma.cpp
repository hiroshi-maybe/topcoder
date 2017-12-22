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
 
 12/20/2017
 
 8:48-9:27 analysis
 19:20-20:26 read editorials and system test passed
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+567
  - http://kmjp.hatenablog.jp/entry/2013/01/22/0900
   - Find all the prime numbers by sieve
   - For each x, keep dividing by prime numbers until we get smallest `s` s.t. x = p^2*s
     - actually no need to use prime number to get `s`
     - we can iterate p from 1 to √x as shown in official editorial
  - http://torus711.hatenablog.com/entry/20130206/p1
  - http://pushl.hatenablog.com/entry/2013/01/25/225141
  - http://topcoder.g.hatena.ne.jp/minus9d/20130131/1362664923
  - http://tckintore.blogspot.com/2013/06/5-srm567-div1easy-thesquarerootdilemma.html
 
 (√a+√b)^2 is integer if and only if √(a*b) is integer.
 That means we want to find (a,b) s.t. a*b = X^2 (perfect square)
 
 My approach #1:
  Perfect square is expressed by ∏ { p[i]^(2*k[i]) : p[i] is prime number }
  So I tried prime factorization.
  1. brute force `a` in [1,A] in O(A)
  2. find prime factors of `a` in O(√A)
  3. find possible counter party `b` by primes of `a` whose factor is odd
   => Counting from "set of primes" is not easy. How do we find 2^5*3^*5^2*11^2 from { 2, 3 }?
 
 I couldn't find out that we don't need to start from set of primes.
 
 My approach #2:
  1. √(a*b) is upper-bounded by 77777. Brute-force x in [1,√(A*B)]
  2. If exponents of prime numbers are all even, count possible pairs (a,b) s.t. a*b=x
   => It's hard to find a and b which satisfies a<=A AND b<=B
 
 Actually #1 is closer to expected solution.
 I tried to find `b` from set of primes though, it's not necessary.
 Eventually a*b = X^2. So generally we can represent `a` and `b` as below:
 
  a = p^2*s, b=s*q^2
 
 If `a` is fixed, we can find smallest `s` from `a` in O(√a)<O(√A)
 Smaller `s` is better because that gives more `q`s which satisfies b<=B
 We can search `q` in O(√b)<O(√B)
 Total runtime is O(A*(√A+√B)) time <=77777*2*√77777 ≈ 5*10^7
 
 Search by keeping x^2 is strong constraint which is popular technique in trial division.
 That reduces search space dramatically.
 
 Key:
  - It's possible to search smallest `s` s.t. a=p^2*s in O(√A)
  - Search corresponding `b` once `s` is found in O(√B)
 
 Summary:
  - My first approach of searching by set of prime was not easy way to search
  - Finding smallest `s` s.t. a=p^2*s in O(√A) was the key
   - It's not straightforward to figure out the approach directly from formula a*b = ∏ { p^k : k is even }
   - Brute-force `a` is the first step. I should have tried represent `a` itself by formula
  - Once we found formula by x^2*s, it's easy to come up with O(√N) search
 
 */

class TheSquareRootDilemma {
public:
  int countPairs(int A, int B) {
    int res=0;
    for(int a=1; a<=A; ++a) {
      int p=1;
      for(int x=1; x*x<=a; ++x) if(a%(x*x)==0) p=x;
      int s=a/p/p;
      for(int q=1; s*q*q<=B; ++q) ++res;
    }
    
    return res;
  }
};

VI primef(int n) {
  MAPII M;
  for(int p=2; p*p<=n; ++p) while(n%p==0) {
    M[p]++;
    n/=p;
  }
  if(n!=1) M[n]++;
  VI res;
  FORR(kvp,M) res.push_back(kvp.second);
  return res;
}
class TheSquareRootDilemma_wrong {
  public:
  int countPairs(int A, int B) {
    int res=0;
    int N=(int)ceil(sqrt(A)*sqrt(B))+5;
    dump(N);
    for(int n=1; n<=N; ++n) {
      VI xs=primef(n);
      int y=1;
      FORR(x,xs) {
        if(x%2!=0) { y=0; continue; }
        y*=x+1;
      }
      if(y)dump2(n,y);
      res+=y;
    }
    
    return res;
  }
};

// CUT begin
ifstream data("TheSquareRootDilemma.sample");

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

bool do_test(int N, int M, int __expected) {
    time_t startClock = clock();
    TheSquareRootDilemma *instance = new TheSquareRootDilemma();
    int __result = instance->countPairs(N, M);
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
        int M;
        from_stream(M);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, M, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1513788501;
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
        cout << "TheSquareRootDilemma (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
