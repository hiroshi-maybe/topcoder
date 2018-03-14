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
 
 3/13/2018
 
 8:12-8:34 analysis
 8:35-8:45 implement and submit (269.99 pt), but 1WA
 9:14-9:20 fix Inf bug and ACC
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+513
    - efficient O(N*M) time algorithm
  - http://d.hatena.ne.jp/kusano_prog/20110726/1311686461
  - http://kg86.hatenablog.com/entry/20130708/1373259896
  - http://topcoder.g.hatena.ne.jp/hide5stm/
 
 24:05-24:37 add smarter solution of official editorial
 
 */
const LL MOD=1000000009;
class YetAnotherIncredibleMachine {
public:
  int countWays(vector<int> X, vector<int> L, vector<int> B) {
    sort(B.begin(),B.end());
    int N=SZ(X);
    LL res=1LL;
    REP(i,N) {
      int x=X[i],l=x-L[i],r=x;
      FORR(y,B) {
        if(l<=y&&l+L[i]>=y) l=y+1;
        if(r<=y&&r+L[i]>=y) r=y-L[i]-1;
        dump4(i,y,l,r);
      }
      dump2(l,r);
      LL cnt=max(r-l+1,0);
      res*=cnt,res%=MOD;
    }
    return res;
  }
};

class YetAnotherIncredibleMachine_org {
  public:
  int countWays(vector<int> X, vector<int> L, vector<int> B) {
    B.push_back(-1e6), B.push_back(1e6);
    sort(B.begin(),B.end());
    dumpAR(B);
    int N=SZ(X),M=SZ(B);
    LL res=1LL;
    REP(i,N) {
      LL cnt=0;
      FORE(l,X[i]-L[i],X[i]) {
        int r=l+L[i];
        REP(j,M-1) {
          int ll=B[j]+1,rr=B[j+1]-1;
          if(ll>rr) continue;
          if(l==-10000) {
            dump2(l,r);
            dump3(ll,rr,ll<=l&&r<=rr);
          }
          if(ll<=l&&r<=rr) ++cnt;
        }
      }
      res*=cnt,res%=MOD;
      dump3(i,cnt,res);
    }
    return res;
  }
};

// CUT begin
ifstream data("YetAnotherIncredibleMachine.sample");

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

bool do_test(vector<int> platformMount, vector<int> platformLength, vector<int> balls, int __expected) {
    time_t startClock = clock();
    YetAnotherIncredibleMachine *instance = new YetAnotherIncredibleMachine();
    int __result = instance->countWays(platformMount, platformLength, balls);
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
        vector<int> platformMount;
        from_stream(platformMount);
        vector<int> platformLength;
        from_stream(platformLength);
        vector<int> balls;
        from_stream(balls);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(platformMount, platformLength, balls, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1520997131;
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
        cout << "YetAnotherIncredibleMachine (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
