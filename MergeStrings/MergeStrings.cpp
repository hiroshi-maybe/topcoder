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

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cout
#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

/*
 
 10/10/2017
 
 9:43-10:20 system test passed (492.09 pt)
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+615
  - http://snuke.hatenablog.com/entry/2014/04/04/213741
   - problem writer's comment
  - http://torus711.hatenablog.com/entry/20140404/1396623989
  - http://kmjp.hatenablog.jp/entry/2014/04/09/1130
 
 summary:
  - figured out dp quickly
  - I spent most of time to fix index bug 👎
 
 */

// O((M+N)^3) time (O(M+N) time for string manipulation)
string dp[55][55];
class MergeStrings {
  public:
  string getmin(string S, string A, string B) {
    int N=SZ(A),M=SZ(B);
    REP(i,N+1)REP(j,M+1) dp[i][j]="_";
    dp[0][0]="";
    REP(i,N+1)REP(j,M+1) if(dp[i][j]!="_") {
      if(i<N&&(S[i+j]=='?'||S[i+j]==A[i])) {
        dp[i+1][j]=min(dp[i+1][j],dp[i][j]+A[i]);
//        dump3(i+1,j,dp[i+1][j]);
      }
      if(j<M&&(S[i+j]=='?'||S[i+j]==B[j])) {
        dp[i][j+1]=min(dp[i][j+1],dp[i][j]+B[j]);
//        dump3(i,j+1,dp[i][j+1]);
      }
    }

    /*
    string res="_";
    REP(i,M+N+1) {
      int j=M+N-i;
      dump3(i,j,dp[i][j]);
      res=min(res,dp[i][j]);
    }
     return res=="_"?"":res;
     */
    return dp[N][M]=="_"?"":dp[N][M];
  }
};

// CUT begin
ifstream data("MergeStrings.sample");

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

bool do_test(string S, string A, string B, string __expected) {
    time_t startClock = clock();
    MergeStrings *instance = new MergeStrings();
    string __result = instance->getmin(S, A, B);
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
        string S;
        from_stream(S);
        string A;
        from_stream(A);
        string B;
        from_stream(B);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, A, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1507653824;
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
        cout << "MergeStrings (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
