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
typedef pair<int,int> II;

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
 
 8/3/2017
 
 16:32-17:12 design done
 17:12-17:34 failing some samples
 18:08 fixed some bugs but still failing sample 4 :(
  - upper bound in DP
  - duplicated variable name `i`
  - count of modulos
 18:10 passed system test (338.13 pt)
 
 Summary
 - 👍 nice job to solve. should sophisticate process to design more quickly.
 - 👎 too many bugs in implementation
  - in bottom-up DP, don't miss dp[MAX][MAX][x<MAX] case
  - should have made formula for count of modulos too. spent much time to find the bug and fix it.
 
 */

int dp[55][16][16][16];
class BearFair2 {
  public:
  int count(int n, int b) {
    return n/3+((b>0)&&(n%3)>=b);
  }
  
  string isFair(int N, int B, vector<int> U, vector<int> QU) {
    U.push_back(B); QU.push_back(N);
    int Q=SZ(QU);
    memset(dp, 0, sizeof dp);
    vector<II> A;
    REP(i,Q) A.emplace_back(U[i],QU[i]);
    sort(A.begin(), A.end());
    
    dp[0][0][0][0]=1;
    REP(p,Q) {
      int preQ=p==0?0:A[p-1].second,preU=p==0?0:A[p-1].first;
      int u=A[p].first;
      int X=count(u,0)-count(preU,0), Y=count(u,1)-count(preU,1), Z=count(u,2)-count(preU,2);
      int m=A[p].second-preQ;
      
      REP(i,min(X+1,17)) REP(j,min(Y+1,17)) {
        int k=m-i-j;
        if(k<0||k>16||k>Z) continue;
        
        REP(a,17) REP(b,17) REP(c,17) {
          if(a+i<=16&&b+j<=16&&c+k<=16) dp[p+1][a+i][b+j][c+k] |= dp[p][a][b][c];
        }
      }
    }
    
    int K=N/3;
    return dp[Q][K][K][K] ? "fair" : "unfair";
  }
};

// CUT begin
ifstream data("BearFair2.sample");

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

bool do_test(int n, int b, vector<int> upTo, vector<int> quantity, string __expected) {
    time_t startClock = clock();
    BearFair2 *instance = new BearFair2();
    string __result = instance->isFair(n, b, upTo, quantity);
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
        int b;
        from_stream(b);
        vector<int> upTo;
        from_stream(upTo);
        vector<int> quantity;
        from_stream(quantity);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, b, upTo, quantity, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501803123;
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
        cout << "BearFair2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
