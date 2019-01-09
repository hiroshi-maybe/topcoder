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
 
 9/29/2017
 
 9:21-9:33 try dijkstra's algorithm
 9:46-9:55 debug and fixed reset of edge bug. submit (527.13 pt)
 9:56 TLE :(
 10:10 give up
 
 22:25-23:30 read editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+626
  - http://purple-jwl.hatenablog.com/entry/2014/09/15/233819
    - DP
  - https://topcoder.g.hatena.ne.jp/peryaudo/
    - solution without dp (kind of greedy?)
  - http://kmjp.hatenablog.jp/entry/2014/06/29/0930
    - solution for div1 (charges<=10^9)
 
 we can make vertices of graph by pair of vertex and capacity (v,c).
 if we run Dijkstra's algorithm for the graph, it hits TLE.
 
 observe that c always decreases by 0 or 1. that means state transition is acyclic (DAG).
 that means we cap do DP. if c does not decrease, we can solve normal shortest path.
 transition from (u,c) to (v,c) for any pair of (u,v) can be precomputed.
 also we can add edge from (u,c) to (u,c-1) by weight 0 to represent state change of use of charge.
 
 dp[x][C] = mx(0,x)
 dp[z][c-1] = min(_,dp[u][c]-w(u,v)+mx(v,z)), v is adjacent from u
 res = min { dp[V-1][i] : i=0..C }
 
 23:31-24:05 add solution and system test passed.
 
 key:
  - DAG property of c reduces DP
  - transition without charge can be precomputed
 
 summary:
  - I couldn't solve though, this is very impressive and beautiful problem
  - div2 hard should not be a problem solved by just Dijkstra's algorithm 🙂
  - after reading outline of editorial, I designed recurrence relation by myself 👍
 
 */

// O(V^3+C*E*V) time
LL dp[51][1001];
LL mx[51][51];
vector<II> E[51];
class NegativeGraphDiv2 {
public:
  const LL Inf=1e18;
  long long findMin(int V, vector<int> A, vector<int> B, vector<int> W, int C) {
    REP(i,V) E[i].clear();
    REP(i,V) REP(c,C+1) dp[i][c]=Inf;
    REP(i,V) REP(j,V) mx[i][j]=Inf;
    REP(i,V) mx[i][i]=0;
    REP(i,SZ(A)) {
      int u=A[i]-1,v=B[i]-1,w=W[i];
      E[u].emplace_back(v,w);
      mx[u][v]=min((LL)w,mx[u][v]);
    }
    REP(k,V)REP(i,V)REP(j,V) mx[i][j]=min(mx[i][j], mx[i][k]+mx[k][j]);
    
    REP(i,V) dp[i][C]=mx[0][i];
    for(int c=C; c>0; --c) REP(u,V) {
      FORR(p,E[u]) REP(z,V) {
        int v=p.first; LL w=p.second;
        dp[z][c-1]=min(dp[z][c-1],dp[u][c]-w+mx[v][z]);
//        dump4(c,u,v,z);
//        dump4(dp[u][c],-w,mx[v][z],dp[z][c-1]);
      }
    }
    
    LL res=Inf;
    REP(c,C+1) res=min(res,dp[V-1][c]);
    return res;
  }
};

LL dist[51][1001];
class NegativeGraphDiv2_dijkstras_TLE {
  public:
  vector<II> E[51];
  const LL Inf=1e18;
  long long findMin(int V, vector<int> A, vector<int> B, vector<int> W, int C) {
    REP(i,V) E[i].clear();
    REP(i,V) REP(c,C+1) dist[i][c]=Inf;
    REP(i,SZ(A)) {
      int u=A[i]-1,v=B[i]-1,w=W[i];
      E[u].emplace_back(v,w);
    }
    set<III> Q; // dist,vertex,c
    Q.emplace(0,0,C); dist[0][C]=0;
    
    while(SZ(Q)) {
      auto it=Q.begin();
      int d,u,c;
      tie(d,u,c)=*it; Q.erase(it);
//      dump3(u,c,d);
      
//      if(u==V-1&&c==0) return d;
      
      FORR(p,E[u]) {
        int v=p.first; int w=p.second;
//        dump2(v,w);
        // no magic
        LL d2=d+w;
        if(d2<dist[v][c]) {
          auto it2=Q.find(make_tuple(dist[v][c],v,c));
          if(it2!=Q.end()) Q.erase(it2);
          dist[v][c]=d2;
          Q.emplace(d2,v,c);
//          dump3(v,c,d2);
        }
        
        if(c<=0) continue;
        
        // use magic
        d2=d-w;
        int c2=c-1;
        if(d2<dist[v][c2]) {
          auto it2=Q.find(make_tuple(dist[v][c2],v,c2));
          if(it2!=Q.end()) Q.erase(it2);
          dist[v][c2]=d2;
          Q.emplace(d2,v,c2);
//          dump3(v,c2,d2);
        }
      }
    }
    
    LL res=Inf;
    REP(c,C+1) res=min(res,dist[V-1][c]);
    
    return res;
  }
};

// CUT begin
ifstream data("NegativeGraphDiv2.sample");

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

bool do_test(int N, vector<int> s, vector<int> t, vector<int> weight, int charges, long long __expected) {
    time_t startClock = clock();
    NegativeGraphDiv2 *instance = new NegativeGraphDiv2();
    long long __result = instance->findMin(N, s, t, weight, charges);
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
        int N;
        from_stream(N);
        vector<int> s;
        from_stream(s);
        vector<int> t;
        from_stream(t);
        vector<int> weight;
        from_stream(weight);
        int charges;
        from_stream(charges);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, s, t, weight, charges, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1506702083;
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
        cout << "NegativeGraphDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
