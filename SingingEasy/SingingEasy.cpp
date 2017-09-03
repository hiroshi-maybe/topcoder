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
 
 9/3/2017
 
 18:11-18:25,21:50-22:25, 22:25-23:45 (303.49 pt)
 
 state: dp[i][l]: i=current index in [0..N], l=length of continuous sung pitches before i-1 in [0..N]
 
 dp[0][0]=0
 
 // switched
 dp[i+1][0] = min(_,dp[i][l]+abs(P[i+1]-P[i-l-1]))
 // no switch
 dp[i+1][l+1] = min(_,dp[i][l]+abs(P[i+1]-P[i])
 
 res = min { dp[N-1][i] : i=0..N }
 
 editorial:
  - http://kmjp.hatenablog.jp/entry/2015/03/20/1030
  - https://apps.topcoder.com/wiki/display/tc/SRM+653
  - http://torus711.hatenablog.com/entry/20150330/1427725457
 
 f(i,j1,j2)=min(f(i+1,i,b)+c1, f(i+1,a,i)+c2)
 from this recurrence relation, we can find out that either j1 or j2 is always i-1.
 thus we don't need to remember both j1 and j2.
 
 f(i,j) = min(
    f(i+1,j)+c1,
    f(i+1,i-1)+c2)
 )
 c1 = abs(P[i]-P[i-1])
 c2 = j==-1 ? 0 : abs(P[i]-P[j])
 
 f(N,_) = 0
 
 res = f(1,-1)
 
 13:3-14:05 add editorial solution
 
 key:
  - from analysis we can drop dimension of DP to N^2
 
 summary:
  - it took a lot of time to make recurrence relation
   - eventually used length to make it
  - great problem to understand how we can reduce states
  - make recurrence relation without trick. it may help make the relation simpler
    - don't do complex thing before getting more used to it
 
 */

int memo[2005][2005];
class SingingEasy {
public:
  VI P;
  int N;
  int f(int i, int j) {
    if(i>=N) return 0;
    if(memo[i][j]>=0) return memo[i][j];
    int &res = memo[i][j];
    
    int x = j==-1 ? f(i+1,i-1) : f(i+1,i-1)+abs(P[i]-P[j]);
    int y = f(i+1,j)+abs(P[i]-P[i-1]);
    return res=min(x,y);
  }
  
  int solve(vector<int> P) {
    this->P=P;
    MINUS(memo);
    this->N=SZ(P);
    
    return f(1,-1);
  }
};

int dp[2005][2005];
class SingingEasy_dp1 {
public:
  const int Inf=2*1e9+10;
  int solve(vector<int> P) {
    int N=SZ(P);
    REP(i,N+1)REP(j,N+1) dp[i][j]=Inf;
    
    dp[0][0]=0;
    REP(i,N) REP(l,i+1) if(dp[i][l]<Inf) {
//      dump3(i,l,dp[i][l]);
      // switch
      int d=i-l-1>=0?abs(P[i+1]-P[i-l-1]):0;
      dp[i+1][0]=min(dp[i+1][0], dp[i][l]+d);
      
      // no switch
      dp[i+1][l+1]=min(dp[i+1][l+1], dp[i][l]+abs(P[i+1]-P[i]));
    }

    int res=Inf;
    REP(j,N+1) res=min(res, dp[N-1][j]);
    return res;
  }
};

class SingingEasy_wrong {
  public:
  const int Inf=2*1e9+10;
  int solve(vector<int> P) {
    int N=SZ(P);
    REP(i,N+1)REP(j,N+1) dp[i][j]=Inf;
    
    dp[0][0]=0;
    REP(i,N){
      REP(j,i) if(dp[i][j]<Inf) {
//        dump3(i,j,dp[i][j]);
        dp[i+1][j]=min(dp[i+1][j], dp[i][j]+abs(P[i]-P[i-1]));
        dp[i+1][i+1]=min(dp[i+1][i+1], dp[i][j]+abs(P[i]-P[j+1]));
      }
      if(i>0) dp[i+1][i+1]=min(dp[i+1][i+1], dp[i-1][0]);
    }
   
    int res=Inf;
    REP(j,N+1) res=min(res, dp[N][j]);
    return res;
  }
};

// CUT begin
ifstream data("SingingEasy.sample");

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

bool do_test(vector<int> pitch, int __expected) {
    time_t startClock = clock();
    SingingEasy *instance = new SingingEasy();
    int __result = instance->solve(pitch);
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
        vector<int> pitch;
        from_stream(pitch);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(pitch, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1504401086;
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
        cout << "SingingEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
