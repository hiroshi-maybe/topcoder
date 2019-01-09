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
 
 11/5/2017
 
 16:18-17:31 time up
 
 17:32-17:55, 22:00-24:00 read editorials and add solution:
  - http://kmjp.hatenablog.jp/entry/2013/11/02/1200
  - http://apps.topcoder.com/wiki/display/tc/SRM+596
 
 My analysis process:
 
 F(n) = ∏ { n-i^2 : i=0..k<√n }
 
 Since k<√n, we have at most 10^6 k.
 Once we find x - i^2 ≡ 0 (mod D) => x ≡ i^2 (mod D) , F(x+p*D) ≡ 0 (mod D) for any non-negative p.
 We can define such xs as S[i] for each i. Now we want to calculate | ∪ { S[i] i=0..k<√n }|
 
 By inclusion-exclusion principle...
 | ∪ { S[i] i=0..k<√n }| = ∑|{S[i]:i=0..k}| - ∑|{S[i]∩S[j]: i<j,i,j=0..k}| + ...

 However, computation of this seems to be at least O(2^k) which is too expensive.
 Also it's not easy to compute |S[i]∩S[j]|... Eventually I'm in stuck.
 
 Now let's focus on property of modular arithmetic.
 This approach worked in some div2 hard problems that I solved
  - https://github.com/k-ori/topcoder/blob/master/TwoNumberGroupsEasy/TwoNumberGroupsEasy.cpp
  - https://github.com/k-ori/topcoder/blob/master/PolynomialRemainder/PolynomialRemainder.cpp
 
   F(n)
 ≡ ∏ { n-i^2 : i=0..k<√n } (mod D)
 ≡ ∏ { (n-i^2) (mod D) : i=0..k<√n }
 ≡ ∏ { n (mod D)- i^2 (mod D) : i=0..k<√n }
 
 Let's define n (mod D) = a (0<=a<D).
 There are at most D `a` and at most 10^6 `i`.
 Now we want to find S(a) = |{ n : n≡a(mod D), ∃i,i^2≡a(mod D), n>i^2 }|
 Note that i^2≡a(mod D) is satisfied because D is prime number.
 It's possible to compute it by computing a-i^2, i=0..√n.
 However it takes totally O(D*√n) ≈ 10^9. It will TLE.
 
 Actually we don't need to compute all i for each a.
 Larger n can take larger i.
 If we find minimum i s.t. i^2≡a(mod D) for each a, we don't need to check all i for each a.
 Also it's possible to pre-compute it. Thus runtime is O(D+√n) time.
 
 res = f(R)-f(L-1)
 f(n) = ∑ {|{ n : n<=N, n≡a(mod D), n>j^2 }| : a=0..D }, j=min { i : i^2≡a(mod D) }
 
   T(P)
 = T(P1) + D*T(P2)
 = O(√n) + D*O(1)
 ≈ 10^6
 
 - P1: computing minimum i s.t. i^2≡a(mod D)
 - P2: count number of n s.t. n≡a(mod D) AND F(n)≡0(mod D)
 
 Key:
  - Search space 10^12 is reduced to 10^3 due to modular arithmetic property
  - If (n%D-i^2%D)=0, for any n2 s.t. n2>n AND n2%D=n%D, F(n)%D=0 (divisible by D)
 
 Summary:
  - I tried to solve by inclusion-exclusion principle though, I couldn't compute AND subset efficietnly
  - I analyzed i^2≡a(mod D). However I missed analysis n≡a(mod D).
  - Reducing search space by (mod n) seems to be useful technique
 
 */
class SparseFactorialDiv2 {
  public:
  LL D;
  LL cnt(LL n, LL D, LL x) {
    return (n-x)/D+1;
  }
  LL f(LL N) {
    vector<LL> J(D,-1);
    for(LL j=0; j*j<N; ++j) if(J[(j*j)%D]==-1) J[(j*j)%D]=j;

    LL res=0;
    REP(x, D) if(J[x]!=-1) {
      LL j=J[x];
      res += cnt(N,D,x) - cnt(j*j,D,x);
    }
    return res;
  }
  long long getCount(long long L, long long R, long long D) {
    this->D=D;
    return f(R)-f(L-1);
  }
};

// CUT begin
ifstream data("SparseFactorialDiv2.sample");

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

bool do_test(long long lo, long long hi, long long divisor, long long __expected) {
    time_t startClock = clock();
    SparseFactorialDiv2 *instance = new SparseFactorialDiv2();
    long long __result = instance->getCount(lo, hi, divisor);
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
        long long lo;
        from_stream(lo);
        long long hi;
        from_stream(hi);
        long long divisor;
        from_stream(divisor);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(lo, hi, divisor, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1509927477;
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
        cout << "SparseFactorialDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
