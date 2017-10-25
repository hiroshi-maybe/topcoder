#include <vector>
#include <queue>
#include <cassert>
#include <iostream>

using namespace std;

/*
 
 Flow prolems
 
 1. Max-flow problem
 
  - Maximize flow from source to sink in given capacity constraint.
  - Max-flow equals to min-cut
  - bipartite matching is a special case of max-flow problem
 
  Algorithms:
   - Naiive Ford-Fulkerson method in O(F*E) time
    - iteratively increases the value of the flow by finding a path by dfs
   - Dinic's algorithm in O(E*V^2) time
    - optimized Ford-Fulkerson method by pre-computing shortest path from source

  References:
   - https://en.wikipedia.org/wiki/Maximum_flow_problem
   - Max-flow min-cut theorem: https://en.wikipedia.org/wiki/Max-flow_min-cut_theorem
   - CLRS 26.2 The Ford-Fulkerson method
   - CLRS 26.3 Maximum bipartite matching
 
 2. Minimum-cost flow problem
 
  - flow `d` is given while computation of flow is goal in max-flow problem
  - compute min-cost which achieves flow `d`
  - special case of other problems
   - if there is no capacity constraint, it's reduced to the shortest path problem
   - if cost is zero, it's reduced to the max flow problem
 
  Algorithms:
  - Dijkstra's algorithm in O(F*E*lg V) time
  - linear programming as shown in CLRS 29.2 Formulating problems as linear programs
 
 References:
  - https://en.wikipedia.org/wiki/Minimum-cost_flow_problem
 
 */

/*
 
 Dinic's max flow algorithm, O(E*V^2)
 
 Usage:
  // Don't miss to update MAX_V constant
  
  // initialize
  Dinic<int> f;
 
  // configure edges with capacity
  f.addEdge(u0,v0,c0);
  f.addEdge(u1,v1,c1);
 
  // compute flow
  flow = f.maxFlow(source, sink)
 
 */
const int MAX_V=100;
template<class V> class Dinic {
public:
  void addEdge(int from, int to, V cap) {
    E[from].push_back((Edge){  to, (int)E[  to].size()  , cap});
    E[  to].push_back((Edge){from, (int)E[from].size()-1,   0}); // cancellation edge in residual graph
  }
  
  V maxFlow(int s, int t) {
    V res=0;
    while(true) {
      bfs(s);
      if(dist[t]<0) return res; // t is unreachable
      memset(iter,0,sizeof(iter));
      V f;
      while((f=dfs(s,t,Inf))>0) res+=f;
    }
    
    return res;
  }
private:
  const V Inf=numeric_limits<V>::max();
  struct Edge { int to, rev; V cap; };
  vector<Edge> E[MAX_V]; // Graph
  int dist[MAX_V]; // distance from `s`
  int iter[MAX_V];
  
  // initialize shoftest path and store in `level`
  void bfs(int s) {
    memset(dist,-1,sizeof(dist));
    
    queue<int> Q;
    dist[s]=0;
    Q.push(s);
    
    while(Q.size()) {
      int u=Q.front(); Q.pop();
      
      for(int i=0; i<E[u].size(); ++i) {
        Edge &e=E[u][i];
        int v=e.to;
        if(e.cap<=0) continue;
        if(dist[v]>=0) continue; // visited
        
        dist[v]=dist[u]+1;
        Q.push(v);
      }
    }
  }
  
  // find augmenting path in residual network and update f
  V dfs(int u, int t, V f) {
    if(u==t) return f;
    for(int &i=iter[u]; i<E[u].size(); ++i) { // visit E[u] only once
      Edge &e=E[u][i];
      int v=e.to;
      if(e.cap<=0) continue;
      if(dist[u]>=dist[v]) continue;
      
      V d=dfs(v,t,min(f,e.cap));
      if(d<=0) continue;
      e.cap-=d;
      E[v][e.rev].cap+=d; // cancellation increases
      return d;
    }
    
    return 0;
  }
};

/*
 
 Naiive Ford-Fulkerson method to compute max flow, O(F*E) time
 
 Usage:
  // Don't miss to update MAX_V constant
 
  // initialize
  FordFulkerson<int> ff;
 
  // configure edges with capacity
  ff.addEdge(u0,v0,c0);
  ff.addEdge(u1,v1,c1);
 
  // compute flow
  flow = ff.maxFlow(source, sink)
 
 */
template<class V> class FordFulkerson {
public:
  void addEdge(int from, int to, V cap) {
    E[from].push_back((Edge){  to, (int)E[  to].size()  , cap});
    E[  to].push_back((Edge){from, (int)E[from].size()-1,   0}); // cancellation edge in residual graph
  }
  
  V maxFlow(int s, int t) {
    V res=0;
    while(true) {
      memset(viz,0,sizeof(viz));
      V f=dfs(s,t,Inf);
      if(f==0) return res;
      res+=f;
    }
    return res;
  }
private:
  const V Inf=numeric_limits<V>::max();
  struct Edge { int to, rev; V cap; };
  vector<Edge> E[MAX_V]; // Graph
  bool viz[MAX_V];
  
  // find augmenting path in residual network and update f
  V dfs(int v, int t, V f) {
    if(v==t) return f;
    viz[v]=true;
    for(int i=0; i<E[v].size(); ++i) if(!viz[E[v][i].to]&&E[v][i].cap>0) {
      Edge &e=E[v][i];
      V d=dfs(e.to,t,min(f,e.cap));
      if(d==0) continue;
      
      e.cap-=d;
      E[e.to][e.rev].cap+=d;
      return d;
    }
    return 0;
  }
};

/*
 
 Solver of bipartite matching problem by Ford-Fulkerson method, O(V*E) time
 
  - compute max flow of bipartite graph with capacity 1
  - no need to add edges with source or sink
  - in bipartite graph, maximum matching = vertex cover number (Ant book 3-5 network flow)
   - generally size of maximum independent set + vertex cover number = V
   - thus in bipartite graph size of maximum independent set = V - maximum matching
 
 References:
  - Ant book 3-5 Network flow
  - CLRS 26.3 Maximum bipartite matching
  - https://en.wikipedia.org/wiki/Matching_(graph_theory)#In_unweighted_bipartite_graphs
  - http://topcoder.g.hatena.ne.jp/agw/20120716/1342405575
  - vertex cover: https://ja.wikipedia.org/wiki/%E9%A0%82%E7%82%B9%E8%A2%AB%E8%A6%86
  - independent set: https://ja.wikipedia.org/wiki/%E7%8B%AC%E7%AB%8B%E9%9B%86%E5%90%88
 
 Usage:

  int V=9;
  MaxBipartiteMatching BM(V); // number of vertices |L ∪ R|
 
  // add possible pairs ∀v, v<V.
  BM.addEdge(0,5); // vertex ID of left and right should be disjoint
  BM.addEdge(1,7);
 
  // compute maximum matching
  int matching = BM.solve()
 
 */
class MaxBipartiteMatching {
public:
  MaxBipartiteMatching(int V) : V(V) {}
  
  void addEdge(int u, int v) {
    assert(u<V&&v<V);
    E[u].push_back(v);
    E[v].push_back(u);
  }
  
  int solve() {
    int res=0;
    memset(match, -1, sizeof(match));
    for(int u=0; u<V; ++u) if(match[u]<0) {
      memset(viz,0,sizeof viz);
      res+=dfs(u);
    }
    
    return res;
  }
private:
  int V;
  vector<int> E[MAX_V];
  int match[MAX_V];
  bool viz[MAX_V];
  
  // find augmenting path in residual network
  bool dfs(int u) {
    viz[u]=true;
    for(auto v : E[u]) {
      int w=match[v];
      if(w<0||(!viz[w]&&dfs(w))) {
        match[v]=u;
        match[u]=v;
        return true;
      }
    }
    return false;
  }
};

int main(int argc, char const *argv[]) {  
  // CLRS Figure 26.6
  vector<vector<int>> C = {
    {   0,  12,  13,   0,   0,   0 },
    {   0,   0,   0,  12,   0,   0 },
    {   0,   4,   0,   0,  14,   0 },
    {   0,   0,   9,   0,   0,  20 },
    {   0,   0,   0,   7,   0,   4 },
    {   0,   0,   0,   0,   0,   0 }
  };
  
  Dinic<int> d;
  FordFulkerson<int> ff;
  for(int u=0; u<C.size(); ++u) {
    for(int v=0; v<C.size(); ++v) {
      if (C[u][v]==0) continue;
      d.addEdge(u,v,C[u][v]);
      ff.addEdge(u,v,C[u][v]);
    }
  }
  int maxf = d.maxFlow(0,C.size()-1);
  assert(maxf == 23);
  int maxff = ff.maxFlow(0,C.size()-1);
  assert(maxff == 23);

  // 0-4: L, 5-8: R
  vector<pair<int,int>> es = {
    {0,5},
    {1,5},{1,7},
    {2,6},{2,7},{2,8},
    {3,7},
    {4,7}
  };
  
  MaxBipartiteMatching BM(9);
  for(auto e : es) BM.addEdge(e.first,e.second);
  int mm = BM.solve();
  
  int source=9,sink=10;
  Dinic<int> f2;
  for(int u=0; u<5; ++u) f2.addEdge(source,u,1);
  for(int v=5; v<9; ++v) f2.addEdge(v,sink,1);
  for(auto e : es) f2.addEdge(e.first,e.second,1);
  assert(f2.maxFlow(source,sink)==mm); // 3
}
