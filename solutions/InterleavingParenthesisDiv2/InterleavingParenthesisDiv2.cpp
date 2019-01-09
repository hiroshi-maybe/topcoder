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
 
 7/12/2017
 
 SRM 718 div2
 
 18:27-19:12 225.96(pt) passed system test in the contest
 
 It took too much time to design recursive relation and bottom-up solution.
 In this case, I tried to look at both direction of `k`. So bottom-up doesn't work easily.
 
 */

int N1,N2;
string s1,s2;
constexpr int MOD = 1e9+7;
int dp[55][55][105];

int dfs(int i, int j, int k) {
  if(k<0) return 0;
  if(i>=N1&&j>=N2) {
    return k==0;
  }
  if(dp[i][j][k]>=0) return dp[i][j][k];

  LL res=0;
  if (i<N1) {
    if(s1[i]=='(') res += dfs(i+1,j,k+1), res%=MOD;
    else if(s1[i]==')') res += dfs(i+1,j,k-1), res%=MOD;
  }
  if (j<N2) {
    if(s2[j]=='(') res += dfs(i,j+1,k+1), res%=MOD;
    else if(s2[j]==')') res += dfs(i,j+1,k-1), res%=MOD;
  }

  return dp[i][j][k]=res;
}

// topdown DP, O(N1*N2*max(N1,N2)) time
class InterleavingParenthesisDiv2 {
  public:
  int countWays(string _s1, string _s2) {
    s1=_s1,s2=_s2;
    /*
    int on=0, cn=0;
    FORR(c,s1+s2) if(c=='(') ++on; else ++cn;
    if (on!=cn) return 0;
     */
    
    memset(dp, -1, sizeof dp);
    N1=SZ(s1),N2=SZ(s2);
    
    return dfs(0,0,0);
  }
};

/*
wrong answer by bottom-up DP
dp[i+1][j][k-1]+=dp[i][j][k] doesn't work because `k` is growing up in increasing order

class InterleavingParenthesisDiv2_wrong {
public:
  int countWays(string s1, string s2) {
    int on=0, cn=0;
    FORR(c,s1+s2) if(c=='(') ++on; else ++cn;
    if (on!=cn) return 0;
    
    memset(dp, 0, sizeof dp);
    dp[0][0][0]=1;
    int N1=SZ(s1),N2=SZ(s2);
    REP(k,on) {
      REP(i,N1) {
        REP(j,N2) {
          if(s1[i]=='(') dp[i+1][j][k+1]+=dp[i][j][k], dp[i+1][j][k+1]%=MOD;
          else if(k>0&&s1[i]==')') dp[i+1][j][k-1]+=dp[i][j][k], dp[i+1][j][k-1]%=MOD;
          if(s2[j]=='(') dp[i][j+1][k+1]+=dp[i][j][k], dp[i][j+1][k+1]%=MOD;
          else if(k>0&&s2[j]==')') dp[i][j+1][k-1]+=dp[i][j][k], dp[i][j+1][k-1]%=MOD;
          dump4(i,j+1,k+1,dp[i][j+1][k+1]);
        }
      }
    }
    
    //    REP(i,2)REP(j,2)REP(k,1) dump4(i,j,k,dp[i][j][k]);
    
    return dp[N1][N2][];
  }
};
 */

// CUT begin
ifstream data("InterleavingParenthesisDiv2.sample");

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

bool do_test(string s1, string s2, int __expected) {
    time_t startClock = clock();
    InterleavingParenthesisDiv2 *instance = new InterleavingParenthesisDiv2();
    int __result = instance->countWays(s1, s2);
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
        string s1;
        from_stream(s1);
        string s2;
        from_stream(s2);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s1, s2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499909221;
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
        cout << "InterleavingParenthesisDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
