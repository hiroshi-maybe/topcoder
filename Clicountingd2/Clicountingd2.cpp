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
typedef vector<II> VII;

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
 
 7/17/2017
 
 9:01-9:40 time up
 18:00-19:00 learned about z-transform, read editorials and solutions
 
 Editorials
 - http://kmjp.hatenablog.jp/entry/2016/08/19/0930
 - http://hamko.hatenadiary.jp/entry/2017/04/04/134015
 
 Z-transform
 - http://d.hatena.ne.jp/todo314/20120614/1339695202
 - http://pekempey.hatenablog.com/entry/2016/10/30/205852
 
 Keys
 - z-transform DP
 - max clique
 
 21:15-21:40 add solution
 
 same solutions (brute-foce max cluque + z-transform)
 - https://community.topcoder.com/stat?c=problem_solution&rm=329116&rd=16775&pm=14372&cr=40466021
 - 
 
 solution with different max clique. Interestingly all the solutions are using z-transform after max clique.
 - DFS
  - https://community.topcoder.com/stat?c=problem_solution&rm=329118&rd=16775&pm=14372&cr=40271137
 - Efficinet O(N*2^√(2*M))? (M is numer of edges)
 - This solution is solving max clique for all subset masks without z-transform.
  - https://community.topcoder.com/stat?c=problem_solution&rm=329118&rd=16775&pm=14372&cr=40455611
 
 */

int dp[1<<20]; // set of used unknown edges -> max clique
int X[21][21];

// O(N^2*2^N+M*2^M) time
class Clicountingd2 {
public:
  int count(vector<string> g) {
    memset(dp, 0, sizeof dp);
    memset(X, 0, sizeof X);
    int N=SZ(g);
    int M=0;
    REP(j,N) REP(i,j) if(g[i][j]=='?') X[j][i]=X[i][j]=M++;
    
    REP(mask,1<<N) {
      bool clique=true;
      int x=0;
      REP(v,N) REP(u,v) if((mask&(1<<u))&&(mask&(1<<v))) {
        if(g[u][v]=='0') clique=false;
        if(g[u][v]=='?') x|=1<<X[u][v];
      }
      if(!clique) continue;
      dp[x]=max(dp[x], __builtin_popcount(mask));
    }
    
    // z-transform
    REP(i,M) REP(T,1<<M) if(T&(1<<i)) dp[T]=max(dp[T],dp[T^(1<<i)]);
    return accumulate(dp,dp+(1<<M),0);
  }
};

/*
class Clicountingd2_giveup {
  public:
  int dp[1048580][20];
  int count(vector<string> g) {
    int N=SZ(g);
    VII K;
    memset(dp,0,sizeof dp);
    REP(j,N) REP(i,j) if(g[i][j]=='?') {
      K.emplace_back(i,j);
    }
    REP(i,N) dp[0][i]=i;
    REP(i,N) {
      SETI S={i};
      while(true) {
        REP(v,N) {
          if(S.count(v)) continue;
          bool ok=true;
          FORR(u,S) {
            if(g[u][v]!='1') { ok=false; break; }
          }
        }
      }
    }
    
    return 0;
  }
};*/

// CUT begin
ifstream data("Clicountingd2.sample");

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

bool do_test(vector<string> g, int __expected) {
    time_t startClock = clock();
    Clicountingd2 *instance = new Clicountingd2();
    int __result = instance->count(g);
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
        vector<string> g;
        from_stream(g);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(g, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500307287;
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
        cout << "Clicountingd2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
