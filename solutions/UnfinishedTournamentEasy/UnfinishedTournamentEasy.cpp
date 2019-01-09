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
 
 12/9/2017
 
 23:12-24:07 time up

 10:30-11:00 read editorial:
  - http://kmjp.hatenablog.jp/entry/2017/11/30/0930
 
 11:00-11:10 add solution
 
   V(X)
 = ∑ { (X[i]-E(X))^2 : i=0..N-1 }
 = E(X^2) - E(X)^2
 
   E(X)
 = ∑ { win(i)/(N-1) } / N
 = 1/N*(N-1) * ∑ win(i)
 = 1/N*(N-1) * N*(N-1)/2  // becaue there is no draw in tornament by N teams
 = 1/2 (=0.5)
 
   V(X)
 = E(X^2) - E(X)^2
 = ∑ (win(i)/(N-1))^2 - (0.5)^2
 = 1/(N-1)^2 * ∑ win(i)^2 - 0.25
 
 Now we want to maximize ∑ win(i)^2
 
 Look at sample 0:
 
  |012
 -+---
 0|-??
 1|?-?
 2|??-
 
 Easy idea is assigning W/L in static order like 0->1->2->...
 However size of search space is 2^(N*(N-1)/2) >10^57. So it doesn't work for N<=20
 It's also hard to apply DP due to this large search space.
 
 Now we understand that order matters. If we assign W in specific priority, we'll get win(i) for all `i`.
 For example, if win priority order is {0,1,2}, we can apply W from 0.
 Eventually we'll get matrix as below:
 
  |012
 -+---
 0|-WW
 1|L-W
 2|LL-

 If we want to try all the orders, it will take N!<20!≈2*10^18. This is still too large.
 However now we can find recurrence relation in it.
 
 Suppose we are assigning W lastly for i=2. i=0,1 are already assigned.
 There can be two orders {0,1,2} or {1,0,2}.
 If we assign for 2, we don't need to know if former order was {0,1} or {1,0}.
 win(0)^2>+win(1)^2 are already computed. We are interested in maxmum value of it.
 Now we can just rememer it associating with subset of assigned elements by dp[mask]
 
 We get below recurrence relation:
 
 dp[mask|(1<<i)] = max(_,dp[mask]+win(i)^2)
 
 win(i) can be computed in O(N) from mask.
 There are max N edges from state `mask`. Total runtime is O(N^2*2^N).
 
 Key;
  - We need to compute win(i) for i=0..N-1 which maximizes ∑ win(i)^2
  - Reduces N! brute-force to bit DP problem
    - Order to assign W matters to compute win(i)
    - However we don't need to remember former orders to assign W to `i` to compute maximal value
 
 Summary:
  - Reduced problem to maximize ∑ win(i)^2 though, I didn't have idea how to assign W/L keeping optimal substructure for DP
  - Nice educational problem to learn how to reduce permutation brute-force to bit DP technique
  - Great chance to research about order in DP
    - If order doesn't matter, solving subproblem in arbitrary order works
     - typically in ascendent order of index
    - If order matters, problem is harder. We may want to brute force N! permutation
    - However if 12<N<=20, we may be able to find recurrence relation between mask1 and mask2 (mask1>mask2)
     - mask2 represents state that element i whose bit is ON is DONE.
     - If we can find recurrence relation between mask1 and mask2 in f(mask2)=g(f(mask1)), then we can solve it in O(2^N*T(g)) time
     - Key is finding recurrence relation so that we can remember only subset.
 
 */
double dp[1<<20];
class UnfinishedTournamentEasy {
  public:
  double maximal(vector<string> G) {
    ZERO(dp);
    int N=SZ(G);
    
    REP(mask,1<<N) {
      REP(i,N) if(((mask>>i)&1)==0) {
        int w=0;
        REP(j,N) if(G[i][j]=='W'||(G[i][j]=='?'&&((mask>>j)&1)==0)) {
          ++w;
        }
        dp[mask|(1<<i)]=max(dp[mask|(1<<i)], dp[mask]+w*w);
      }
    }
    
    return dp[(1<<N)-1]/(N-1)/(N-1)/N-0.25;
  }
};

// CUT begin
ifstream data("UnfinishedTournamentEasy.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<string> G, double __expected) {
    time_t startClock = clock();
    UnfinishedTournamentEasy *instance = new UnfinishedTournamentEasy();
    double __result = instance->maximal(G);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        vector<string> G;
        from_stream(G);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(G, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1512889943;
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
        cout << "UnfinishedTournamentEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
