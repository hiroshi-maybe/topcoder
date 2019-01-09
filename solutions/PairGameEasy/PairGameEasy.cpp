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
 
 10/5/2017
 
 8:31-8:35 system test passed (490.84 pt)
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+620
   - dfs, bfs, greedy
  - http://torus711.hatenablog.com/entry/20140511/1399827663
   - greedy
 
 21:09-21:13 add greedy solution by simulating backward state transition
 
 solutions in contest:
  - dp
   - https://community.topcoder.com/stat?c=problem_solution&rm=322143&rd=15853&pm=13161&cr=23141356
   - https://community.topcoder.com/stat?c=problem_solution&rm=322122&rd=15853&pm=13161&cr=23147569
  - BFS
   - https://community.topcoder.com/stat?c=problem_solution&rm=322145&rd=15853&pm=13161&cr=23187012
  - DFS
   - https://community.topcoder.com/stat?c=problem_solution&rm=322135&rd=15853&pm=13161&cr=23018719
 
 */

class PairGameEasy {
public:
  const string yes="Able to generate",no="Not able to generate";
  string able(int a, int b, int c, int d) {
    while(min(c,d)>0) {
      if(c==a&&d==b) return yes;
      if(c>d) c-=d;
      else d-=c;
    }
    return no;
  }
};

int dp[1001][1001];
class PairGameEasy_dp {
  public:
  const string yes="Able to generate",no="Not able to generate";
  string able(int a, int b, int c, int d) {
    ZERO(dp);
    dp[a][b]=1;
    for(int x=1;x<=1000;++x) for(int y=1;y<=1000;++y) if(dp[x][y]) {
      if(x+y<=1000) dp[x+y][y]=1,dp[x][x+y]=1;
    }
    return dp[c][d]?yes:no;
  }
};

// CUT begin
ifstream data("PairGameEasy.sample");

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

bool do_test(int a, int b, int c, int d, string __expected) {
    time_t startClock = clock();
    PairGameEasy *instance = new PairGameEasy();
    string __result = instance->able(a, b, c, d);
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
        int a;
        from_stream(a);
        int b;
        from_stream(b);
        int c;
        from_stream(c);
        int d;
        from_stream(d);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, c, d, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1507217472;
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
        cout << "PairGameEasy (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
