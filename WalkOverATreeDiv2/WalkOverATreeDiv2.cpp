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

/**
 
 8/19/2017
 
 17:15-18:15 TLE and time up
 
 8/20/2017
 
 10:00-10:30,12:10-13:33 read editorials
 - https://apps.topcoder.com/wiki/display/tc/SRM+666
 - http://torus711.hatenablog.com/entry/2015/10/05/230627
 
 f_r(u,i,L) = max {
    T[v]+f_r(v,0,l)+f_r(u,i+1,L-l-2),
    f_r(u,i+1,L)
  where l=0..L, v=E[u][i] }
 
 f_nr(u,i,L) = max {
    T[v]+f_r(v,0,l)+f_r(u,i+1,L-l-1),
    f_nr(u,i+1,L),
    T[v]+f_r(v,0,l)+f_nr(u,i+1,L-l-2)
  where l=0..L, v=E[u][i] }
 
 res = f_nr(0,0,L)+T[0]
 
 13:34-14:00 add solution
 
 Simpler bottom-up DP solution in dfs
  - http://kmjp.hatenablog.jp/entry/2015/08/27/0930
  - https://community.topcoder.com/stat?c=problem_solution&rm=326903&rd=16515&pm=13973&cr=23322801
 
 14:00-15:08 add dp in dfs solution
 
 Key:
 - state that represents whether path returns back to current node
 - tree DP
  - suppose we have result of e-1 subtrees. add another subtree and compute result for e subtrees
  - f(*,e) = f(*,e-1) + g(*,e,e-1)
  - in this case, children have dependency to share limited resource L. This approach works.
 
 Summary:
  - 2 hops further to solve this problem
    - add return/no-return to state
    - run DP by iterating subtrees
 
 */

vector<int> E[51];
int dp[55][101][2]; // v,length,not-last/last

class CollectingTokens {
public:
  VI T;
  int L;
  
  int maxTokens(vector<int> A, vector<int> B, vector<int> _T, int _L) {
    T=_T; L=_L;
    int V=T.size();
    REP(i,V) E[i].clear();
    for(int i=0;i<A.size(); ++i) {
      int u=A[i]-1,v=B[i]-1;
      E[u].push_back(v); E[v].push_back(u);
    }
    
    ZERO(dp);
    dfs(0,-1);
    
    return max(dp[0][L][0],dp[0][L][1]);
  }
  
  void dfs(int u, int pre) {
    REP(l,L+1) dp[u][l][0]=dp[u][l][1]=T[u];
    FORR(v,E[u]) if(v!=pre) {
      dfs(v,u);
      for(int l=L; l>=0; --l) for(int x=0; x<=l; ++x) {
        if(l-x-2>=0) {
          dp[u][l][0] = max(dp[u][l][0], dp[u][l-x-2][0]+dp[v][x][0]);
          dp[u][l][1] = max(dp[u][l][1], dp[u][l-x-2][1]+dp[v][x][0]);
        }
        if(l-x-1>=0) {
          dp[u][l][1] = max(dp[u][l][1], dp[u][l-x-1][0]+dp[v][x][1]);
        }
      }
    }
  }
};

int memo[51][51][101][2];
class CollectingTokens_rec {
public:
  VI T;
  int maxTokens(vector<int> A, vector<int> B, vector<int> _T, int L) {
    T=_T;
    int V=T.size();
    REP(i,V) E[i].clear();
    for(int i=0;i<A.size(); ++i) {
      int u=A[i]-1,v=B[i]-1;
      E[u].push_back(v); E[v].push_back(u);
    }
    
    MINUS(memo);
    return T[0]+f(0,0,L,0,-1);
  }
  
  int f(int u, int i, int L, int ret, int pre) {
    if(memo[u][i][L][ret]>=0) return memo[u][i][L][ret];
    if(i==SZ(E[u])) return 0;
    int res=0;
    int v=E[u][i];
    REP(l,L+1) {
      res=max(res,f(u,i+1,L,ret,pre));
      if(v==pre) continue;
      if (ret==0) {
        /* no return */
        
        // return from v. no return from others
        if(L-l-2>=0) res=max(res,T[v]+f(v,0,l,1,u)+f(u,i+1,L-l-2,0,pre));
        
        // no return from v, return from others
        if(L-l-1>=0) res=max(res,T[v]+f(v,0,l,0,u)+f(u,i+1,L-l-1,1,pre));
      } else {
        /* return */
        
        if(L-l-2>=0) res=max(res,T[v]+f(v,0,l,1,u)+f(u,i+1,L-l-2,1,pre));
      }
    }
    
    return memo[u][i][L][ret]=res;
  }
};

class CollectingTokens_TLE {
public:
  int maxTokens(vector<int> const &A,
                vector<int> const &B,
                vector<int> const &T,
                int L) {
    int V=T.size();
    REP(i,V) E[i].clear();
    for(int i=0;i<A.size(); ++i) {
      int u=A[i]-1,v=B[i]-1;
      E[u].push_back(v); E[v].push_back(u);
    }
    
    queue<tuple<int,int,int,LL>> Q; // u,score,l,viz
    int res=T[0];
    Q.emplace(0,T[0],0,1LL<<0);
    while(Q.size()) {
      int u,score,l; LL viz;
      tie(u,score,l,viz) = Q.front(); Q.pop();
      cout << u << ","<<score<<","<<l<<","<<viz<<endl;
      res=max(res,score);
      if(l==L) continue;
      
      for(auto &v : E[u]) {
        int score2=score+((viz&(1<<v))==0?T[v]:0);
        Q.emplace(v,score2,l+1,(LL)viz|(1LL<<v));
      }
    }
    
    return res;
  }
};

/*
 int dp[51][101];
 LL viz[51][101];
 vector<int> E[51];
 class CollectingTokens {
 public:
 int maxTokens(vector<int> const &A,
 vector<int> const &B,
 vector<int> const &T,
 int L) {
 int V=T.size();
 for(int i=0;i<A.size(); ++i) {
 int u=A[i]-1,v=B[i]-1;
 E[u].push_back(v); E[v].push_back(u);
 }
 memset(dp, 0, sizeof dp);
 memset(viz, 0, sizeof dp);
 
 int res=T[0];
 dp[0][0]=T[0]; viz[0][0]=1<<0;
 for(int u=0; u<V; ++u) for(int l=0; l<=L; ++l) if(dp[u][l]) {
 for(auto &v : E[u]) {
 int score2=dp[u][l]+((viz[u][l]&(1<<v))==0?T[v]:0);
 if(score2>dp[v][l+1]) {
 dp[v][l+1]=score2;
 viz[v][l+1]=viz[u][l]|(1<<v);
 cout << u<<"->"<<v<<"/"<<score2<<endl;
 if(l+1<=L) res=max(res,dp[v][l+1]);
 }
 }
 }
 
 return res;
 }
 };
 */

// CUT begin
ifstream data("WalkOverATreeDiv2.sample");

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

bool do_test(vector<int> A, vector<int> B, vector<int> tokens, int L, int __expected) {
    time_t startClock = clock();
    CollectingTokens *instance = new CollectingTokens();
    int __result = instance->maxTokens(A, B, tokens, L);
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
        vector<int> A;
        from_stream(A);
        vector<int> B;
        from_stream(B);
        vector<int> tokens;
        from_stream(tokens);
        int L;
        from_stream(L);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, tokens, L, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1503256157;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 999 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "WalkOverATreeDiv2 (999 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
