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

int dp[51][51];

/**

 7/15/2017
 
 9:45-10:05 (357.39 points)
 11:25 failed system test. (train DP more! recursive relation was wrong)
 11:36 passed system test by collecting DP solution
 
 16:57 read editorials
 - http://kmjp.hatenablog.jp/entry/2016/09/19/0900
 
 17:01-17:31 add delivering DP solution
 
 */

class RepeatStringEasy {
  public:
  int maximalLength(string s) {
    int res=0;
    REP(i,SZ(s)) {
      res = max(res, 2*lcs(s.substr(0,i),s.substr(i)));
    }
    return res;
  }
  
  int lcs(string s, string t) {
    memset(dp, 0, sizeof dp);
    int M=SZ(s),N=SZ(t);

    /*
    // collecting DP
    FOR(i,1,M+1) {
      FOR(j,1,N+1) {
        if(s[i-1]==t[j-1]) {
          dp[i][j]=dp[i-1][j-1]+1;// max(dp[i-1][j-1]+1,max(dp[i-1][j], dp[i][j-1]));
        } else {
          dp[i][j]=max(dp[i-1][j], dp[i][j-1]);
        }
      }
    }
    return dp[M][N];
    */
    
    // delivering DP
    int res=0;
    REP(i,M) {
      REP(j,N) {
        if(s[i]==t[j]) {
          dp[i+1][j+1]=max(dp[i+1][j+1],dp[i][j]+1);
        } else {
          dp[i+1][j]=max(dp[i+1][j],dp[i][j]);
          dp[i][j+1]=max(dp[i][j+1],dp[i][j]);
        }
        res=max(res,dp[i+1][j+1]);
      }
    }
    return res;
  }
};

// CUT begin
ifstream data("RepeatStringEasy.sample");

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

bool do_test(string s, int __expected) {
    time_t startClock = clock();
    RepeatStringEasy *instance = new RepeatStringEasy();
    int __result = instance->maximalLength(s);
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
        string s;
        from_stream(s);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1500137138;
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
        cout << "RepeatStringEasy (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
