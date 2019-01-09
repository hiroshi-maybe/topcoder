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

/**
 
 8/8/2017
 
 9:33-9:55 pause
 17:15-18:30 analysis
 18:30-18:40 implementation. hit TLE.
 
 18:45-19:20 read editorials
  - dp[# of node][# of L=2 simple path][# of leaves]
    - https://apps.topcoder.com/wiki/display/tc/SRM+675
      - keep adding x nodes to any leaves. then path increases by i+i*(i-1)/2, i: with grand parent, i*(i-1)/2: between children
  - dp[# of node][# of L=2 simple path][has parent?]
    - http://kmjp.hatenablog.jp/entry/2015/12/11/1030
      - reduce states by assuming only left-most child has children. where to attach children doesn't matter.
      - count # of paths which goes through current node <parent> - <current> - <child> by (x+p)*(x+p-1)/2
        - x = # of children
        - p = {1: has parent, 0: no parent}
 
 21:10-21:35 add @kmjp solution
 
 res = f(N,s,0)
 f(n,s,p) = OR { f(n-k, s-s', 1) : k=1..n-1 AND s'=(k+p)*(k+p-1)/2 AND s-s'>=0 }
 f(1,s,*) = s==0
 f(n,0,1) = n<=1
 f(n,0,0) = n<=2
 
 21:57-22:18 add official editorial solution
 
 res |= f(n-1-i,i,s-i*(i-1)/2)
 f(n,l,s) = OR { f(n-i,l-1+i, s-s') : i=1..n, s'=i+i*(i-1)/2, s-s'>=0 }
 f(0,*,s) = s==0
 
 22:37 we shouldn't need to manage # of leaves because as long as available leaves more than 1 exists, we can keep adding more leaves. The solution passes locally though, somehow segmentation fault happens in some test cases in topcoder server.
 
 Key:
  - depth doesn't matter due to the conditin that path length is exactly 2
 
 Summary
  - my analysis was catching how paths increase though, I didn't have an idea to push `s` into states.
  - my analysis was trying to count path of <parent> - <current> - <child> separatedly from <child 1> - <current> - <child 2> though, it's not necessary.
    - count # of paths where current node is center by (x + 1)*(x + 1 - 1)/2 where x is # of children. We can choose endpoints from children or parent.
 
 */

class TreeAndPathLength2_somehow_segmentation_fault_only_in_server {
public:
  int memo[51][1001];
  string ok="Possible",ng="Impossible";
  int f(int n, int s) {
    if(n==0) return s==0;
    if(memo[n][s]>=0) return memo[n][s];
    
    int res=0;
    for(int i=1; i<=n; ++i) {
      int s2=i+i*(i-1)/2;
      if(s<s2) continue;
      res|=f(n-i,s-s2);
    }
    return memo[n][s]=res;
  }
  
  string possible(int N, int s) {
    MINUS(memo);
    int res=0;
    for(int i=1; i<N; ++i) res|=f(N-1-i,s-i*(i-1)/2);
    return res ? ok : ng;
  }
};

int memo[51][51][1001];
class TreeAndPathLength2 {
public:
  string ok="Possible",ng="Impossible";
  int f(int n, int l, int s) {
    if(n==0) return s==0;
    if(memo[n][l][s]>=0) return memo[n][l][s];
    
    int res=0;
    for(int i=1; i<=n; ++i) {
      int s2=i+i*(i-1)/2;
      if(s<s2) continue;
      res|=f(n-i,l-1+i,s-s2);
    }
    return memo[n][l][s]=res;
  }
  
  string possible(int N, int s) {
    MINUS(memo);
    int res=0;
    for(int i=1; i<N; ++i) res|=f(N-1-i,i,s-i*(i-1)/2);
    return res ? ok : ng;
  }
};

class TreeAndPathLength2_dp1 {
public:
  string ok="Possible",ng="Impossible";
  int memo[51][1001][2];
  int f(int n, int s, bool p) {
//    assert(n>0);
//    if(n==1) return s==0;
    if(s==0) return (!p&&n<=2)||(p&&n<=1);
    if(memo[n][s][p]>=0) return memo[n][s][p];
    int res=false;
    for(int k=1; k<=n-1; ++k) {
      int s2=s-(k+p)*(k+p-1)/2;
      if(s2<0) continue;
      res|=f(n-k, s2, 1);
    }
    
    return memo[n][s][p]=res;
  }
  
  string possible(int N, int s) {
    MINUS(memo);
    return f(N,s,0) ? ok : ng;
  }
};

class TreeAndPathLength2_wrong {
  public:
  SETI S[51][51];
  void f(int n, int k) {
    if(SZ(S[n][k])) return;
//    dump2(n,k);
    if(k==0) return;
    if(n<=2) return;
    if(k==n) {
      S[n][k].insert(n*(n-1)/2);
      return;
    }
    
    FOR(l,1,n-k) {
      f(n-k,l);
      FORR(x,S[n-k][l]) {
        int s=k*(k-1)/2+l+x;
        S[n][k].insert(s);
      }
    }
  }
  
  string possible(int N, int s) {
    REP(i,N) REP(j,N) S[i][j].clear();
    
    FOR(k,1,N) {
      f(N-1,k);
      if (S[N-1][k].count(s)) return "Possible";
    }
  
    return "Impossible";
  }
};

// CUT begin
ifstream data("TreeAndPathLength2.sample");

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

bool do_test(int n, int s, string __expected) {
    time_t startClock = clock();
    TreeAndPathLength2 *instance = new TreeAndPathLength2();
    string __result = instance->possible(n, s);
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
        int s;
        from_stream(s);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, s, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1502209989;
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
        cout << "TreeAndPathLength2 (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
