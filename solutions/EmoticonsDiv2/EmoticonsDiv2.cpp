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
 
 10/15/2017
 
 10:41-11:12 system test passed (277.85 pt)
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+612
   - greedy
  - http://torus711.hatenablog.com/entry/20140313/p1
   - dp
  - http://kmjp.hatenablog.jp/entry/2014/03/14/0900
   - solution for div1 easy (additional operatin delete one char)
 
 21:00-21:20 add BFS solution
 
 summary:
  - same as 650 in Leetcode
   - https://leetcode.com/problems/2-keys-keyboard/description/
  - I misunderstood that I could add one character 👎
 
 sutmit solutions:
   - DP
     - https://community.topcoder.com/stat?c=problem_solution&rm=320953&rd=15845&pm=13041&cr=22697716
   - greedy
     - https://community.topcoder.com/stat?c=problem_solution&rm=320963&rd=15845&pm=13041&cr=23109764
     - https://community.topcoder.com/stat?c=problem_solution&rm=320966&rd=15845&pm=13041&cr=22926309
 */

// O(N+D) time, D = ∑ { divisor of N }
int dp[1001];
class EmoticonsDiv2_dp {
  public:
  int printSmiles(int N) {
    REP(i,N+1) dp[i]=N+1;
    dp[1]=0;
    FOR(i,1,N) {
//      dp[i+1]=min(dp[i+1],dp[i]+1);
      for(int j=i+i; j<=N; j+=i) {
//        dump3(i,j,dp[i]+j/i);
        dp[j]=min(dp[j],dp[i]+j/i);
      }
//      if(i%2==0&&i+i/2<=N) dp[i+i/2]=min(dp[i+i/2],dp[i]+1);
    }
    return dp[N];
  }
};

int dist[1001][1001];
class EmoticonsDiv2 {
public:
  int printSmiles(int N) {
    REP(i,N+1)REP(j,N+1) dist[i][j]=N+1;
    queue<II> Q;
    Q.emplace(1,0); dist[1][0]=0;

    while(SZ(Q)) {
      auto p=Q.front(); Q.pop();
      int t,c; tie(t,c)=p;
      
      if(dist[t][c]>=N) continue;
      
      vector<II> xs;
      xs.emplace_back(t,t); // copy
      xs.emplace_back(t+c,c); // paste
      
      FORR(p, xs) if(p.first<=N&&dist[p.first][p.second]>dist[t][c]+1) {
        dist[p.first][p.second]=dist[t][c]+1;
        Q.emplace(p);
      }
    }
    
    int res=N+1;
    REP(i,N+1) res=min(res,dist[N][i]);
    return res;
  }
};

// CUT begin
ifstream data("EmoticonsDiv2.sample");

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

bool do_test(int smiles, int __expected) {
    time_t startClock = clock();
    EmoticonsDiv2 *instance = new EmoticonsDiv2();
    int __result = instance->printSmiles(smiles);
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
        int smiles;
        from_stream(smiles);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(smiles, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1508089283;
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
        cout << "EmoticonsDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
