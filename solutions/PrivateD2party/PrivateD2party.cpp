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
 
 8/27/2017
 
 16:10-16:30 submit (350.44 pt)
 18:30 system test failed
 ok I should detect cycle
 19:04 implement union-found and system test passed

 editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+660
  - http://kmjp.hatenablog.jp/entry/2015/06/04/1000
 
 key:
  - deep analysis of dependency graph is important
  - res = |V| - |C| where C = set of cycles
  - cycle detection can be performed by DFS
   - mark visited table by start of search when visited
   - if search reaches visited node with the same start node, they are in cycle
 
 summary:
  - imagined that topological order matters for invitation order intuitively
  - also my first analysis was that complete graph would drop one participant. however it was not correct.
    - actually cycle matters
    - I analyzed cycle case before submit though, I didn't pay much attention. Submit solution with this misunderstanding
  - I figured out that I need to find what vertices are in cycle though, it took some time to design it.
    - eventually used floyd-warshall and union-find
    - however DFS works too
    - I tried to apply SCC library though, I made a mistake when evaluating connected component.
 
 25:43-25:47 add solution by SCC library
 25:49-25:56 add solution by DFS cycle detection
 
 */

int viz[51];
class PrivateD2party {
public:
  VI A;
  bool dfs(int u, int s) {
    viz[u]=s;
    if(A[u]==u) return false;
    int v=A[u];
    if(viz[v]!=-1) return viz[v]==s;
    return dfs(v,s);
  }
  
  int getsz(vector<int> _A) {
    A=_A;
    int c=0;
    int V=SZ(A);
    MINUS(viz);
    REP(i,V) if(viz[i]==-1 && dfs(i,i)) ++c;
    
    return V-c;
  }
};

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

class PrivateD2party_SCC {
public:
  int getsz(vector<int> A) {
    int V=SZ(A);
    SCC scc=SCC(V);
    REP(i,V) {
      if(i==A[i]) continue;
      scc.edge(i,A[i]);
    }
    scc.build();
    
    int res=V;
    FORR(cc,scc.CC) {
      if(SZ(cc)>1) res-=1;
    }
    
    return res;
  }
};

int mx[51][51];
class PrivateD2party_unionfind_floydwarshall {
  public:
  VI uf;
  int find(int u) { return uf[u]==u ? u : uf[u]=find(uf[u]); }
  void unite(int u, int v) {
    int p1=find(u),p2=find(v);
    uf[p1]=p2;
  }
  int getsz(vector<int> A) {
    int V=SZ(A);
    uf=VI(V);
    REP(i,V) uf[i]=i;
    ZERO(mx);
    REP(i,V) {
      if(i==A[i]) continue;
      mx[i][A[i]]=1;
    }
    REP(k,V)REP(i,V)REP(j,V) mx[i][j]|=mx[i][k]&&mx[k][j];
    REP(u,V)FOR(v,u+1,V) if (mx[u][v]&&mx[v][u]) unite(u,v);
    
    int res=0;
    REP(i,V) if(find(i)==i) {
      int x=1;
      REP(j,V)if(i!=j&&find(j)==i) ++x;
      if(x>1) res+=x-1;
      else ++res;
    }
    
    return res;
  }
};

// CUT begin
ifstream data("PrivateD2party.sample");

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

bool do_test(vector<int> a, int __expected) {
    time_t startClock = clock();
    PrivateD2party *instance = new PrivateD2party();
    int __result = instance->getsz(a);
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
        vector<int> a;
        from_stream(a);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1503875410;
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
        cout << "PrivateD2party (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
