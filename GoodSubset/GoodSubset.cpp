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

constexpr int MOD = 1e9+7;

/*
 
 9/22/2017
 
 9:49-10:16 design
 10:17-10:32 implement and system test passed (460.92 pt)
 
 F(x*y,i+1) += F[y] if T%(x*y)==0, x=ns[i], y∈{ divisor of T }
 res = F(T,N)
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+632
  - http://kmjp.hatenablog.jp/entry/2014/09/05/1000
  - http://sucrose.hatenablog.com/entry/2014/09/05/235244
 
 key:
  - highly_composite_number(<=2095133040) = 1600
    - search space is upper-bounded by 1600 for number of divisors
  - reuse number of divisors by DP
 
 summary:
  - solved by myself without major issues 👍
  - analysis is still slow 👎
    - I mainly spent time to validate my idea by example
 
 submit solutions:
  - most of solutions are using DP by map
    - https://community.topcoder.com/stat?c=problem_solution&rm=323628&rd=16075&pm=13396&cr=23086361
    - https://community.topcoder.com/stat?c=problem_solution&rm=323635&rd=16075&pm=13396&cr=40052679
    - https://community.topcoder.com/stat?c=problem_solution&rm=323607&rd=16075&pm=13396&cr=23091809
 
 */

// O(√T+D*(lg D+N)) time, D is number of divisors of T
class GoodSubset {
  public:
  int numberOfSubsets(LL T, vector<int> ns) {
    unordered_set<int> X;
    for(int p=1; p*p<=T; ++p) if(T%p==0) {
      X.emplace(p);
      X.emplace(T/p);
    }
    vector<LL> D(X.begin(),X.end());
    sort(D.rbegin(),D.rend());
    int N=SZ(ns);
    unordered_map<int, int> F;
    for(int i=N-1; i>=0; --i) if(T%ns[i]==0) {
      LL x=ns[i];
      FORR(y,D) {
        LL xy=1LL*y*x;
        if((LL)T%xy==0) {
          F[x*y]+=F[y], F[x*y]%=MOD;
        }
      }
      ++F[x],F[x]%=MOD;
    }
    
    return F[T];
  }
};

// CUT begin
ifstream data("GoodSubset.sample");

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

bool do_test(int goodValue, vector<int> d, int __expected) {
    time_t startClock = clock();
    GoodSubset *instance = new GoodSubset();
    int __result = instance->numberOfSubsets(goodValue, d);
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
        int goodValue;
        from_stream(goodValue);
        vector<int> d;
        from_stream(d);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(goodValue, d, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1506098974;
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
        cout << "GoodSubset (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
