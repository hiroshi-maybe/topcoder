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
 
 10/30/2017
 
 8:39-9:04 system test passed (313.57 pt)
 
 editorial:
  - sort and two pointers
   - http://kmjp.hatenablog.jp/entry/2013/12/29/0930
  - brute force possible height and weith
   - https://apps.topcoder.com/wiki/display/tc/SRM+602
   - http://snuke.hatenablog.com/entry/2013/12/29/040056
     - writer's comment
  - DP (same as my solution)
   - http://torus711.hatenablog.com/entry/20131228/p2
 
 submit solutions
  - DP
   - https://community.topcoder.com/stat?c=problem_solution&rm=319964&rd=15820&pm=12928&cr=23288241
  - brute force possible height and widht
   - https://community.topcoder.com/stat?c=problem_solution&rm=319981&rd=15820&pm=12928&cr=23282585
   - https://community.topcoder.com/stat?c=problem_solution&rm=319966&rd=15820&pm=12928&cr=23137498
 
 */

class PilingRectsDiv2 {
public:
  int getmax(vector<int> X, vector<int> Y, int L) {
    int N=SZ(X);
    
    int res=0;
    for(int W=1; W<=200; ++W) for(int H=1; H<=200; ++H) {
      if(W*H<L) continue;
      int x=0;
      REP(i,N) {
        if((X[i]>=W&&Y[i]>=H) || (X[i]>=H&&Y[i]>=W)) ++x;
      }
      res=max(res,x);
    }

    return res==0?-1:res;
  }
};

int dp[201][201][50];
class PilingRectsDiv2_dp {
  public:
  int getmax(vector<int> X, vector<int> Y, int L) {
    int N=SZ(X);
    REP(i,N) if(X[i]>Y[i]) swap(X[i],Y[i]);
    
    ZERO(dp);
    dp[0][0][0]=1;
    REP(i,N) REP(x,201) REP(y,201) {
      int s=X[i],t=Y[i];
      int xx=min(x,s),yy=min(y,t);
//      if(dp[xx][yy][i+1]<dp[x][y][i]+1) dump4(i,xx,yy,dp[x][y][i]+1);
      dp[xx][yy][i+1]=max(dp[xx][yy][i+1],dp[x][y][i]+1);
      dp[x][y][i+1]=max(dp[x][y][i+1],dp[x][y][i]);
    }
    
    int res=0;
    REP(x,201)REP(y,201) if(x*y>=L)res=max(res,dp[x][y][N]);
    
    return res==0?-1:res;
  }
};

// CUT begin
ifstream data("PilingRectsDiv2.sample");

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

bool do_test(vector<int> X, vector<int> Y, int limit, int __expected) {
    time_t startClock = clock();
    PilingRectsDiv2 *instance = new PilingRectsDiv2();
    int __result = instance->getmax(X, Y, limit);
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
        vector<int> X;
        from_stream(X);
        vector<int> Y;
        from_stream(Y);
        int limit;
        from_stream(limit);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(X, Y, limit, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1509377968;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "PilingRectsDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
