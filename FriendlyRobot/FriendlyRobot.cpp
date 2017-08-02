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
 
 8/1/2017
 
 8:55-9:20 give up
 17:40-17:56 got hint from editorial
 - http://pekempey.hatenablog.com/entry/2016/02/23/154513
 - http://kmjp.hatenablog.jp/entry/2016/02/24/0900
 
 18:00-18:56 tried to build recurrence relation based on interpretaion of sequence and passed system test
  - basic approach was not bad though, took some time to find my misunderstanding of problem
    - x=1&&y=0, x=0&&y=1 handling is completely wrong. analyze problem carefully
    - condition to check is x=2&&y=0, x=0&&y=2, x=1&&y=1. don't miss the last condition
  - solution is almost same as @pekempey's solution
 
 my recurrence relation:

 ```
   i)  (x,y)==(0,0) after processing S[i..j-1]
    dp[j][k] = max(_, dp[i][k]+1)
   ii) (x,y)==(2,0),(0,2),(1,1) after processing S[i..j-1]
    dp[j][k+1] = max(_, dp[i][k]+1)
 ```
 
 19:17-19:56 back to editorial again
 - http://pekempey.hatenablog.com/entry/2016/02/23/154513
 - http://kmjp.hatenablog.jp/entry/2016/02/24/0900
 
 22:27-23:20 add @kmjp DP solution
 
  Z[x][y] = abs(x)/2 + abs(y)/2 + abs(x)%2
  dp[y][n] = min(_, dp[x][n-1]+Z[x][y]), x<y
 
 23:26-23:34 read official editorial
 - https://apps.topcoder.com/wiki/display/tc/SRM+682
  - almost same as my original solution or @pekempey's solution
 
 Other solutions
 - official editorial, @pekempey's approach
  - https://community.topcoder.com/stat?c=problem_solution&rm=328113&rd=16652&pm=14165&cr=23178685
  - https://community.topcoder.com/stat?c=problem_solution&rm=328093&rd=16652&pm=14165&cr=40380304
  - https://community.topcoder.com/stat?c=problem_solution&rm=328109&rd=16652&pm=14165&cr=40121353
 - @kmjp approach
  - https://community.topcoder.com/stat?c=problem_solution&rm=328096&rd=16652&pm=14165&cr=40261710
 
 Key
  - how to reduce states to beat O(N^4) time
  - if (x,y) is expensive, iterate sequence linearly. drop dimension.
 
 Summary
  - +1 to figure out that this is DP problem
  - +1 to understand that reducing state is the key from dp[x][y][k]
  - -1 to wrong analysis in the retry
 
 */

int dp[305][305];
int CX[305];
int CY[305];// CX[i]=S[0..i-1]
int Z[305][305]; // S[i..<j]
unordered_map<char,pair<int,int>> T={{'U',{0,1}},{'D',{0,-1}},{'L',{-1,0}},{'R',{1,0}}};

// from @kmjp's editorial
class FriendlyRobot {
public:
  int findMaximumReturns(string S, int K) {
    int N=SZ(S);
    int Inf=1e9;
    
    memset(CX, 0, sizeof CX);
    memset(CY, 0, sizeof CY);
    memset(Z, 0, sizeof Z);
    REP(i,N) {
      auto p=T[S[i]];
      int dx=p.first, dy=p.second;
      CX[i+1]=CX[i]+dx;
      CY[i+1]=CY[i]+dy;
    }
    REP(i,N+1) FOR(j,i+1,N+1) {
      int x=abs(CX[j]-CX[i]),y=abs(CY[j]-CY[i]);
      Z[i][j] = (x+y)&1 ? Inf : x/2+y/2+x%2;
    }
    
    REP(i,N+1) REP(j,N+1) dp[i][j]=Inf;
    dp[0][0]=0;
    REP(x,N+1) FOR(y,x+1,N+1) FOR(n,1,N+1) {
      // S[x..<y]
      dp[y][n] = min(dp[y][n], dp[x][n-1]+Z[x][y]);
    }
    
    int res=0;
    REP(i,N+1)REP(j,N+1)if(dp[i][j]<=K) res=max(res,j);
    return res;
  }
};

class FriendlyRobot_org {
public:
  int dp[305][305];
  int findMaximumReturns(string S, int K) {
    int N=SZ(S);
    memset(dp, -1, sizeof dp);
    dp[0][0]=0;
    REP(i,N+1) REP(k,K+1) if(dp[i][k]>=0) {
      int x=0, y=0;
      FOR(j,i+1,N+1) {
        auto p=T[S[j-1]];
        int dx=p.first, dy=p.second;
        x+=dx, y+=dy;
        if(x==0&&y==0) dp[j][k]=max(dp[j][k], dp[i][k]+1);
        if (k>=K) continue;
        /*
        if((abs(x)==2&&y==0)||(x==0&&abs(y)==2)) dp[j][k+1]=max(dp[j][k+1], dp[i][k]+1);
        if(abs(x)==1&&abs(y)==1) dp[j][k+1]=max(dp[j][k+1], dp[i][k]+1);
        // simplified as below
         */
        if(abs(x)+abs(y)==2) dp[j][k+1]=max(dp[j][k+1], dp[i][k]+1);
      }
    }
    
    int res=0;
    REP(i,N+1)REP(j,K+1) res=max(res,dp[i][j]);
    return res;
  }
};

// cannot pass sample 4
// actually wrong recursive relationship :(
class FriendlyRobot_wrong {
  public:
  int findMaximumReturns(string S, int K) {
    int N=SZ(S);
    memset(dp, -1, sizeof dp);
    dp[0][0]=0;
    REP(i,N+1) REP(k,K+1) if(dp[i][k]>=0) {
      int x=0, y=0;
      FOR(j,i+1,N+1) {
        auto p=T[S[j-1]];
        int dx=p.first, dy=p.second;
        x+=dx, y+=dy;
        if(x==0&&y==0) dp[j][k]=max(dp[j][k], dp[i][k]+1);
        else if((abs(x)==1&&y==0)||(x==0&&abs(y)==1)) if(k<K&&j+1<=N) dp[j+1][k+1]=max(dp[j+1][k+1], dp[i][k]+1);
      }
    }
    
    int res=0;
    REP(i,N+1)REP(j,K+1) res=max(res,dp[i][j]);
    return res;
  }
};

// CUT begin
ifstream data("FriendlyRobot.sample");

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

bool do_test(string instructions, int changesAllowed, int __expected) {
    time_t startClock = clock();
    FriendlyRobot *instance = new FriendlyRobot();
    int __result = instance->findMaximumReturns(instructions, changesAllowed);
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
        string instructions;
        from_stream(instructions);
        int changesAllowed;
        from_stream(changesAllowed);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(instructions, changesAllowed, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501602790;
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
        cout << "FriendlyRobot (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
