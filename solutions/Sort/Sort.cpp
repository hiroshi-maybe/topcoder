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
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 2/8/2018
 
 9:38-10:10 analysis
 10:11-11:21 Samples don't pass. Pause.
 18:00-18:16 fixed a bug and ACC
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+535
  - http://kmjp.hatenablog.jp/entry/2014/01/06/0900
 
 Key:
  - two steps
   - find corresponding digit sum first and rank `k` in it
   - build `k`-th number in lexicographical order
 
 Summary:
  - It took tons of time to implement though, I solved by myself 👍
   - Nobody solved during the contest
  - Very tough implementation
  - I should get more used to this kind of counting problem
   - Handling relative index is sometimes confusing for me
  - Don't panic even if implementation is not straighforward!
   - If there is a bug in implementation, I sometimes add wrong adhoc code without paying attention
   - That messes up because I need to debug this wrong code later
 
 */
LL memo[19][163];
class FoxAndSorting {
  public:
  LL f(int i, int d) {
    if(d<0) return 0;
    if(i==0) return d==0;
    LL &res=memo[i][d];
    if(res>=0) return res;
    res=d==0;
    for(int x=0; x<=9; ++x) if(x<=d) {
      res+=f(i-1,d-x);
    }
//    dump3(i,d,res);
    return res;
  }
  LL dfs(int i, int D, LL k, LL cur) {
    dump4(i,D,k,cur);
    //
    if(D==0) --k;
    if(k==0) return cur;
    for(int d=0; d<=9; ++d) if(d<=D) {
      LL cnt=f(i-1,D-d);
//      dump4(i,D,d,cnt>=k);
      if(cnt<k) k-=cnt;
      else return dfs(i-1,D-d,k,10LL*cur+d);
    }
    assert(false);
    return -1;
  }
  long long get(long long K) {
    MINUS(memo);
    if(K==1) return 0;
    --K;
    for(int D=0; D<=9*18; ++D) {
      for(int d=1; d<=9; ++d) {
        LL cnt=f(17,D-d);
        if(K<=cnt) {
          // I went back and force to specify initial number `d`
          return dfs(17,D-d,K,d);
        }
        K-=cnt;
      }
    }
    dump(K);
    assert(false);
    return -1;
  }
};

// CUT begin
ifstream data("Sort.sample");

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

bool do_test(long long idx, long long __expected) {
    time_t startClock = clock();
    FoxAndSorting *instance = new FoxAndSorting();
    long long __result = instance->get(idx);
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
        long long idx;
        from_stream(idx);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(idx, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1518111503;
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
        cout << "Sort (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
