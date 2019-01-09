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
 
 12/26/2017
 
 20:35-21:41 Time up
 21:42-22:04 Take a look at approach in editorial and add solution
 
 12/27/2017
 
 14!≫10^8. So brute-force by permutation doesn't work.
 Two approaches came up with me.
 
 1. Inclusion-exclusion principle
 
 My computation did not match sample result
 
 2. Something to use bit mask
 
 N is small (<=14). Bitmask by managing set of used number may work.
 I didn't have idea to put numbers from left to right.
 
 12/28/2017
 
 Add solution which computes probability directly
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+562
  - http://kmjp.hatenablog.jp/entry/2012/12/06/0900
  - http://topcoder.g.hatena.ne.jp/minus9d/20121211/1355235360
 
 Key:
  - Typical bit DP
  - Order doesn't matter. Put from left to right statically.
  - We can keep constraint by remembering only consecutive (last) one
 
 Summary:
  - Problem statement is unnecessarily complex and confusing
  - Typical bit DP by forcing static order. How stupid that I could not solve by myself 😡
 
 */

// counting, O(N^2*2^N) time
double memo[1<<14][51];
class RandomOption {
public:
  int N;
  int NG[15][15];
  double f(int mask, int last) {
    if(__builtin_popcount(mask)==N) return 1.0;
    double &res=memo[mask][last];
    if(res>=0) return res;
    res=0;
    int t=N-__builtin_popcount(mask);
    REP(i,N) if((mask&(1<<i))==0&&NG[last][i]==0) {
      res+=f(mask|(1<<i),i)/t;
    }
    return res;
  }
  double getProbability(int _N, vector<int> B1, vector<int> B2) {
    this->N=_N;
    ZERO(NG);
    MINUS(memo);
    REP(i,SZ(B1)) NG[B1[i]][B2[i]]=1,NG[B2[i]][B1[i]]=1;
    return f(0,N);
  }
};

// counting, O(N^2*2^N) time
class RandomOption_org {
  public:
  int N;
  LL memo[1<<14][51];
  SETI NG[15];
  LL f(int mask, int last) {
    if(__builtin_popcount(mask)==N) return 1LL;
    LL &res=memo[mask][last];
    if(res>=0) return res;
    res=0;
    REP(i,N) if((mask&(1<<i))==0&&NG[last].count(i)==0) {
      res+=f(mask|(1<<i),i);
    }
    return res;
  }
  double getProbability(int _N, vector<int> B1, vector<int> B2) {
    this->N=_N;
    MINUS(memo);
    REP(i,SZ(B1)) NG[B1[i]].emplace(B2[i]),NG[B2[i]].emplace(B1[i]);
    LL a=0;
    REP(i,N) a+=f(1<<i,i);
    LL b=1;
    REP(i,N) b*=i+1;
    return (double)a/b;
  }
};

// CUT begin
ifstream data("RandomOption.sample");

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

bool do_test(int keyCount, vector<int> badLane1, vector<int> badLane2, double __expected) {
    time_t startClock = clock();
    RandomOption *instance = new RandomOption();
    double __result = instance->getProbability(keyCount, badLane1, badLane2);
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
        int keyCount;
        from_stream(keyCount);
        vector<int> badLane1;
        from_stream(badLane1);
        vector<int> badLane2;
        from_stream(badLane2);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(keyCount, badLane1, badLane2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1514349315;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "RandomOption (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
