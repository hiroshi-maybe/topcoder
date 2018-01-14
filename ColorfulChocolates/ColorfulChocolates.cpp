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
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define MAXS(a,b) a = max(a,b)
#define MINS(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 1/13/2018
 
 17:47-18:01 analysis
 18:09 re-analyze
 18:23 submit and system test passed (255.64 pt)

 My first design was DP to always move from left to right.
 However left to right is not always optimal due to M swap constraint
 
 In below case, 5 + 1 swaps needed
 
 A---->A: 5
    A->A: 2

 If we move right-most A to middle one, 2 + 2 swaps needed
 
 A->A   : 2
    A<-A: 2
 
 We can brute-force all i-th chocolate to "collect" from left and right.
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+551
  - http://d.hatena.ne.jp/kusano_prog/20120804/1344106849
   - sort
  - http://n-knuu.hatenablog.jp/entry/2016/06/02/225031
  - http://mayokoex.hatenablog.com/entry/2016/06/01/234244
 
 1/14/2018
 
 10:44-10:49 add solution by sort
 
 Summary:
  - My first wrong analysis of DP is not acceptable 👎
 
 */
class ColorfulChocolates {
public:
  int maximumSpread(string X, int M) {
    int N=SZ(X);
    int res=1;
    REP(a,N) {
      VI Y={0};
      int cnt=1;
      FOR(i,a+1,N) if(X[a]==X[i]) {
        Y.push_back(i-a-cnt);
        ++cnt;
      }
      cnt=1;
      for(int i=a-1; i>=0; --i) if(X[a]==X[i]) {
        Y.push_back(a-i-cnt);
        ++cnt;
      }
      sort(Y.begin(),Y.end());
      int sum=0;
      REP(i,SZ(Y)) {
        sum+=Y[i];
        if(sum<=M) res=max(res,i+1);
      }
    }
    return res;
  }
};

// O(N^2) time
class ColorfulChocolates_org {
public:
  int maximumSpread(string X, int M) {
    int N=SZ(X);
    int res=1;
    REP(a,N) {
      int l=a-1,r=a+1;
      int i=l,j=r;
      int m=M; int cnt=1;
      while(i>=0||j<N) {
        if(i>=0) {
          if (X[i]==X[a]) {
            int d=l-i;
            if(d<=m) {
              m-=d;
              ++cnt;
              --l;
            }
          }
          --i;
        }
        if(j<N) {
          if(X[j]==X[a]) {
            int d=j-r;
            if(d<=m) {
              m-=d;
              ++cnt;
              ++r;
            }
          }
          ++j;
        }
        if(m<=0) break;
      }
//      dump4(a,l,r,res);
      res=max(res,cnt);
    }
    return res;
  }
};

int dp[51][26][2501];
class ColorfulChocolates_wrong {
  public:
  int maximumSpread(string X, int M) {
    ZERO(dp);
    int N=SZ(X);
    dp[0][X[0]-'A'][0]=1;
    int res=1;
    FOR(i,1,N) REP(c,26) REPE(m,M) {
      int cc=X[i]-'A';
      dp[i][cc][m]=c==cc?dp[i-1][c][m]+1:1;
      res=max(res,dp[i][cc][m]);
      if(c!=cc) {
        dp[i][c][m+1]=1;
      }
    }
    return res;
  }
};

// CUT begin
ifstream data("ColorfulChocolates.sample");

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

bool do_test(string chocolates, int maxSwaps, int __expected) {
    time_t startClock = clock();
    ColorfulChocolates *instance = new ColorfulChocolates();
    int __result = instance->maximumSpread(chocolates, maxSwaps);
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
        string chocolates;
        from_stream(chocolates);
        int maxSwaps;
        from_stream(maxSwaps);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(chocolates, maxSwaps, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1515894444;
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
        cout << "ColorfulChocolates (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
