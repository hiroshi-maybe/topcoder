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
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 10/16/2018
 
 14:34-15:01 AC by digit dp
 
 http://apps.topcoder.com/wiki/display/tc/SRM+510
 Brute-force was not in mind...
 
 Summary:
  - Decision problem or search is always candidate to fill unknown. Especially search space is not large
  - we try to resolve unknown by satisfying given conditions. If it's rare to fill the condition, search is definitely a candidate.
 
 */
LL dp[20][3][2];
class TheAlmostLuckyNumbersDivOne_org {
  public:
  LL f(string S, int less) {
    int N=SZ(S);
    ZERO(dp);
    dp[0][0][less]=1;
    REP(i,N)REP(j,3)REP(less,2) {
      int D=S[i]-'0';
      int L1=less?9:D;
      int L0=i==0?1:0;
      FORE(d,L0,L1) {
        int nonl=min(2,j+(d!=4&&d!=7));
        dp[i+1][nonl][less|(d<D)]+=dp[i][j][less];
      }
    }
    LL res=0;
    REP(j,2)REP(less,2)res+=dp[N][j][less];
    return res;
  }
  LL g(LL A) {
    string S=to_string(A);
    LL res=0;
    REP(i,SZ(S)) res+=f(S.substr(i),i!=0);
    return res;
  }
  long long find(long long a, long long b) {
    LL x=g(b);
    LL y=g(a-1);
    return x-y;
  }
};

class TheAlmostLuckyNumbersDivOne {
public:
  LL A,B;
  LL res=0;
  LL P10[17];
  void dfs(int p, int nonl, LL cur) {
    if(nonl>1) return;
    if(p==16) {
      if(A<=cur&&cur<=B){
       ++res;
      }
      return;
    }
    if(nonl<1) {
      REP(d,10) {
        int nonl2=nonl+(d!=4&&d!=7);
        if(cur==0&&d==0) --nonl2;
        dfs(p+1,nonl2,10LL*cur+d);
      }
    } else {
      dfs(p+1,nonl,10LL*cur+4LL);
      dfs(p+1,nonl,10LL*cur+7LL);
    }
  }
  long long find(long long A, long long B) {
    if(A==1e16) --A;
    if(B==1e16) --B;
    this->A=A,this->B=B;
    dfs(0,0,0);
    return res;
  }
};

// CUT begin
ifstream data("TheAlmostLuckyNumbersDivOne.sample");

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

bool do_test(long long a, long long b, long long __expected) {
    time_t startClock = clock();
    TheAlmostLuckyNumbersDivOne *instance = new TheAlmostLuckyNumbersDivOne();
    long long __result = instance->find(a, b);
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
        long long a;
        from_stream(a);
        long long b;
        from_stream(b);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1539725652;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TheAlmostLuckyNumbersDivOne (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
