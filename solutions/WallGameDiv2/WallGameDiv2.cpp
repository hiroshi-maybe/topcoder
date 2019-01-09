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
 
 12/1/2017
 
 9:26-9:35 pause
 16:19-16:29 analysis
 16:29-16:49 system test passed (no bug, no compile error)
 17:00-19:00 read editorial and add simpler solution
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+580
   - a bit verbose states
  - http://kmjp.hatenablog.jp/entry/2013/05/26/0930
  - http://emkcsharp.hatenablog.com/entry/SRM580/WallGameDiv2
  - http://snuke.hatenablog.com/entry/2013/05/26/024648
   - problem writer
 
 Key:
  - Eel can force rabbit to go through specific column at each row to maximize cost
  - Rabbit cannot move upward. So if row is a part of state, state transition should be DAG => DP
 
 Summary:
  - Problem statement was a bit long though, approach was straighforward
  - I figured out DAG property and built recurrence relation
 
 */

// O(R*C^2) time, simpler implementation
int dp[51][51];
int cum[51];
class WallGameDiv2 {
public:
  int R,C;
  const int Inf = 1e5;
  void makeCum(string S) {
    cum[0]=0;
    REP(i,C) cum[i+1]=cum[i]+cost(S[i]);
  }
  int f(int y, int x) {
    if (x==y) return 0;
    return x<y?cum[y]-cum[x]:cum[x+1]-cum[y+1];
  }
  int cost(char c) {
    return c=='x'?-Inf:c-'0';
  }
  int play(vector<string> G) {
    this->R=SZ(G),this->C=SZ(G[0]);
    REP(i,R+1)REP(j,C+1) dp[i][j]=-Inf;
    dp[0][0]=0;
    
    REP(i,R-1) {
      makeCum(G[i]);
      REP(x,C) REP(y,C) {
        dp[i+1][x]=max(dp[i+1][x], dp[i][y]+f(y,x)+cost(G[i+1][x]));
      }
    }
    
    int res=-Inf;
    REP(j,C) res=max(res,dp[R-1][j]);
    return res;
  }
};

// O(R*C^2) time
class WallGameDiv2_org {
  public:
  int R,C;
  const int Inf = 1e5;
  void makeCum(string S) {
    cum[0]=0;
    REP(i,C) cum[i+1]=cum[i]+(S[i]=='x'?-Inf:S[i]-'0');
  }
  int cost(int x, int y) {
    if(x>y) swap(x,y);
    return cum[y+1]-cum[x];
  }
  int play(vector<string> G) {
    this->R=SZ(G),this->C=SZ(G[0]);
    REP(i,R+1)REP(j,C+1) dp[i][j]=-Inf;
    makeCum(G[0]);
    REP(j,C) dp[0][j]=cost(0,j);
    
    FOR(i,1,R-1) {
      makeCum(G[i]);
      REP(x,C) REP(y,C) {
        dp[i][x]=max(dp[i][x], dp[i-1][y]+cost(y,x));
      }
    }

    int res=-Inf;
    REP(j,C) res=max(res,dp[R-2][j]+(G[R-1][j]=='x'?-Inf:G[R-1][j]-'0'));
    
    return res;
  }
};

// CUT begin
ifstream data("WallGameDiv2.sample");

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

bool do_test(vector<string> costs, int __expected) {
    time_t startClock = clock();
    WallGameDiv2 *instance = new WallGameDiv2();
    int __result = instance->play(costs);
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
        vector<string> costs;
        from_stream(costs);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(costs, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1512149171;
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
        cout << "WallGameDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
