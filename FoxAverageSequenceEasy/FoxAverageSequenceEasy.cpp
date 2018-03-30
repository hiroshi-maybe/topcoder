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
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cout
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 3/28/2018
 
 22:02-22:12 analysis
 22:13-22:39 implement and submit. ACC (501.71 pt)
 
 Editorials:
  - http://topcoder.g.hatena.ne.jp/JAPLJ/20110331
  - http://kmjp.hatenablog.jp/entry/2014/04/20/1000
  - http://kenkoooo.hatenablog.com/entry/2015/08/07/022144
  - http://mayokoex.hatenablog.com/entry/2015/05/14/234827
  - http://d.hatena.ne.jp/komiyam/20110331/1301497280
  - http://rsujskf.blog32.fc2.com/blog-entry-1907.html
 
 Key:
  - Remember below states for DP
   - Previous value to ensure A[i-2]>A[i-1]>A[i] is false
   - Keep flag of A[i-2]>A[i-1] in state. No need to rememeber A[i-2]
   - Sum up to current index to compute average
 
 Summary:
  - 1 wrong analysis during implementation
   - no need to remember prev prev value. just a flag of state of A[i-2]>A[i-1] is sufficient
  - implementation mistake
   - `b` was used instead of `any` because I changed design during implementation
   - braces warning helped me {}
    - `warning: add explicit braces to avoid dangling else [-Wdangling-else]`
 
 */

// O(N*M^4) time
const LL MOD=1000000007LL;
LL dp[41][2][40*40+1];
class FoxAverageSequence {
  public:
  bool ok(int a, int b, int num, int sum, int any) {
    if(num*b>sum) return false;
    if(!any&&a>b) return false;
    return true;
  }
  int theCount(vector<int> S) {
    ZERO(dp);
    int N=SZ(S);
    if(S[0]==-1) {
      REPE(i,40) dp[i][1][i]=1LL;
    } else {
      dp[S[0]][1][S[0]]=1LL;
    }
    REP(i,N-1) {
      int b=S[i+1],num=i+1;
      LL dp2[41][2][40*40+1]; ZERO(dp2);
      dump3(i,b,num);
      REPE(a,40)REP(any,2)REPE(sum,1600)if(dp[a][any][sum]) {
        if(b==-1) REPE(bb,40) if(ok(a,bb,num,sum,any)) {
          int any2=a>bb?0:1;
          (dp2[bb][any2][sum+bb]+=dp[a][any][sum])%=MOD;
        } else if(ok(a,b,num,sum,any)) {
           int any2=a>b?0:1;
          (dp2[b][any2][sum+b]+=dp[a][any][sum])%=MOD;
        }
      }
      swap(dp2,dp);
    }
    LL res=0;
    REPE(a,40)REP(any,2)REPE(sum,40*40) res+=dp[a][any][sum],res%=MOD;
    return res;
  }
};

// CUT begin
ifstream data("FoxAverageSequenceEasy.sample");

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

bool do_test(vector<int> seq, int __expected) {
    time_t startClock = clock();
    FoxAverageSequence *instance = new FoxAverageSequence();
    int __result = instance->theCount(seq);
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
        vector<int> seq;
        from_stream(seq);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(seq, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1522299723;
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
        cout << "FoxAverageSequenceEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
