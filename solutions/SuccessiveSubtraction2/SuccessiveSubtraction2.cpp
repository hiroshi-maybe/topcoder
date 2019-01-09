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
 
 9/2/2017
 
 10:14-10:45,11:00-11:25 time up

 11:25-12:17 read editorials and add solution
 - http://mayokoex.hatenablog.com/entry/2015/03/30/124538
 - https://apps.topcoder.com/wiki/display/tc/SRM+654
 - http://kmjp.hatenablog.jp/entry/2015/03/28/1000
 - https://bitbucket.org/temp_impl/topcodersrm/src/tip/SRMClass/0601-0700/Srm654/SuccessiveSubtraction2.cs?fileviewer=file-view-default
 
 dp[1][0][0] = X[0]
 dp[i+1][0][cnt]   = max(_, dp[i][0][cnt] - X[i])
 dp[i+1][1][cnt+1] = max(_, dp[i][0][cnt] - X[i])
 dp[i+1][0][cnt]   = max(_, dp[i][1][cnt] + X[i])
 dp[i+1][0][cnt]   = max(_, dp[i][1][cnt] + X[i])
 res = max { dp[N][s][cnt] : s=0,1 cnt=0..2 }
 
 key:
  - plus sign shows up at most two intervals
    - A-(B-(C-D)-E) = A-B+C-D+E
  - To calcualte maximal sum, we need to remember how many parenthesis did we use
 
 summary:
  - no idea which leads to solution came up 👎
  - implementation was straightforward though, there was a bug
    - X[i] could be a negative number. initial value of min should not be zero
 
 */

const int Inf=100*2005;
int dp[2001][2][3];
class SuccessiveSubtraction2 {
  public:
  int f(VI X) {
    int N=SZ(X);
    if(N==1) return X[0];
    REP(i,N+1)REP(s,2)REP(cnt,3) dp[i][s][cnt]=-Inf;
    dp[1][0][0]=X[0];
    FOR(i,1,N) REP(cnt,3) {
      if(dp[i][0][cnt]>-Inf) {
        // - -> -
        dp[i+1][0][cnt]=max(dp[i+1][0][cnt], dp[i][0][cnt]-X[i]);
        // - -> +
        if(cnt<2) dp[i+1][1][cnt+1]=max(dp[i+1][1][cnt+1], dp[i][0][cnt]-X[i]);
      }
      if(dp[i][1][cnt]>-Inf) {
        // + -> -
        dp[i+1][0][cnt]=max(dp[i+1][0][cnt], dp[i][1][cnt]+X[i]);
        // + -> +
        dp[i+1][1][cnt]=max(dp[i+1][1][cnt], dp[i][1][cnt]+X[i]);
      }
    }
    
    int res=-Inf;
    REP(s,2)REP(cnt,3) res=max(res, dp[N][s][cnt]);
    return res;
  }
  
  vector<int> calc(vector<int> A, vector<int> P, vector<int> V) {
    VI res;
    VI X=A;
    
    REP(i,SZ(P)) {
      X[P[i]]=V[i];
      res.push_back(f(X));
    }
    
    return res;
  }
};

// CUT begin
ifstream data("SuccessiveSubtraction2.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<int> a, vector<int> p, vector<int> v, vector<int> __expected) {
    time_t startClock = clock();
    SuccessiveSubtraction2 *instance = new SuccessiveSubtraction2();
    vector<int> __result = instance->calc(a, p, v);
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
        vector<int> a;
        from_stream(a);
        vector<int> p;
        from_stream(p);
        vector<int> v;
        from_stream(v);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, p, v, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1504372474;
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
        cout << "SuccessiveSubtraction2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
