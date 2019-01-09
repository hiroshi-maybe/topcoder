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
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 3/19/2018
 
 23:37-24:32 analysis
 24:33-24:48 implement and ACC (185.43 pt)
 
 What I did:
  - Start from position 1 and move backward
  - Research patterns by playing around samples
 
 What I figured out
  - We can divide only by prime as described in the problem statement. # of edges in search space: 256->19
  - If divided by p, M' = M%(N/p)
  - If we keep dividing, position of M eventually reaches position 1
  - It seemed that dividing first is optimal though, I didn't have proof
 
 It seemed impossible to brute-force mix of shift and division. So I did division brute-force with memoization.
 
 Editorials:
  - http://mayokoex.hatenablog.com/entry/2015/06/17/000056
  - https://topcoder.g.hatena.ne.jp/jackpersel/20110603/1307110671
  - http://d.hatena.ne.jp/kusano_prog/20110602/1307037147
  - http://www.vexorian.com/2011/06/thoughts-after-srm-507.html
  - http://isatan.blog41.fc2.com/blog-entry-29.html
  - http://topcoder.g.hatena.ne.jp/firewood/20110612/1307897928
 
 Editorials are showing how my algorithm can be proved to be correct.
 Key is commutativity of operations and modular arithmetic.
 
 Possible scenario to solve quickly:
 
 Trying all the combination of division and shift does not fit in memory or time limit.
 We want to find "something" which simplifies problem.
 If division is performed, M' which is new M is shown as below:
 
  M' = M%(N/p)
 
 This is modular arithmetic. Let's see how shift operation can be combined by this.
 
 1. shift -> divide
  M' = (M+1)%d = M%d+1
 2. divide -> shift
  M' = M%d+1
 
 Ok. We are eventually getting the same result.
 Therefore we can try either way:
  1. Divide first and shift at last
  2. Shift first and divide at last
 
 Division happens at most 19 times. Shift happens at most 10^6 times.
 Second one exceeds time limit though, first one works.
 
 25:20-25:36 add simple solution in official editorial.
 
 Key:
  - We TLE if we brute-force order of operations. Some smart observation is needed.
  - Division and shift are mutually commutative. Shift can be always the last operation.
  - Proof of commutativity is given by modular arithmetic
   - (M±1)%y is equal to M%y±1
 
 Summary:
  - Misunderstanding that number can be divided by not only prime number but also compound number 👎👎👎👎👎👎👎👎👎👎👎
  - Too slow to figure out that division first is better than intermediate shift DDDSSS is ok. DDDSDDD is shit.
  - Search space was not clear 👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎
   - This was unclear because I've not figured out how state transitions when we just keep dividing first
   - Shift is last. Since M is given, we can remember only state `N`. State is at most 256 which is highly composite number in [1,10^6]
  - Division -> modular arithmetic is very popular
 
 */

class DivideAndShift {
public:
  vector<LL> P;
  int getLeast(int N, int M) {
    --M;
    int res=N;
    FORE(d,1,N) if(N%d==0) {
      int dd=d;
      int x=0;
      for(int p=2;p*p<=dd; ++p) while(dd%p==0) {
        ++x,dd/=p;
      }
      if(dd!=1) ++x;
      int nn=N/d;
      int m=M%nn;
//      dump2(d,x);
      SMIN(res,min(m,nn-m)+x);
    }
    return res;
  }
};


vector<LL> distinctPrimeFactors(LL n) {
  /*
   vector<LL> res=primeFactors(n);
   res.erase(unique(res.begin(),res.end()),res.end());
   return res;
   */
  assert(n>=1);
  vector<LL> res;
  for(LL p=2; p*p<=n; ++p) if(n%p==0) {
    res.push_back(p);
    while(n%p==0) n/=p;
  }
  if(n>1) res.push_back(n);
  return res;
}

// TLE. 256*10^6≈10^8 though.
class DivideAndShift_TLE {
public:
  MAPII memo;
  vector<LL> P;
  int f(int n, int m) {
    if(m==0) return 0;
    if(memo.count(n)) return memo[n];
    int res=1e8;
    FORR(p,P) if(n%p==0) SMIN(res,1+f(n/p, m%(n/p)));
    return memo[n]=res;
  }
  int getLeast(int N, int M) {
    P=distinctPrimeFactors(N);
    --M;
    int res=1e8;
    REP(s,N) {
      memo.clear();
      int d1=abs(M-s),d2=N-abs(s-M);
      int x=f(N,s);
//      dump4(s,d1,d2,x);
      res=min(res,min(d1,d2)+x);
      dump2(s,SZ(memo));
    }
    return res;
  }
};

map<II,int> memo;
class DivideAndShift_org {
  public:
  vector<LL> P;
  int f(int n, int m) {
    if(m==0) return 0;
    if(memo.count({n,m})) return memo[{n,m}];
    int res=min(m,n-m);
    FORR(p,P) if(n%p==0) SMIN(res,1+f(n/p, m%(n/p)));
    return memo[{n,m}]=res;
  }
  int getLeast(int N, int M) {
    memo.clear();
    P=distinctPrimeFactors(N);
    --M;
    return f(N,M);
  }
};

// CUT begin
ifstream data("DivideAndShift.sample");

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
    DivideAndShift *instance = new DivideAndShift();
    int __result = instance->getLeast(N, M);
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
        int T = time(NULL) - 1521527857;
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
        cout << "DivideAndShift (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
