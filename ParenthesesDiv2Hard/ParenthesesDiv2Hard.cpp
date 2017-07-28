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

/**
 
 7/26/2017
 
 9:45-9:55, 17:50-18:18 give up
 18:20-19:50 read editorials and analyze
 - DP solution
  - http://pekempey.hatenablog.com/entry/2016/04/16/162812
 - Greedy count up solution (swap inside intervals first, bring lacking chars outside interval if needed more)
  - https://community.topcoder.com/stat?c=problem_solution&rm=328534&rd=16709&pm=14228&cr=22886741
  - https://community.topcoder.com/stat?c=problem_solution&rm=328554&rd=16709&pm=14228&cr=40037225
 
 21:40-22:22 add DP solution
 22:55-23:11 add greedy solution
 
 Key
 - Free to use chars outside intervals. Key is how to manage pool of available open/close parentheses
  - in DP solution, it's a part of state
  - in count up solution, use chars outside intervals only when it cannot be balanced within intervals
 
 Summary
 - I was in stuck how to handle "swap" and how to handle chars outside intervals
 - thinking about "balance" always reduces states in parenthesis pairing problems
 - possible operations
  - pool to swap in the future
  - leave it
  - do swap
  - count balance only in intervals
 
 7/28/2017
 
 official editorial found
 - https://apps.topcoder.com/wiki/display/tc/SRM+688
 
 */

class ParenthesesDiv2Hard {
public:
  int minSwaps(string s, vector<int> L, vector<int> R) {
    int N=SZ(s);
    VI ON(N, false);
    REP(i,SZ(L)) {
      FOR(k,L[i],R[i]+1) ON[k]=true;
    }
    int opool=0, cpool=0;
    REP(i,N) if(!ON[i]) {
      if(s[i]=='(') ++opool;
      else ++cpool;
    }
    
    int odebt=0,cdebt=0;
    REP(x,SZ(L)) {
      int bal=0;
      int l=L[x],r=R[x]+1;
      FOR(i,l,r) {
        if(s[i]==')') {
          if(bal<=0) ++bal, ++odebt;
          else --bal;
        } else {
          if(r-i<=bal) --bal, ++cdebt;
          else ++bal;
        }
      }
      if(bal!=0) return -1;
    }
    
    int debt = abs(odebt-cdebt);
    int s1 = min(cdebt,odebt);
    if(odebt>=cdebt) return debt<=opool ? s1+debt : -1;
    else return debt<=cpool ? s1+debt : -1;
  }
};

class ParenthesesDiv2Hard_dp {
  public:
  int offset=51;
  int dp[51][51][102][102];
  int inf=1e9;
  int minSwaps(string s, vector<int> L, vector<int> R) {
    int N=SZ(s);
    REP(i,N+1)REP(j,N+1)REP(k,102)REP(l,102)dp[i][j][k][l]=inf;
    
    VI ON(N, false);
    VI LAST(N, false);
    REP(i,SZ(L)) {
      FOR(k,L[i],R[i]+1) ON[k]=true;
      if(R[i]+1<N) LAST[R[i]+1]=true;
    }
    
    dp[0][0][offset][offset]=0;
    REP(i,N) REP(b,N) REP(o,102) REP(c,102) if(dp[i][b][o][c]!=inf) {
      if(LAST[i]&&b!=0) continue;
//      dump4(i,b,o,c); dump(dp[i][b][o][c]);
      
      if(ON[i]) {
        if(s[i]=='(') {
          // no swap
          dp[i+1][b+1][o][c]=min(dp[i+1][b+1][o][c], dp[i][b][o][c]);
          // swap
          if(b>0) dp[i+1][b-1][o+1][c-1]=min(dp[i+1][b-1][o+1][c-1], dp[i][b][o][c]+1);
        } else {
          // no swap
          if(b>0) dp[i+1][b-1][o][c]=min(dp[i+1][b-1][o][c], dp[i][b][o][c]);
          // swap
          dp[i+1][b+1][o-1][c+1]=min(dp[i+1][b+1][o-1][c+1], dp[i][b][o][c]+1);
        }
      } else {
        // even if char is not in an interval, value should be incremented.
        // otherwise it's not counted as a swap at `dp[N][0][offset][offset]/2` part
        if(s[i]=='(') {
          dp[i+1][b][o+1][c-1]=min(dp[i+1][b][o+1][c-1], dp[i][b][o][c]+1);
        } else {
          dp[i+1][b][o-1][c+1]=min(dp[i+1][b][o-1][c+1], dp[i][b][o][c]+1);
        }
        
        dp[i+1][b][o][c]=min(dp[i+1][b][o][c], dp[i][b][o][c]);
      }
    }
    
    return dp[N][0][offset][offset]==inf ? -1 : dp[N][0][offset][offset]/2;
  }
};

// CUT begin
ifstream data("ParenthesesDiv2Hard.sample");

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

bool do_test(string s, vector<int> L, vector<int> R, int __expected) {
    time_t startClock = clock();
    ParenthesesDiv2Hard *instance = new ParenthesesDiv2Hard();
    int __result = instance->minSwaps(s, L, R);
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
        vector<int> L;
        from_stream(L);
        vector<int> R;
        from_stream(R);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, L, R, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501084014;
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
        cout << "ParenthesesDiv2Hard (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
