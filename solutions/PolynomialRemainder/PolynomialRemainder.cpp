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
 
 10:16-10:40,11:45-12:00,18:40-19:00 give up
 
 19:00-20:10,21:30-22:36 read editorial and add solution:
  - http://kmjp.hatenablog.jp/entry/2015/04/29/1030
  - http://mayokoex.hatenablog.com/entry/2015/09/26/205253
  - https://apps.topcoder.com/wiki/display/tc/SRM+657
    - modular congluence https://www.khanacademy.org/computing/computer-science/cryptography/modarithmetic/a/congruence-modulo
    - Chinese Remainder Theorem https://en.wikipedia.org/wiki/Chinese_remainder_theorem
    - Programming contest challenge book (ant book) section 4-1
    - CLRS 31.3 Modular arithmetic, 31.4 Solving modular linear equations, 31.5 The Chinese remainder theorem
 
 We want to find x s.t. P(x) ≡ 0 (mod 10^9) where P(x) = a*x^2+b*x+c
 Chinese Remainder Theorem suggests that P(x) ≡ 0 (mod 10^9) <=> P(x) ≡ 0 (mod 2^9) AND P(x) ≡ 0 (mod 5^9)
  - CRT: P (mod n) <=> P (mod p) AND P (mod q), where p and q are coprime and n=p*q
 
 It's easier to find x2 and x5 such that...
  x2 ∈ { x : P(x) ≡ 0 (mod 2^9) }
  x5 ∈ { x : P(x) ≡ 0 (mod 5^9) }

 Since P(x) ≡ P(x+2^9) (mod 2^9) AND P(x) ≡ P(x+5^9) (mod 5^9), we can search x2 from [0,2^9) and x5 from [0,5^9)
 Note that 5^9 < 2*10^6, 2^9 < 1*10^3, it's possible to search without TLE
 
 CRT implies that x is a number which satisfies both x ≡ x2 (mod 2^9) and x ≡ x5 (mod 5^9)
 Once we find x2 and x5, we can search such x in [0,10^9).
 
 x ≡ x5 (mod 5^9) AND x ≡ x2 (mod 2^9)
 => x = x5 + k*5^9 AND x % 2^9 = x2, k=0..<10^9
 
 key:
  - 10^9 = 2^9*5^9 is the first step
  - divisible => mod, mod and coprime => CRT
  - problem(10^9) => subproblem(2^9) + subproblem(5^9) => search x which satisfies both subproblems
    - Leverage CRT to divide into two subproblems and merge them
 
 Summary:
  - I tried to solve from 10^9=2^9*5^9 though, it's hard to move forward without understanding CRT
  - deep understanding of modular arithmetic is important
 
 Submit solution:
  - dfs with backtracking? 🤔
    - https://community.topcoder.com/stat?c=problem_solution&rm=326152&rd=16417&pm=13774&cr=23304823
 
 */
class PolynomialRemainder {
  public:
  const LL N=1000000000;
  LL a,b,c;
  LL P(LL x, LL M) {
    LL f1=((a*x)%M)*x%M;
    LL f2=(b*x)%M;
    LL f3=c;
    
    return (f1+f2+f3)%M;
  }
  
  LL getCongruence(int M) {
    for(int x=0; x<M; ++x) {
      if(P(x,M)==0) return x;
    }
    return -1;
  }
  
  int findRoot(int a, int b, int c) {
    this->a=a,this->b=b,this->c=c;
    
    LL pow2=1,pow5=1;
    REP(_,9) pow2*=2, pow5*=5;
    
    LL x2=getCongruence(pow2),x5=getCongruence(pow5);
    if(x2==-1||x5==-1) return -1;
    
    LL x=x5;
    while (x%pow2!=x2) x+=pow5;
    
    // assert x ≡ x5 (mod 5^9) AND x ≡ x2 (mod 2^9)
    assert(x%pow2==x2);
    assert(x%pow5==x5);
    // assert  P(x) ≡ 0 (mod 10^9)
    assert(P(x,pow2*pow5)==0);
    return x;
  }
};

// CUT begin
ifstream data("PolynomialRemainder.sample");

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

bool do_test(int a, int b, int c, int __expected) {
    time_t startClock = clock();
    PolynomialRemainder *instance = new PolynomialRemainder();
    int __result = instance->findRoot(a, b, c);
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
        int a;
        from_stream(a);
        int b;
        from_stream(b);
        int c;
        from_stream(c);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, c, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1504113406;
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
        cout << "PolynomialRemainder (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
