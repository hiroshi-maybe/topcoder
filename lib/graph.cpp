#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <set>
#include <tuple>
using namespace std;

#define dumpAR(ar) for(auto &x : (ar)) { cout << x << ','; } cout << endl;

/*
 
 Bellman-ford algorithm, O(V*E)
 
 - Solver of single-source shortest path problem
 - negative cycle detection
 
 */
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

/*
 
 Dijkstra's algorithm, O((V+E)*lg V) time
 
 - Solver of single-source shortest path problem
 - More efficient than Bellman-ford algorithm
   - However, this cannot solve graph with negative weight
 
 */
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

/*
 
 Floyd-warshall algorithm, O(V^3)
 
  - Solver of all pairs shortest paths
  - Find connected component
   - If W[u][v]!=Inf and W[u][v]!=Inf, u and v are both part of connected component
   - If W[u][v]=Inf, vertex u is not connected to v
   - Or W[i][j]=W[i][j]|(W[i][k]&W[k][j]) directly solves connectivity problem
 
 */
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

/*
 
 Johnson's algorithm, O(V^3)
 
 - Solver of all pairs shortest paths
 
 */
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
 
 Build Strongly Connected Components a.k.a. SCCs, Θ(V+E) time
 
 - This is implementation of Kosaraju's algorithm
 - Two dfs with transpose of original graph
 
 References:
  - CLRS 22.5
  - https://en.wikipedia.org/wiki/Kosaraju%27s_algorithm
  - https://en.wikipedia.org/wiki/Strongly_connected_component
 
 There are other algorithms
  - Tarjan's algorithm
   - https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm
   - find cycle with stack which keeps vertices in the current path
  - Path-based strong component algorithm
   - https://en.wikipedia.org/wiki/Path-based_strong_component_algorithm
   - dfs with two stacks
 
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

/*
 
 # Eulerian cycle (tour), O(E) time
 
 Cycle which visits every "edge" exactly once
 
 ## References:
 
 - https://en.wikipedia.org/wiki/Eulerian_path
 - CLRS problem 22-3
 - CLRS 34. NP-Completeness
 - https://leetcode.com/problems/reconstruct-itinerary/description/
 - https://discuss.leetcode.com/topic/36383/share-my-solution
 - https://www.geeksforgeeks.org/eulerian-path-and-circuit/
 - http://www.geeksforgeeks.org/hierholzers-algorithm-directed-graph/
 
 ## Undirected graph
 
 - There is Eulerian CYCLE when ALL the vertices have odd degree
 - There is Eulerian PATH when ONLY 2 vertices have odd degree
 
 ## Directed graph
 
 - There is Eulerian CYCLE when both below conditions are satisfied
  a. every vertex has equal in degree and out degree
  b. All of its vertices with nonzero degree belong to a single SCC
 
 - There is Eulerian PATH
  a. At most one vertex has (out-degree)−(in-degree)=1
  b. At most one vertex has (in-degree)−(out-degree)=1
  c. Every other vertex has equal in-degree and out-degree
  d. All of its vertices with nonzero degree belong to a single connected component of the underlying undirected graph.
 
 ## Construction of Euler cycles
 
 - Hierholzer's algorithm, O(E) time
 
 # Hamilton cycle, NP-complete
 
 Cycle (path) which visits every "vertex" exactly once.
 
 Reference:
  - https://en.wikipedia.org/wiki/Hamiltonian_path
 
 # Travelling salesman problem, NP-complete
 
 Shortest cycle which visits every "vertex".
 
 Decision version of the TSP (given a length L, the task is to decide whether the graph has any tour shorter than L) belongs to the class of NP-complete problems.
 
 Reference:
  - https://en.wikipedia.org/wiki/Travelling_salesman_problem
 
 */

/**
 
 Find Eulerian cycle, O(V+E) time
 
 Hierholzer's algorithm
 
 Usage:
 
 ```
 EC ec(V);
 ec.edge(u1,v1); ec.edge(u2,v2); ...
 vector<int> p = ec.solve()
 ```
 
 */
struct EC {
public:
  // input
  int V;
  vector<vector<int>> G;
  vector<int> viz; // pointer to next edge to be visited
  EC(int V): V(V), G(V), viz(V) {}
  void edge(int u, int v) {
    assert(u<V&&v<V);
    G[u].push_back(v);
  }
  vector<int> solve(int u) {
    vector<int> res;
    dfs(u,res);
    return vector<int>(res.rbegin(),res.rend());
  }
private:
  void dfs(int u, vector<int> &res) {
    while(viz[u]<G[u].size()) {
      int v=G[u][viz[u]++];
      dfs(v,res);
    }
    res.push_back(u);
  }
};

/*
 
 Kruskal's algorithm to compute minimum spanning tree, O(E*lg V) time
 
 Greedily take edges until all the vertices are connected.
 
 References:
  - https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
  - Ant book 2-5 graph
  - CLRS Chapter 23 Minimum Spanning Trees

 Used problems:
  - https://github.com/k-ori/topcoder/blob/master/KingdomReorganization/KingdomReorganization.cpp#L94
 
 Usage:
  MST mst(10);
  mst.edge(0,1,6);
  mst.edge(1,2,3);
  ..
 
  res = mst.solve();

 */
struct MST {
public:
  int V;
  vector<tuple<int,int,int>> E;
  MST(int V): V(V) {
    uf = vector<int>(V);
    for(int i=0; i<V; ++i) uf[i]=i;
  }
  void edge(int u, int v, int w) {
    assert(u<V&&v<V);
    E.emplace_back(w,u,v);
  }
  int solve() {
    sort(E.begin(),E.end());
    
    int res=0;
    for(int i=0; i<E.size(); ++i) {
      int u,v,w;
      tie(w,u,v)=E[i];
      if(!same(u,v)) res+=w,unite(u,v);
    }
    return res;
  }
private:
  vector<int> uf;
  int find(int x) { return uf[x]==x?x:uf[x]=find(uf[x]); }
  void unite(int x, int y) {
    int px=find(x),py=find(y);
    if(px!=py) uf[px]=py;
  }
  int same(int x, int y) {
    return find(x)==find(y);
  }
};

/*
 
 Prim's algorithm to compute minimum spanning tree, O(E*lg V) time
 
 Greedily take edges until all the vertices are connected.
 Note that undirected edge needs to be added in both direction u->v and v->u in Prim's algorithm.
 
 References:
  - https://en.wikipedia.org/wiki/Prim%27s_algorithm
  - Ant book 2-5 graph
  - CLRS Chapter 23 Minimum Spanning Trees
 
 Used problems:
  - https://github.com/k-ori/topcoder/blob/master/KingdomReorganization/KingdomReorganization.cpp#L152
 
 Usage:
  Prim mst(10);
  mst.edge(0,1,6);
  mst.edge(1,2,3);
  ..
 
  res = mst.solve();
 
 */
struct Prim {
public:
  int V;
  vector<vector<pair<int,int>>> E;
  Prim(int V): V(V) {
    E = vector<vector<pair<int,int>>>(V);
    viz = vector<int>(V,0);
  }
  void edge(int u, int v, int w) {
    assert(u<V&&v<V);
    E[u].emplace_back(v,w);
  }
  int solve() {
    set<pair<int,int>> Q;
    Q.emplace(0,0);
    int res=0;
    while(Q.size()) {
      auto it=Q.begin();
      auto p=*it;
      int w=p.first,u=p.second;
      Q.erase(it);
      if(viz[u]) continue;
      viz[u]=true;
      res+=w;
      for(auto p : E[u]) if(!viz[p.first]) {
        Q.emplace(p.second,p.first);
      }
    }
    return res;
  }
private:
  vector<int> viz;
};

/*
 
 Cycle detection in linear runtime, O(V+E) time
 
 - Returns list of nodes whose descendent has NO cycle
 - Variant of SCC library. This is even simpler because we don't need to group and contract cycles.
 - This is equivalent to classic white, gray, black coloring dfs in CLRS 22.3 Depth-first search
  - white: not visited
  - gray: processing going-on
  - black: processing completed
 
 Used problems:
  - https://leetcode.com/contest/weekly-contest-76/problems/find-eventual-safe-states/
 
 */

struct GraphCycle {
public:
  // input
  int V;
  vector<vector<int>> G;
  GraphCycle(int V): V(V), G(V), done(V, -1), viz(V, 0) {}
  void edge(int u, int v) {
    assert(u<V&&v<V);
    G[u].push_back(v);
  }
  
  vector<int> findCycleFreeNodes() {
    vector<int> res;
    for(int u=0; u<V; ++u) {
      if(!viz[u]) dfs(u);
      if(!done[u]) res.push_back(u);
    }
    return res;
  }
private:
  vector<int> done; // -1: not done, 0: descendent has NO cycle, 1: descendent has cycle
  vector<int> viz;
  
  int dfs(int u) {
    if(done[u]!=-1) return done[u];
    viz[u]=true;
    
    int res=false;
    for(int v : G[u]) {
      if(!viz[v]) dfs(v);
      res|=done[v]==-1?true:done[v];
    }
    return done[u]=res;
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
  
  EC ec(7);
  ec.edge(0,1),ec.edge(0,6);
  ec.edge(1,2);
  ec.edge(2,0),ec.edge(2,3);
  ec.edge(3,4);
  ec.edge(4,2),ec.edge(4,5);
  ec.edge(5,0);
  ec.edge(6,4);
  vector<int> cycle=ec.solve(0);
  vector<int> cycleExpected={0,1,2,0,6,4,2,3,4,5,0};
  assertVec(cycle, cycleExpected);
  
  // Minimum spanning tree
  // CLRS 23.1 Growing a minimum spanning tree, Figure 23.1
  vector<pair<int,int>/*(v,w)*/> G[9];
  G[0]={{1,4},{7,8}};
  G[1]={{0,4},{2,8},{7,11}};
  G[2]={{1,8},{3,7},{5,4},{8,2}};
  G[3]={{2,7},{4,9},{5,14}};
  G[4]={{3,9},{5,10}};
  G[5]={{2,4},{3,14},{4,10}};
  G[6]={{5,2},{7,1},{8,6}};
  G[7]={{0,8},{1,11},{6,1},{8,7}};
  G[8]={{2,2},{6,6},{7,7}};
  
  MST mst1(9);
  Prim mst2(9);
  for(int u=0; u<9; ++u) for(auto p : G[u]) {
    mst1.edge(u,p.first,p.second);
    mst2.edge(u,p.first,p.second),mst2.edge(p.first,u,p.second);
  }
  assert(mst1.solve()==37);
  assert(mst2.solve()==37);
  
  // Cycle detection
  vector<vector<int>> G_cycle={{1,2},{2,3},{5},{0},{5},{},{}};
  GraphCycle gc(G_cycle.size());
  for(int u=0; u<G_cycle.size(); ++u) for(int v : G_cycle[u]) gc.edge(u,v);
  vector<int> cycleFreeNodes={2,4,5,6};
  assertVec(gc.findCycleFreeNodes(), cycleFreeNodes);
}
