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
 
 10/1/2017
 
 16:00-16:45 analysis
 17:25 time up. it turns out that this is problem of grundy number as imagined :(
 17:49 add solution by grundy number
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+624
  - http://kmjp.hatenablog.jp/entry/2014/06/14/1000
  - http://sucrose.hatenablog.com/entry/2014/06/13/233519
 
 state transition is defined as...
 f(n) -> { (f(x), f(n-x-2)) : x=0..n }

 we can define grundy number reachable from f(n) as gr(x)^gr(n-x-2).
 now grundy number is mex (Minimum Excluded Value) of { gr(x)^gr(n-x-2) }
 gr(n) = mex({ gr(x)^gr(n-x-2) : x=0..n }
 
 res = gr(N)==0?2:1
 
 grundy number: https://www.hackerrank.com/topics/game-theory-and-grundy-numbers
 
 key:
  - state transition is defined by f(n) -> f(x), f(n-x-2)
  - grundy number of tuple of grundy numbers is defined by XOR like Nim game
 
 summary:
  - figured out state transition from N to x and n-x-2
  - figured out leveraging f(x)^f(n-x-2)
  - I haven't understood grundy number enough
   - one grundy number to one state
   - grundy number when multiple states are reachable from state s0
     - XOR { gr(s) : s is reachable state from s0 }
     - one state corresponds to one pile in Nim game
 
 */
int gr[1001];
class GameOfSegments {
public:
  int f(int n) {
    if(gr[n]>=0) return gr[n];
    SETI S;
    REP(x,n+1) {
      int y=n-x-2;
      if(y>=0) S.emplace(f(x)^f(y));
    }
    
    int g=0;
    while(S.count(g))++g;
    return gr[n]=g;
  }
  
  int winner(int N) {
    MINUS(gr);
    return f(N)?1:2;
  }
};

int G[1001];
class GameOfSegments_iterative {
public:
  int winner(int N) {
    ZERO(G);
    G[0]=G[1]=0; G[2]=G[3]=1;
    FOR(x,4,N+1) {
      SETI S;
      REP(y1,x) {
        int y2=x-y1-2;
        if(y2>=0) S.insert(G[y1]^G[y2]);
      }
      int g=0;
      while(S.count(g)) ++g;
      G[x]=g;
    }
    
    return G[N]?1:2;
  }
};

int memo[1001];
class GameOfSegments_wrong {
  public:
  bool f(int n) {
    if(n==3||n==2) return true;
    if(n<=1) return false;
    if (memo[n]>=0) return memo[n];

    bool win=false;
    FOR(x,1,n/2+1) {
//      dump2(x,n-x-2);
      bool f1=f(x),f2=f(n-x-2);
      bool ff=(f1^f2)!=0;
      win|=!ff;
    }
    return memo[n]=win;
  }
  
  int winner(int N) {
    MINUS(memo);
    return f(N)?1:2;
  }
};

// CUT begin
ifstream data("GameOfSegments.sample");

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

bool do_test(int N, int __expected) {
    time_t startClock = clock();
    GameOfSegments *instance = new GameOfSegments();
    int __result = instance->winner(N);
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
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1506898821;
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
        cout << "GameOfSegments (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
