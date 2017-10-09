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
 
 10/8/2017
 
 10:28-11:10 pause
 12:10-12:49 give up
 
 http://wwwhomes.uni-bielefeld.de/achim/highly.txt
 66    1102701600         1440   5 4 2 1 1 1 1

 12:50-14:33 read editorials and add solution
  - Euler's phi function
    - http://apps.topcoder.com/wiki/display/tc/SRM+617
    - http://sucrose.hatenablog.com/entry/2014/04/22/005557
    - http://rsujskf.s602.xrea.com/?topcoder_srm617_div1_1
  - Iclusion-exclusion principle
    - http://kmjp.hatenablog.jp/entry/2014/04/21/0900
     - count by primes
    - http://torus711.hatenablog.com/entry/20140427/1398605486
     - count by divisors with Möbius function
 
 if we mark cutting point in range [0,N], it's multiple of divisors.
 for example, cutting point of 12 is below:
 2,3,4,6,8,9,10 => 8 pieces
 
 if we denote X = { n : n is multiple of divisor of N },
 res = |X|
 
 It's not easy to count |X| directly for large N because |x| may be nearly N (very large).
 We can compute complement set of X. Let's say Y = U - X
 then res = N - |Y|
 
 |Y| = phi(N), where phi(x) is Euler's totient (Euler's phi function).
 
 phi(x) = n * ∏ { (1-1/p) : p | p is prime factor of N }
 
 We can compute prime factor of N by O(√N).
 
 Euler's totient (Euler’s phi function)
  - https://en.wikipedia.org/wiki/Euler%27s_totient_function
  - CLRS 31.1 Modular arithmetic
 
 algorithms to compute divisors and prime factors:
  - http://sucrose.hatenablog.com/entry/2014/10/10/235805
  - http://sucrose.hatenablog.com/entry/2016/11/06/234635
 
 ! the other solution by inclusion-exclusion principle by Möbius function
 
  Inclusion-exclusion principle
   - https://en.wikipedia.org/wiki/Inclusion%E2%80%93exclusion_principle
 
  We are back to count up number of multiple of divisors |X|
 
 X
 = { n : n is multiple of divisor of N }
 = { k*d : k=1..n/p-1, d | n }
 = m(d[1]) ∪ m(d[2]) ∪ .. ∪ m(d[L]), m(d) is set of multiples of d
 = ∪ { m(d[i]) : i=1..L }
 
|X|
 = | ∪ { m(d[i]) : i=1..L } |
 =              ∑{ |m(d[i])| : i=1..L }                          // one set
              - ∑{ |m(d[i]) ∩ m(d[j])| : 1<=i<j<=L }             // intersection of two sets
              + ∑{ |m(d[i]) ∩ m(d[j]) ∩ m(d[k])| : 1<=i<j<k<=L } // intersection of three sets
            ...
   (-1)^(L-1) * ∑{ |m(d[i]) ∩ .. ∩ m(d[L])| : 1<=i<j<..<=L }     // intersection of L sets
 = ∑ (-1)^(x-1) * ∑{ |m(d[i]) ∩ .. ∩ m(d[x])| : 1<=i<j<..<=L }, x=1..L // inclusion-exclusion principle
 
 1. count by primes (@kmjp's solution)
 
 counting by prime is easier by two reasons
  - number of prime factor is much smaller than divisor
   - at most 9 prime factors in [1..10^9])
  - we don't need to be worried about square factors as it's necessary in divisor's solution
 
 look at simple example N=24 = 2^3*3
 24 has distinct prime factors 2 and 3. All the multiple of divisors have factors 2 or 3.
 below is multiples of divisors of 24
 
  2 = 2     ∈ m(2)
  3 = 3     ∈        m(3)
  4 = 2^2   ∈ m(2)
  6 = 2*3   ∈ m(2) ∩ m(3)
  8 = 2^3   ∈ m(2)
  9 = 3^2   ∈        m(3)
 10 = 2(*5) ∈ m(2)
 12 = 2^2*3 ∈ m(2) ∩ m(3)
 14 = 2(*7) ∈ m(2)
 15 = 3(*5) ∈        m(3)
 16 = 2^4   ∈ m(2)
 18 = 2*3^2 ∈ m(2) ∩ m(3)
 20 = 2^2*5 ∈ m(2)
 21 = 3(*7) ∈        m(3)
 22 = 2(*11)∈ m(2)
 24 = 2^3*3 ∈ m(2) ∩ m(3)

 cut(24) = 16 as shown above
 
 cut(24)
 = |m(2)| + |m(3)| - |m(2) ∩ m(3)| // inclusion-exclusion principle
 = 24/2 + 24/3 - 24/6
 = 12 + 8 - 4
 = 16

 @kmjp is using bitmask to iterate all subset of prime factors.
 
 2. count by Möbius function (@torus711's solution)
 
 Möbius function
  - https://en.wikipedia.org/wiki/M%C3%B6bius_function
  - https://www.quora.com/profile/Surya-Kiran/Posts/A-Dance-with-Mobius-Function
  - https://discuss.codechef.com/questions/46074/coprime3-editorial

 res = ∑ -1*𝜇(d)*(N/d-1) -1
 
 this seems to be right for N=24 though, I couldn't understand correctness.
  - how efficient to calculate Mobius function?
  - basic set seems to be divisors though, I'm not sure why Möbius function calculated by prime factor is associated with sign -1^(x-1)...
 
 key:
  - cutting point is multiple of divisors
  - N is large. it's hard to count number of multiples of divisors
   - count complement set (number which is co-prime with N)
  - calculate phi(N) which shows number of co-prime with N
 
 summary:
  - I'm not smart enogh to represent cutting point by integer 👎
   - it's a key to figure out divisors
   - I was trying to make sequence of size of pieces like 2,2,1,1,2,... I'm foolish and stupid
 
 submit solutions:
  - Euler's totient
   - https://community.topcoder.com/stat?c=problem_solution&rm=321800&rd=15850&pm=13138&cr=23188657
   - https://community.topcoder.com/stat?c=problem_solution&rm=321811&rd=15850&pm=13138&cr=22756223
   - https://community.topcoder.com/stat?c=problem_solution&rm=321802&rd=15850&pm=13138&cr=23168966
 
 */

SETI primeFactors(int n) {
  SETI res;
  for(int p=2; p*p<=n; ++p) while(n%p==0) {
    res.emplace(p);
    n/=p;
  }
  if(n>1) res.emplace(n);
  return res;
}

class MyVeryLongCake {
  public:
  int cut(int N) {
    SETI ps=primeFactors(N);
    int tot=N;
    FORR(p,ps) {
      tot=tot/p*(p-1);
    }
    return N-tot;
  }
};

// CUT begin
ifstream data("MyVeryLongCake.sample");

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

bool do_test(int n, int __expected) {
    time_t startClock = clock();
    MyVeryLongCake *instance = new MyVeryLongCake();
    int __result = instance->cut(n);
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
        int T = time(NULL) - 1507483705;
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
        cout << "MyVeryLongCake (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
