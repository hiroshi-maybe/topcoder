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
 
 16:46-17:03 dijkstra's algorithm
 17:34 (432.74 pt) 1WA
 17:38 add missing moves and system test passed
 
 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+637
    - Dijkstra's algorithm
    - mention to min-cut approach too
    - shorter than mine by processing each cell as different vertices
  - http://torus711.hatenablog.com/entry/20141024/1414159692
    - Dijkstra's algorithm
    - mention to min-cut approach too
  - http://kmjp.hatenablog.jp/entry/2014/10/26/1030
    - min-cut max flow (Dinic's algorithm)
 
 writer's comment:
  - http://snuke.hatenablog.com/entry/2014/10/24/014124
 
 key:
  - transform to graph problem
  - 8-connected cells are incident
  - min-cut of planar graph is shortest path
 
 summary:
  - interesting graph problem
  - figured out Dijkstra's algorithm quickly 👍
  - solved by myself 👍
  - conversion to graph was a bit complex
 
 submit solutions
  - flow
    - https://community.topcoder.com/stat?c=problem_solution&rm=324150&rd=16080&pm=13507&cr=23056829
    - https://community.topcoder.com/stat?c=problem_solution&rm=324168&rd=16080&pm=13507&cr=23172452
  - Dijkstra's algorithm
    - https://community.topcoder.com/stat?c=problem_solution&rm=324134&rd=16080&pm=13507&cr=23107134
  - Floyd-warshall
    - https://community.topcoder.com/stat?c=problem_solution&rm=324147&rd=16080&pm=13507&cr=23184967
 
 9/25/2017
 
 24:51- add solution by min-cut by @kmjp
 
 */

#define MAX_V 1100
vector< pair < int, int > >  moves = { {0,1},{0,-1},{1,0},{-1,0} };

template<class V> class MaxFlow_dinic {
public:
  void addEdge(int from, int to, V cap) {
    E[from].push_back((Edge){  to, (int)E[  to].size()  , cap});
    E[  to].push_back((Edge){from, (int)E[from].size()-1,   0}); // residual graph
  }
  
  V maxFlow(int s, int t) {
    V flow = 0;
    while (true) {
      bfs(s);
      if (level[t] < 0) return flow; // t is unreachable
      
      memset(iter, 0, sizeof(iter));
      int f;
      while ((f = dfs(s, t, numeric_limits<V>::max())) > 0) {
        flow += f;
      }
    }
    
    return flow;
  }
private:
  struct Edge { int to, rev; V cap; };
  vector<Edge> E[MAX_V]; // Graph
  int level[MAX_V]; // distance from `s`
  int iter[MAX_V];
  
  // initialize shoftest path and store in `level`
  void bfs(int s) {
    memset(level, -1, sizeof(level));
    
    queue<int> Q;
    level[s] = 0;
    Q.push(s);
    
    while (!Q.empty()) {
      int u = Q.front(); Q.pop();
      
      for (int i = 0; i < E[u].size(); i++) {
        Edge &e = E[u][i];
        int v = e.to;
        if (e.cap<=0) continue;
        if (level[v]>=0) continue; // visited
        
        level[v] = level[u] + 1;
        Q.push(v);
      }
    }
  }
  
  // find augmenting path in residual network and update f
  int dfs(int u, int t, V f) {
    if (u == t) return f;
    for (int &i = iter[u]; i < E[u].size(); i++) {
      Edge &e = E[u][i];
      V v = e.to;
      if (e.cap <= 0) continue;
      if (level[u] >= level[v]) continue;
      
      int d = dfs(v, t, min(f, e.cap));
      if (d <= 0) continue;
      e.cap -= d;
      E[v][e.rev].cap += d;
      return d;
    }
    
    return 0;
  }
};

int cap[256],top[256],bottom[256];
int mx[256][256];
int const Inf=1e8;
class ConnectingGameDiv2 {
public:
  int getmin(vector<string> board) {
    int M=SZ(board),N=SZ(board[0]);
    ZERO(cap); ZERO(top); ZERO(bottom); ZERO(mx);
    
    REP(j,N) top[board[0][j]]=bottom[board[M-1][j]]=1;
    REP(i,M)REP(j,N) ++cap[board[i][j]];
    REP(i,M)REP(j,N) FORR(m,moves) {
      int i2=i+m.first,j2=j+m.second;
      if(i2<0||i2>=M||j2<0||j2>=N) continue;
      char r1=board[i][j],r2=board[i2][j2];
      if(r1!=r2) mx[r1][r2]=1;
    }
    
    MaxFlow_dinic<int> mf;
    int source=0,sink=530;
    REP(r1,256) {
      int s=r1+1,t=r1+257;
      if(top[r1])    mf.addEdge(source,s,Inf);
      if(bottom[r1]) mf.addEdge(t,sink,Inf);
      mf.addEdge(s,t,cap[r1]);
      REP(r2,256) if(mx[r1][r2]) mf.addEdge(t,r2+1,Inf);
    }
    
    return mf.maxFlow(source,sink);
  }
};

unordered_map<int,int> W[2505];
int dist[2505];
class ConnectingGameDiv2_dijkstra {
  public:
  VI moves={-1,0,1};

  int getmin(vector<string> board) {
    int M=SZ(board),N=SZ(board[0]);
    unordered_map<char,int> S;
    REP(i,M)REP(j,N) S[board[i][j]]++;
    int V=SZ(S)+2;
    vector<char> cs;
    FORR(kvp,S) cs.push_back(kvp.first);
    sort(cs.begin(),cs.end());
    unordered_map<char,int> IM;
    REP(i,SZ(cs)) IM[cs[i]]=i;
    vector<vector<int>> B(M,vector<int>(N,-1));
    REP(i,M)REP(j,N) B[i][j]=IM[board[i][j]]+1;
    
    REP(i,V) W[i].clear();
    REP(i,M) {
      int v1=B[i][0];
      W[0][v1]=S[cs[v1-1]];
      int v2=B[i][N-1];
      W[v2][V-1]=0;
    }
    REP(i,M) REP(j,N) {
      int u=B[i][j],ru=S[cs[u-1]];
      FORR(dx,moves) {
        FORR(dy,moves) {
          int i2=i+dx,j2=j+dy;
          if(i2<0||i2>=M||j2<0||j2>=N) continue;
          int v=B[i2][j2];
          if(v==u) continue;
          int rv=S[cs[v-1]];
          
          W[u][v]=rv,W[v][u]=ru;
        }
      }
    }
    
    const int Inf=M*N;
    REP(i,V) dist[i]=Inf;
    set<II> Q; Q.emplace(0,0); dist[0]=0;
    
    while(SZ(Q)) {
      int u,d;
      auto it=Q.begin();
      tie(d,u)=*it; Q.erase(it);
      
      FORR(kvp, W[u]) {
        int v=kvp.first,w=kvp.second;
        if(dist[v]>d+w) {
          auto it2=Q.find({v,dist[v]});
          if(it2!=Q.end()) Q.erase(it2);
          dist[v]=d+w;
          Q.emplace(dist[v],v);
        }
      }
    }
    
    return dist[V-1];
  }
};

// CUT begin
ifstream data("ConnectingGameDiv2.sample");

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
    ConnectingGameDiv2 *instance = new ConnectingGameDiv2();
    int __result = instance->getmin(board);
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
        int T = time(NULL) - 1505691935;
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
        cout << "ConnectingGameDiv2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
