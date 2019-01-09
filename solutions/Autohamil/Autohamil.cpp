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
typedef vector < VI > VVI;
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
 
 7/30/2017
 
 14:39-14:51 design
 14:51-14:57 coding
 15:15 give up
 
 Code does not solve the problem
 - Bellmanford
  - to check if all the vertices are reachable from vertex 0
  - this doesn't work if graph is like A->B and A->C (no route from B to C)
    - Sample 6
 - Simple DFS
  - to check if vertices are reachable in a single path
  - this doesn't work if there is a cycle. We cannot re-visit vertices in DFS.
    - Sample 5
 
 22:06-22:54 editorials
 - http://pekempey.hatenablog.com/entry/2016/03/09/162620
 - http://kmjp.hatenablog.jp/entry/2016/03/09/0930
 - https://apps.topcoder.com/wiki/display/tc/SRM+684
 
 What we are looking for is a path which traces all the vertices in a graph.
  - this is different from Hamilton path
    - In Hamilton path we can visit each vertices ONLY ONCE though, that's not the case in this problem.
    - BTW Finding Hamilton path is NP-hard
 
 If there is a cycle , those involved vertices can be visited each other.
 Vertices involved in a cycle forms SCC (strongly connected component).
 We can do `contraction` on the strongly connected component to simplify our problem.
 Contracted graph (`component graph`) forms DAG. If there is a path to reach all the SCCs in the DAG, all the states in the automaton are reachable ("Exists").
 
 22:55-23:35 Revisit SCC in CLRS and editorials
 23:35-24:10 create SCC library
 24:10-24:38 add solution based on @pekempey approach
 
 25:41-25:48 add Floyd-Warshall solution
 
 Solution 1. get SCCs by Kosaraju's algorithm and search DAG
 
 Strongly connected component
 - https://en.wikipedia.org/wiki/Strongly_connected_component
 - CLRS 22.5
 - Kosaraju's algorithm
  - https://en.wikipedia.org/wiki/Kosaraju%27s_algorithm
 
 Solution 2. use Floyd-warshall
 
 No path in below conditions
 - There is a vertex which is not reachable from vertex `0`
 - If all the vertices are reachable from `0`...
  - In any node u and v, if there is a path u->v or v->u, those nodes are traceable
  - However if there is neither path u->v nor v->u, no path to go thorough both u and v
 - Those conditions are easily tested by Floyd-Warshall
 
 Key
 - Reduce search space by strongly connected component (solution 1)
 - reachability from 0 is obvious. If figured out u->v or v->u path condition, Floyd-Warshall can be easily applied
 
 Summary
 - Shouldn't start coding until problem is `solved` on the paper
 - Looks easy at a first glance. However it's not so straightforward. Nice problem.
 - Good chance to create SCC library
 
 */

/**

 Build Strongly Connected Components a.k.a. SCCs (CLRS 22.5)

 Usage:
  SCC scc(V);
  scc.edge(u1,v1); scc.edge(u2,v2); ...
  scc.make()
  scc.contract()
 
 */
struct SCC {
public:
  // input
  int V;
  vector<vector<int>> G, G_T; /* G_T=(V,E_T) where E_T = {(u,v):(v,u)∈E} */
  SCC(int V): V(V), G(V), G_T(V), cid(V, -1), viz(V) {}
  void edge(int u, int v) {
    assert(u<V&&v<V);
    G[u].push_back(v);
    G_T[v].push_back(u);
  }
  
  // build SCCs, Θ(V+E) time
  vector<int> cid; /* vertex -> component ID */
  vector<vector<int>> CC; /* component ID -> vertices */
  void build() {
    for(int u=0; u<V; ++u) dfs(u);
    int id=0;
    for(int i=(int)fins.size()-1; i>=0; --i) if(cid[fins[i]]==-1) dfs_t(fins[i], id++);
    CC.resize(id);
    for(int u=0; u<V; ++u) CC[cid[u]].push_back(u);
  }
  
  // contract SCCs and build component graph, Θ(V+E) time
  vector<vector<int>> G_SCC;
  void contract() {
    set<pair<int, int>> es;
    for(int u=0; u<V; ++u) for(int v : G[u]) if(cid[u]!=cid[v]) es.emplace(cid[u],cid[v]);
    G_SCC.resize(CC.size());
    for(auto e : es) G_SCC[e.first].push_back(e.second);
  }
private:
  vector<int> viz, fins;
  void dfs(int u) {
    if(viz[u]) return;
    viz[u]=true;
    for(int v : G[u]) dfs(v);
    fins.push_back(u);
  }
  void dfs_t(int u, int id) {
    cid[u]=id;
    for(int v : G_T[u]) if(cid[v]==-1) dfs_t(v, id);
  }
};

class Autohamil {
public:
  int mx[51][51]={};
  string check(vector<int> z0, vector<int> z1) {
    int V=SZ(z0);
    REP(u,V) mx[u][z0[u]]=1, mx[u][z1[u]]=1, mx[u][u]=1;
    
    REP(w,V)REP(u,V)REP(v,V) mx[u][v] |= mx[u][w]&mx[w][v];
    FOR(u,1,V) if(!mx[0][u]) return "Does not exist";
    FOR(u,1,V) FOR(v,1,V) if(!mx[u][v]&&!mx[v][u]) return "Does not exist";
    return "Exists";
  }
};

class Autohamil_SCCs {
public:
  int memo[51];
  int dfs(int u, SCC &scc) {
    if(memo[u]>=0) return memo[u];
    int res=1;
    FORR(v, scc.G_SCC[u]) res=max(res, dfs(v,scc)+1);
    return memo[u]=res;
  }
  
  string check(vector<int> z0, vector<int> z1) {
    int V=SZ(z0);
    SCC scc(V);
    REP(u,V) {
      scc.edge(u,z0[u]), scc.edge(u,z1[u]);
    }
    scc.build();
    scc.contract();
    memset(memo,-1,sizeof memo);
    int cs=dfs(scc.cid[0], scc);
    return cs==SZ(scc.CC) ? "Exists" : "Does not exist";
  }
};


class Autohamil_wrong_dfs {
public:
  bool ok=false;
  int V;
  VI Z0,Z1;
  VVI viz;
  int vizcnt=0;
  
  void dfs(int u, int pre) {
    if(viz[u][pre]||ok) return;
    
    viz[u][pre]=true; ++vizcnt;
    if(vizcnt>=V) {
      ok=true;
      return;
    }
    
    dfs(Z0[u],u);
    dfs(Z1[u],u);
//    viz[u][pre]=false; --vizcnt;
  }
  
  string check(vector<int> z0, vector<int> z1) {
    Z0=z0, Z1=z1;
    V=SZ(z0);
    viz=VVI(V+1,VI(V+1,false));
    
    dfs(0,V);
    
    return ok ? "Exists" : "Does not exist";
  }
};


class Autohamil_wrong_bellmanford {
  public:
  string check(vector<int> z0, vector<int> z1) {
    int V=SZ(z0);
    int Inf=1e9;
    VI dist(V,Inf);
    dist[0]=0;
    REP(_,V) REP(u,V) if(dist[u]<Inf) {
      int v0 = z0[u];
      dist[v0] = min(dist[v0], dist[u]+1);
      int v1 = z1[u];
      dist[v1] = min(dist[v1], dist[u]+1);
    }
    
    dumpAR(dist);
    
    bool ok=true;
    REP(i,V) if(dist[i]>=Inf) ok=false;
    
    return ok ? "Exists" : "Does not exist";
  }
};

// CUT begin
ifstream data("Autohamil.sample");

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

bool do_test(vector<int> z0, vector<int> z1, string __expected) {
    time_t startClock = clock();
    Autohamil *instance = new Autohamil();
    string __result = instance->check(z0, z1);
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
        vector<int> z0;
        from_stream(z0);
        vector<int> z1;
        from_stream(z1);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(z0, z1, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1501450745;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Autohamil (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
