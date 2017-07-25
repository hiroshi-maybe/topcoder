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

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

/**
 
 7/24/2017
 
 8:47-9:40 time up
 
 18:00-19:05 read editorial
 - http://kmjp.hatenablog.jp/entry/2016/05/05/1000
 
 19:05-20:00,23:10-23:44 read editorial
 - https://apps.topcoder.com/wiki/display/tc/SRM+690
 I cannot understand `x-2` part in `f(x,y)=f(x-2,y-1) + f(x,y-1)` 👎
 
 23:49-24:11 add solution of kmjp version.
 
 Key
 - insert in descendent order
  - We can satisfy one of two conditions to be "nice" in the first insertion. It reduces one constraint.
  - if inserting number is lower than any prior numbers, result sequence is same (no need to consider what column to be inserted)
 - Give one state which shows if first time insertion is done or not
  - to satisfy max(row x) >= K easily
 
 Other editorials
 - http://h-noson.hatenablog.jp/entry/2016/05/05/011658
 - https://www.linkedin.com/pulse/topcoder-srm690-wolfhockeyteameasy-yingwu-zhu
 - http://codeforces.com/blog/entry/44678
 
 */

LL f[2001][2001][2];
constexpr int MOD = 1e9+7;

class WolfHockeyTeamEasy {
  public:
  int count(int N, int K) {
    memset(f, 0, sizeof f);
    f[2*N][1][1]=2*N;
    for(int n=2*N-1; n>=1; --n) REP(fst,2) REP(s,2*N) if(f[n+1][s][fst]) {
      int blank = (n-s)/2;
      if(fst) {
        if(n>K&&s>0) {
           // OOO..
           // ..*..
          f[n][s-1][0] += f[n+1][s][1];
        }
        if(blank>0) {
          // OOO*.
          // .....
          f[n][s+1][1] += f[n+1][s][1]*blank,f[n][s+1][1]%=MOD;
        }
        if (blank>0&&n>K) {
          // OOO..
          // ...*.
          f[n][s+1][0] += f[n+1][s][1]*blank,f[n][s+1][0]%=MOD;
        }
      } else {
        if(s>0) {
          // OOO.OO..
          // *...O.O.
          f[n][s-1][0] += f[n+1][s][0], f[n][s-1][0]%=MOD;
        }
        if(blank>0) {
          // OOO.OO.*
          // ....O.O.
          f[n][s+1][0] += f[n+1][s][0]*blank, f[n][s+1][0]%=MOD;
        }
      }
    }
    
    return f[1][0][0];
  }
};

// CUT begin
ifstream data("WolfHockeyTeamEasy.sample");

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

bool do_test(int N, int K, int __expected) {
    time_t startClock = clock();
    WolfHockeyTeamEasy *instance = new WolfHockeyTeamEasy();
    int __result = instance->count(N, K);
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
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500911230;
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
        cout << "WolfHockeyTeamEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
