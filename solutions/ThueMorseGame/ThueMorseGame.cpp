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
 
 7/11/2017
 
 8:49-9:06 design done
 9:15 stack overflow for recursion
 9:40 time up
 
 21:32 read editorials
 - "プログラミングコンテストチャレンジブック [第2版]" 4-2
 - https://www.topcoder.com/community/data-science/data-science-tutorials/algorithm-games/
 - https://apps.topcoder.com/wiki/display/tc/SRM+701
  - basic turn game DP
  - mark as T if __builtin_popcount(n) is odd
  - keep only m chunk state by `long` integer bit-mask
 
 - http://kmjp.hatenablog.jp/entry/2016/11/03/0930
 - http://www004.upp.so-net.ne.jp/s_honma/relax/stone.htm
  - Keep (M+1)*k strategy
  - In general nim game (without __builtin_popcount() rule)...
    i) n=(M+1)*k => Bob wins
    ii) otherwise => Alice wins (take stone so that remaining is (M+1)*k in Bob's turn)
  - in this case, this (M+1) cycle slides if it hits __builtin_popcount()=odd stone
 
 22:53 try turn game DP by bit-mask
 23:10 TLE for 402653184, 3 :(
 23:15 passed by popcount cache following editorial solution
 
 23:44 add solution of (M+1)*k strategy
 */

int win(int N, int M) {
  int ok=false;
  for(int m=1; m<=M; ++m) {
    if (__builtin_popcount(N-m)%2==0 && !win(N-m,M)) ok=true;
  }
  return ok;
}

class ThueMorseGame {
public:
  string get(int N, int M) {
    if (M<=2) return win(N,M) ? "Alice" : "Bob";
    
    int cur=0;
    while(cur+M+1<=N) {
      cur += M+1;
      while(__builtin_popcount(cur)%2==1) cur++;
    }
    
    return cur==N ? "Bob" : "Alice";
  }
};

// cache of __builtin_popcount()
int popcount[1<<16];

class ThueMorseGame_turnGameDP {
public:
  string get(int N, int M) {
    REP(i,1<<16) popcount[i]=__builtin_popcount(i);
    
    LL full = (1LL<<M)-1;
    LL mask = full;
    REP(i,N+1) {
      bool win=false;
      
      // 65535=2^16-1
      // `(popcount[i&65535]+popcount[i>>16])%2` === `__builtin_popcount(i)`
      if((popcount[i&65535]+popcount[i>>16])%2==1||mask!=full) {
        win = true;
      } else {
        win = false;
      }
      
      mask = (mask<<1)|win;
      mask &= full;
      assert(0<=mask);
      assert(mask<=full);
    }
    
    return (mask&1)==1 ? "Alice" : "Bob";
  }
};

/*
int dp[500000001];

class ThueMorseGame_tle {
public:
  string get(int N, int M) {
    memset(dp, 0, sizeof dp);
    
    dp[0][0]=1;
    for(int i=1; i<=M; ++i) dp[i][0]=1;
    
    for(int n=M+1; n<=N; ++n) {
      if(__builtin_popcount(n)&1) continue;
      
      REP(p,2) {
        int cp=(p+1)%2;
        
        bool lose=true;
        FOR(i,1,M+1) {
          if(__builtin_popcount(n-i)&1) continue;
          lose &= dp[n-i][cp];
        }
        
        dp[n][p]=!lose;
      }
    }
    
    return dp[N][0] ? "Alice" : "Bob";
  }
};*/

/*
int c=0;
bool dfs(int n) {
  if(n<=0) return false;
  if(memo[n]>=0) return memo[n];
  
  dump2(n, ++c);
  
  bool lose=true;
  FOR(i,1,M+1) {
    if(__builtin_popcount(n-i)&1) continue;
    lose &= dfs(n-i);
  }
  
  return memo[n]=!lose;
}

class ThueMorseGame_stackOverflow {
  public:
  int memo[500000001];
  int N,M;
  string get(int _N, int _M) {
    N=_N,M=_M;
    memset(memo, -1, sizeof memo);
    
    return dfs(N) ? "Alice" : "Bob";
  }
};*/

// CUT begin
ifstream data("ThueMorseGame.sample");

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

bool do_test(int n, int m, string __expected) {
    time_t startClock = clock();
    ThueMorseGame *instance = new ThueMorseGame();
    string __result = instance->get(n, m);
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
        int m;
        from_stream(m);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, m, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499788138;
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
        cout << "ThueMorseGame (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
