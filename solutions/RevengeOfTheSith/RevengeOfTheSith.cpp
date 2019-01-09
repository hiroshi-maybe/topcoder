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
#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

/**
 
 8/5/2017
 
 9:55-11:00 design done
 11:00-11:22 failed some samples
 11:22-12:08 another state `cnt` and passed samples
 12:08 eventually failed system test
 
 23:39-24:17 read editorials
 - http://kmjp.hatenablog.jp/entry/2016/01/14/0930
 - https://apps.topcoder.com/wiki/display/tc/SRM+678
  - equal heights give minimal cost in summation of quadratic formula
 
 f(s,*) = 0
 f(s,t) = min { cost(i,h) + f(s-i-1,t-i) : i=0...t }
 cost(i,h) = ∑ { max(0,hs[j]-D)^2 : j=0...i }
 hs[j] = i) j<h%(i+1) ? h/(i+1) + 1
        ii) otherwise h/(i+1)
 
 24:25-24:45 make recurrence relation and add solution
 
 Key:
  - straightforward DP formulat doesn't fit problem size
  - move of step affects both previous and next cost
    - top or bottom floor does not move
    - build recurrence relation focusing on what is FIXED following top or bottom steps
  - minimize cost by keeping as evenly distributed as possible
    - suppose distributing total amount S into k items. Then ∑ { v[i]^2: i=1..k } is minimal when v[i] = S/k.
    - (x+1)^2+(x-1)^2 = 2+2*x^2 > (x+0)^2 + (x+0)^2 = 2*x^2
    - reduce states by this greedy technique
 
 */

int memo[51][51];
class RevengeOfTheSith {
public:
  VI S;
  int D;
  int calcost(int i, int h) {
    int d=h/(i+1);
    int res=0;
    REP(j,i+1) {
      int h2=d+(j<h%(i+1)?1:0);
      int x=max(0,h2-D);
      res += x*x;
    }
    return res;
  }
  
  int f(int s, int t) {
    if(s==0) return 0;
    if(memo[s][t]>=0) return memo[s][t];
    
    int res=INT_MAX,h=0;
    for(int i=0; i<=t&&s-i-1>=0; ++i) {
      h += S[s-i];
      if (h>=i+1) {
        int cost = calcost(i,h);
        res = min(res,cost+f(s-i-1,t-i));
      }
    }
    
    return memo[s][t]=res;
  }
  
  int move(vector<int> steps, int T, int DD) {
    steps.insert(steps.begin(),0);
    D = DD; S=steps;
    memset(memo, -1, sizeof memo);
    
    return f(SZ(S)-1,T);
  }
};

int dp[51][51][1001];
int H[51][51][1001];
// O(N^2*D^2) time ≈3*10^9
class RevengeOfTheSith_wrong_v2 {
public:
  const int Inf=2*1e9;
  int move(vector<int> S, int T, int D) {
    REP(i,51)REP(j,51)REP(d,1001) dp[i][j][d]=Inf;
    memset(H, 0, sizeof H);
    int N=SZ(S);
    
    int SUM=accumulate(S.begin(),S.end(),0);
    
    dp[0][0][0]=0;
    
    REP(i,N) REP(cnt,N) REP(dd,SUM+1) REP(d,SUM+1) if(dp[i][cnt][d]<Inf) {
//      dump4(i,cnt,dd,d);
      int h=dd+(i>0?S[i-1]-d:0);
      if(h<=0) continue;
      int x=max(0,h-D);
      int damage = x*x;
      int cost = dp[i][cnt][d] + damage;
      int cnt2 = cnt + (dd!=S[i]);

      if (cost<dp[i+1][cnt2][dd]) {
        dp[i+1][cnt2][dd] = min(dp[i+1][cnt2][dd], cost);
        H[i+1][cnt2][dd] = H[i][cnt][d] + h;
      }
//      dump4(i+1,cnt2,dd,dp[i+1][cnt2][dd]);
    }
    
    int res=Inf;
    REP(t,T+1) REP(d,1001) if (H[N][t][d]==SUM) {
//      if (res>dp[N][t][d]) dump3(t,d,dp[N][t][d]);
      res=min(res, dp[N][t][d]);
    }
    
    return res;
  }
};

class RevengeOfTheSith_wrong_v1 {
  public:
  const int Inf=2*1e9;
  int dp[51][1001];
  int use[51][1001];
  int move(vector<int> S, int T, int D) {
    REP(i,51)REP(j,1001) dp[i][j]=Inf;
    memset(use, 0, sizeof use);
    int N=SZ(S);
    
    dp[0][0]=0;
    
    REP(i,N) REP(dd,1001) REP(d,1001) if(dp[i][d]<Inf) {
      int h=dd+(i>0?S[i-1]-d:0);
      if(h<=0) continue;
      int damage = h<=D ? 0 : h*h;
      int cost = dp[i][d] + damage;
      if (dp[i+1][dd]<cost) continue;
      int cnt = use[i][d] + (dd!=S[i]);
      if (dp[i+1][dd]==cost&&use[i+1][dd]<cnt) continue;
      dp[i+1][dd] = cost;
      use[i+1][dd] = cnt;
    }
    
    int res=Inf;
    REP(d,1001) if(use[N][d]<=T) res=min(res, dp[N][d]);
    
    return res;
  }
};

// CUT begin
ifstream data("RevengeOfTheSith.sample");

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

bool do_test(vector<int> steps, int T, int D, int __expected) {
    time_t startClock = clock();
    RevengeOfTheSith *instance = new RevengeOfTheSith();
    int __result = instance->move(steps, T, D);
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
        vector<int> steps;
        from_stream(steps);
        int T;
        from_stream(T);
        int D;
        from_stream(D);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(steps, T, D, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501952136;
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
        cout << "RevengeOfTheSith (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
