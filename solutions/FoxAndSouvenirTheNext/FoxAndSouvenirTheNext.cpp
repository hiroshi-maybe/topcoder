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
 
 9/4/2017
 
 10:33-10:54 system test passed (342.47 pt)
 
 17:55-18:02 fix original solution with balance. it was index bug in implementation :(
 
 key:
  - typical DP problem

 summary:
  - quickly figured out DP 👍
  - made a mistake in first dp solution. wasted 10 mins 👎
 
 editorials:
  - http://kmjp.hatenablog.jp/entry/2015/03/02/0930
  - http://roiti46.hatenablog.com/entry/2015/03/02/TopCoder_SRM_651_Div2%3A_Easy%2C_Med
 
 18:20-18:46 add two interative DP solutions
 
 */
class FoxAndSouvenirTheNext_total {
public:
  int N;
  VI V;
  int memo[51][26][2501];
  int f(int i, int n, int v) {
    if(n<0||v<0) return 0;
    if(i==N) return n==0&&v==0;
    if(memo[i][n][v]>=0) return memo[i][n][v];
    int &res=memo[i][n][v];
    return res=f(i+1,n-1,v-V[i])||f(i+1,n,v);
  }
  string ableToSplit(vector<int> V) {
    N=SZ(V); this->V=V;
    int sum=accumulate(V.begin(),V.end(),0);
    if(N%2||sum%2) return "Impossible";
    MINUS(memo);
    return f(0,N/2,sum/2)?"Possible":"Impossible";
  }
};

const int offn=50,offv=2500;
int memo[51][101][5001];
class FoxAndSouvenirTheNext_balance {
  public:
  int N;
  VI V;
  int f(int i, int n, int v) {
    if(i==0) return n==0&&v==0;
    if(memo[i][n+offn][v+offv]>=0) return memo[i][n+offn][v+offv];
    int &res=memo[i][n+offn][v+offv];
    return res=f(i-1,n-1,v-V[i-1])||f(i-1,n+1,v+V[i-1]);
  }
  string ableToSplit(vector<int> V) {
    N=SZ(V); this->V=V;
    MINUS(memo);
    return f(N,0,0)?"Possible":"Impossible";
  }
};

class FoxAndSouvenirTheNext_it {
public:
  int dp[51][105][2505];
  string ableToSplit(vector<int> V) {
    int N=SZ(V);
    ZERO(dp);
    int sum=accumulate(V.begin(),V.end(),0);
    if(N%2||sum%2) return "Impossible";
    
    dp[0][0][0]=1;
    REP(i,N) REP(n,N+1) REP(v,sum) {
      dp[i+1][n+1][v+V[i]]|=dp[i][n][v];
      dp[i+1][n][v]|=dp[i][n][v];
    }
    
    return dp[N][N/2][sum/2]?"Possible":"Impossible";
  }
};

class FoxAndSouvenirTheNext {
public:
  string ableToSplit(vector<int> V) {
    int N=SZ(V);
    int dp[105][2505];
    ZERO(dp);
    int sum=accumulate(V.begin(),V.end(),0);
    if(N%2||sum%2) return "Impossible";
    
    dp[0][0]=1;
    REP(i,N) for(int n=i; n>=0; --n) for(int v=2500; v>=0; --v) {
      if(n+1<=N&&v<=2500) dp[n+1][v+V[i]]|=dp[n][v];
    }
    
    return dp[N/2][sum/2]?"Possible":"Impossible";
  }
};

// CUT begin
ifstream data("FoxAndSouvenirTheNext.sample");

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

bool do_test(vector<int> value, string __expected) {
    time_t startClock = clock();
    FoxAndSouvenirTheNext *instance = new FoxAndSouvenirTheNext();
    string __result = instance->ableToSplit(value);
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
        vector<int> value;
        from_stream(value);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(value, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1504546372;
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
        cout << "FoxAndSouvenirTheNext (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
