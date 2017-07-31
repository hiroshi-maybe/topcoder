#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <set>

using namespace std;

#define dumpAR(ar) for(auto &x : (ar)) { cout << x << ','; } cout << endl;

vector<int> bellmanford(int V, vector<unordered_map<int, int>> E, int s) {
  vector<int> res(V, INT_MAX);
  res[s] = 0;
  
  for(int t=0; t<V-1; ++t) {
    for(int u=0; u<V; ++u) {
      for(auto &kvp : E[u]) {
        int v = kvp.first;
        int w = kvp.second;
        if (res[u]==INT_MAX) continue;
        res[v] = min(res[v], res[u] + w);
      }
    }
  }
  
  for(int u=0; u<V; ++u) {
    for(auto &kvp : E[u]) {
      int v = kvp.first;
      int w = kvp.second;
      if (res[u]==INT_MAX) continue;
      // negative-weight cycle detected
      if (res[v]!=INT_MAX && res[v] > res[u] + w) {
        cout << "cycle detected " << u << "->" << v << endl;
        return {};
      }
    }
  }
  
  return res;
}

vector<int> dijkstra(int V, vector<unordered_map<int, int>> E, int s) {
  vector<int> visited(V, false);
  vector<int> res(V, INT_MAX);
  set<pair<int,int>> Q;
  
  res[s] = 0;
  Q.emplace(0, s);
  
  while(Q.size()) {
    auto it = *(Q.begin()); Q.erase(it);
    int u = it.second;
    visited[u] = true;
    
    for(auto &kvp : E[u]) {
      int v = kvp.first, w = kvp.second;
      assert(w>=0);
      
      if (visited[v]) continue;
      if (res[u]==INT_MAX) continue;
      
      auto vi=Q.find({res[v], v});
      if (vi!=Q.end()) Q.erase(vi);
      
      res[v] = min(res[v], res[u] + w);
      Q.emplace(res[v], v);
    }
  }
  
  return res;
}

vector<vector<int>> floydWarshall(vector<vector<int>> W) {
  if (W.empty()) return W;
  int V=W.size();
  
  for(int k=0; k<V; ++k) {
    for(int i=0; i<V; ++i) {
      for(int j=0; j<V; ++j) {
        if (W[i][k]==INT_MAX || W[k][j]==INT_MAX) continue;
        W[i][j] = min(W[i][j], W[i][k]+W[k][j]);
      }
    }
  }
  
  return W;
}

vector<vector<int>> johnson(vector<unordered_map<int, int>> E, int V) {
  if (E.empty()) return {{}};
  
  // initialize G'
  int V2 = V+1;
  vector<unordered_map<int, int>> E2(E.begin(), E.end());
  E2.push_back(unordered_map<int, int>());
  for(int i=0; i<V2; ++i) E2[V][i] = 0;
  
  // get h(i) by bellman-ford
  vector<int> H = bellmanford(V2, E2, V);
  if (H.empty()) return {};
  
  for(int u=0; u<V; ++u) {
    auto &es = E2[u];
    for(auto &kvp : es) {
      int v=kvp.first;
      E[u][v] = kvp.second + H[u] - H[v];
    }
  }
  
  // calc distance by Dijkstra
  vector<vector<int>> D;
  for(int u=0; u<V; ++u) {
    D.push_back(dijkstra(V, E, u));
    for(int v=0; v<D[u].size(); ++v) {
      if (D[u][v] != INT_MAX) D[u][v] += H[v] - H[u];
    }
  }
  
  return D;
}

/**
 
 Build Strongly Connected Components a.k.a. SCCs (CLRS 22.5)
 
 Θ(V+E) time
 
 Usage:
 
 ```
 SCC scc(V);
 scc.edge(u1,v1); scc.edge(u2,v2); ...
 scc.build()
 scc.contract()
 ```
 
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

/***********************   test code below   ***********************/

// helper

void print(vector<vector<int>> Mx) {
  for(int i=0; i<Mx.size(); ++i) {
    dumpAR(Mx[i]);
  }
}

void assertVec(vector<int> actual, vector<int> expected) {
  assert(actual.size()==expected.size());
  for(int i=0; i<actual.size(); ++i) {
    assert(actual[i]==expected[i]);
  }
}
void assertVVec(vector<vector<int>> actual, vector<vector<int>> expected) {
  assert(actual.size()==expected.size());
  for(int i=0; i<actual.size(); ++i) {
    assertVec(actual[i], expected[i]);
  }
}

int toi(char c) { return c-'a'; }

void assertComponents(unordered_set<char> c, SCC &scc) {
  int cid=scc.cid[toi(*c.begin())];
  for(char u : c) assert(scc.cid[toi(u)]==cid);
}

// main

int main(int argc, char const *argv[]) {
  int Inf = INT_MAX;
  // floyd-warshall test
  // CLRS Figure 25.2
  vector<vector<int>> W = {
    {   0, Inf, Inf, Inf,  -1, Inf },
    {   1,   0, Inf,   2, Inf, Inf },
    { Inf,   2,   0, Inf, Inf,  -8 },
    {  -4, Inf, Inf,   0,   3, Inf },
    { Inf,   7, Inf, Inf,   0, Inf },
    { Inf,   5,  10, Inf, Inf,   0 }
  };
  vector<vector<int>> fwres = floydWarshall(W);
  
  vector<vector<int>> fwresExpected = {
    {  0,  6, Inf,  8, -1, Inf},
    { -2,  0, Inf,  2, -3, Inf},
    { -5, -3,   0, -1, -6,  -8},
    { -4,  2, Inf,  0, -5, Inf},
    {  5,  7, Inf,  9,  0, Inf},
    {  3,  5,  10,  7,  2,   0},
  };
  assertVVec(fwres, fwresExpected);

  // Johnson test
  int V=(int)W.size();
  vector<unordered_map<int, int>> E0(V);
  for(int u=0; u<V; ++u) {
    for(int v=0; v<V; ++v) {
      if (W[u][v]!=INT_MAX) E0[u][v] = W[u][v];
    }
  }
  vector<vector<int>> jhres = johnson(E0, V);
  assertVVec(jhres, fwresExpected);
  
  // bellmanford test
  // CLRS Figure 24.4
  vector<unordered_map<int, int>> E1 = {
    { {1,6}, {3,7} },
    { {2,5}, {3,8}, {4,-4} },
    { {1,-2} },
    { {2,-3}, {4,9} },
    { {0,2}, {2,7} }
  };
  
  vector<int> bres = bellmanford(E1.size(), E1, 0);
  
  vector<int> bresExpected = { 0,2,4,7,-2 };
  assertVec(bres, bresExpected);
  
  // Dijkstra's algorithm test
  // CLRS Figure 24.6
  vector<unordered_map<int, int>> E2 = {
    { {1,10}, {3,5} },
    { {2,1}, {3,2} },
    { {4,4} },
    { {1,3}, {2,9}, {4,2} },
    { {0,7}, {2,6} }
  };
  
  vector<int> dres = dijkstra(E2.size(), E2, 0);
  
  vector<int> dresExpected = { 0,8,9,5,7 };
  assertVec(dres, dresExpected);
  
  // Strongly connected component test
  // CLRS Figure 22.9
  SCC scc(8);
  set<pair<char,char>> E3={
    {'a','b'},
    {'b','c'},{'b','f'},{'b','e'},
    {'c','d'},{'c','g'},
    {'d','c'},{'d','h'},
    {'e','a'},{'e','f'},
    {'f','g'},
    {'g','f'},{'g','h'},
    {'h','h'}
  };
  for(auto p : E3) scc.edge(toi(p.first), toi(p.second));
  scc.build();
  
  unordered_set<char> c1={'a','b','e'};
  unordered_set<char> c2={'c','d'};
  unordered_set<char> c3={'f','g'};
  unordered_set<char> c4={'h'};
  
  assertComponents(c1,scc);
  assertComponents(c2,scc);
  assertComponents(c3,scc);
  assertComponents(c4,scc);
  
  scc.contract();
  
  int cid1=scc.cid[toi(*(c1.begin()))];
  int cid2=scc.cid[toi(*(c2.begin()))];
  int cid3=scc.cid[toi(*(c3.begin()))];
  int cid4=scc.cid[toi(*(c4.begin()))];
  
  vector<int> cid1Expected = { cid2, cid3 };
  assertVec(scc.G_SCC[cid1], cid1Expected);
  vector<int> cid2Expected = { cid3, cid4 };
  assertVec(scc.G_SCC[cid2], cid2Expected);
  vector<int> cid3Expected = { cid4 };
  assertVec(scc.G_SCC[cid3], cid3Expected);
  vector<int> cid4Expected = {  };
  assertVec(scc.G_SCC[cid4], cid4Expected);
}
