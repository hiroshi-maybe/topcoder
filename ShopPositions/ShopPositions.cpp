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
 
 8/18/2017
 
 18:17-18:40 designed DP
 18:44 submit (601.92 pt)
 
 f(i,m1,m2,m3) = max { f(i+1,m2,m3,x)+m2*C[3*i*M+m1+m2+m3-1] : x=0...M }
 f(N, _, _, _) = 0
 
 res = max { f(0,0,m2,m3) : m2=0..M, m3=0..M }
 
 8/18/2017
 
 10:08-10:35 read editorials
  - http://kmjp.hatenablog.jp/entry/2015/09/12/0930
  - https://apps.topcoder.com/wiki/display/tc/SRM+667
 
 Profit is determined only by number of shops at i+1.
 No need to wait for computation at i+1 to get it as shown in my original recurrence relation.
 
 f(i,m1,m2) = max { f(i+1,m2,x)+m2*C[3*i*M+m1+m2+x-1 : x=0..M }
 f(N, _, _) = 0
 
 res = max { f(0,0,m2) : m2=0..M }
 
 11:14 add more efficient solution with memoized recursion
 11:41 add bottom-up DP solution
 
 dp[_][_][_]=0
 i=0..N-1,x=0..M
 dp[i+1][m2][x] = max(_, dp[i][m1][m2]+m2*C[3*i*M+m1+m2+x-1])
 res=max { dp[N][x][0] : x=0..M }
 
 key:
  - typical DP
  - computation which depends on prev state and next state
    - move index from left to right, score of current index is determined without waiting for computation of next state
 
 Summary:
  - solved 👍
  - even better to find out that state can be reduced
    - score is determined without waiting for computation of next state (need only parameter m)
 
 */

// O(N*M^3) time < 9*10^5
int dp[31][31][31];
class ShopPositions {
public:
  int maxProfit(int N, int M, vector<int> C) {
    ZERO(dp);
    
    REP(i,N) {
      REP(m1,M+1)REP(m2,M+1)REP(x,M+1) {
        dp[i+1][m2][x]=max(dp[i+1][m2][x],dp[i][m1][m2]+m2*C[3*i*M+m1+m2+x-1]);
      }
    }

    int res=0;
    REP(x,M+1) res=max(res, dp[N][x][0]);
    
    return res;
  }
};

// O(N*M^3) time < 9*10^5
int memo[31][31][31];
class ShopPositions_memo {
public:
  int N,M;
  VI C;
  int f(int i, int m1, int m2) {
    if(i==N) return 0;
    if(memo[i][m1][m2]>=0) return memo[i][m1][m2];
    int res=0;
    for(int x=0; x<=M; ++x) {
      res=max(res,f(i+1,m2,x)+m2*C[3*i*M+m1+m2+x-1]);
    }
    return memo[i][m1][m2]=res;
  }
  
  int maxProfit(int n, int m, vector<int> c) {
    N=n; M=m; C=c;
    MINUS(memo);
    
    int res=0;
    for(int m2=0; m2<=M; ++m2) {
      res=max(res, f(0,0,m2));
    }
    
    return res;
  }
};

// O(N*M^4) time < 3*10^7
class ShopPositions_org {
  public:
  int N,M;
  VI C;
  int memo[31][31][31][31];
  int f(int i, int m1, int m2, int m3) {
    if(i==N) return 0;
    if(memo[i][m1][m2][m3]>=0) return memo[i][m1][m2][m3];
    int res=0;
    for(int m4=0; m4<=M; ++m4) {
      res=max(res, f(i+1,m2,m3,m4)+m2*C[3*i*M+m1+m2+m3-1]);
    }
    return memo[i][m1][m2][m3]=res;
  }
  
  int maxProfit(int n, int m, vector<int> c) {
    N=n; M=m; C=c;
    MINUS(memo);
    
    int res=0;
    for(int m2=0; m2<=M; ++m2) for(int m3=0; m3<=M; ++m3) {
      res=max(res, f(0,0,m2,m3));
    }
    
    return res;
  }
};

// CUT begin
ifstream data("ShopPositions.sample");

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

bool do_test(int n, int m, vector<int> c, int __expected) {
    time_t startClock = clock();
    ShopPositions *instance = new ShopPositions();
    int __result = instance->maxProfit(n, m, c);
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
        vector<int> c;
        from_stream(c);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, m, c, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1503019042;
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
        cout << "ShopPositions (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
