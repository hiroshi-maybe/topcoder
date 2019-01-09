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
 
 9/17/2017
 
 16:05-16:45 system test passed (240.57 pt)
 21:45-22:30 add greedy solution
 22:40-22:42 add writer's greedy solution
 22:58-23:14 add solution by BFS
 
 editorial:
  - http://torus711.hatenablog.com/entry/20141024/1414159693
    - BFS
  - http://kmjp.hatenablog.jp/entry/2014/10/26/0930
    - greedy
  - https://apps.topcoder.com/wiki/display/tc/SRM+637
    - DP
 
 writer's comment:
  - http://snuke.hatenablog.com/entry/2014/10/24/014124
    - greedy or BFS
 
 key:
  - DP or greedy
 
 summary:
  - I needed to spend some time to fix one missing state transition and index bug
  - I thought there might be a greedy solution though, solved by DP for safety
 
 submit solutions:
  - many of early submits are solving by DP
  - dp
    - https://community.topcoder.com/stat?c=problem_solution&rm=324168&rd=16080&pm=13506&cr=23172452
    - https://community.topcoder.com/stat?c=problem_solution&rm=324150&rd=16080&pm=13506&cr=23056829
  - greedy
    - https://community.topcoder.com/stat?c=problem_solution&rm=324147&rd=16080&pm=13506&cr=23184967
 
 */

int dist[105];
class PathGameDiv2 {
public:
  int calc(vector<string> B) {
    int N=SZ(B[0]);
    set<II> Q;
    const int Inf=1e3;
    REP(i,2*N) dist[i]=Inf;
    if(B[0][0]=='.') Q.emplace(1,0),dist[0]=1;
    if(B[1][0]=='.') Q.emplace(1,N),dist[N]=1;
    while(SZ(Q)) {
      auto it=Q.begin();
      int d,p;
      tie(d,p)=*it; Q.erase(it);
      int i=p/N,j=p%N;
      
      int i2=i^1,j2=j,p2=i2*N+j2;
      if(B[i2][j2]=='.'&&dist[p2]>d+1) {
        dist[p2]=d+1; Q.emplace(d+1,p2);
      }
      int i3=i,j3=j+1,p3=i3*N+j3;
      if(B[i3][j3]=='.'&&dist[p3]>d+1) {
        dist[p3]=d+1; Q.emplace(d+1,p3);
      }
    }
    int mind=min(dist[N-1],dist[2*N-1]);
    return count(B[0].begin(),B[0].end(),'.')+count(B[1].begin(),B[1].end(),'.')-mind;
  }
};

// exclusive-inclusive principle
class PathGameDiv2_greedy2 {
public:
  int calc(vector<string> B) {
    int res=0,N=SZ(B[0]);
    VI es;
    REP(i,N) {
      if(B[0][i]!='.'||B[1][i]!='.') es.emplace_back(B[0][i]=='#');
      else ++res;
    }
    FOR(i,1,SZ(es)) if(es[i]!=es[i-1]) --res;
    return res;
  }
};

// observe event when '#' shows up
class PathGameDiv2_greedy1 {
public:
  int calc(vector<string> B) {
    int res=0,N=SZ(B[0]);
    vector<II> es;
    REP(i,N) if(B[0][i]!='.'||B[1][i]!='.') {
      es.emplace_back(i,B[0][i]=='#');
    }
    REP(i,SZ(es)) {
      if(i==0) res+=es[i].first;
      else res+=es[i].first-es[i-1].first-1-(es[i-1].second!=es[i].second);
    }
    if(SZ(es)) res+=N-es.back().first-1;
    else res+=N;
    return res;
  }
};

int dp[51][3];
class PathGameDiv2_dp {
  public:
  int calc(vector<string> B) {
    MINUS(dp);
    int N=SZ(B[0]);
    
    dp[0][0]=0;
    REP(i,N) REP(s,3) if(dp[i][s]>=0) {
      if(B[0][i]=='.'&&B[1][i]=='.') {
        if(s==0||s==1) dp[i+1][1]=max(dp[i+1][1],dp[i][s]+1);
        if(s==0||s==2) dp[i+1][2]=max(dp[i+1][2],dp[i][s]+1);
        dp[i+1][0]=max(dp[i+1][0],dp[i][s]);
      } else if(B[0][i]=='.'&&B[1][i]=='#'&&(s==0||s==2)) {
        dp[i+1][2]=max(dp[i+1][2], dp[i][s]);
      } else if(B[0][i]=='#'&&B[1][i]=='.'&&(s==0||s==1)) {
        dp[i+1][1]=max(dp[i+1][1], dp[i][s]);
      }
    }

    return max({dp[N][0],dp[N][1],dp[N][2]});
  }
};

// CUT begin
ifstream data("PathGameDiv2.sample");

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

bool do_test(vector<string> board, int __expected) {
    time_t startClock = clock();
    PathGameDiv2 *instance = new PathGameDiv2();
    int __result = instance->calc(board);
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
        vector<string> board;
        from_stream(board);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1505689499;
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
        cout << "PathGameDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
