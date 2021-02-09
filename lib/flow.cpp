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
  - build residual graph with (cap, cost) and increase f following shortest path of cost
   - initial (cap, cost) of reverse edge is (0, -cost)
   - edge is valid path only when cap>0
  - special case of other problems
   - if there is no capacity constraint, it's reduced to the shortest path problem
   - if cost is zero, it's reduced to the max flow problem
  - minimum cost bipartite matching is a special case of minimum-flow problem
   - Ant book 3-5 network flow

  Algorithms:
  - Dijkstra's algorithm in O(F*E*lg V) time
  - linear programming as shown in CLRS 29.2 Formulating problems as linear programs

 3. Vertex/edge cover, independent set

    Independent (stable) set = V - Vertex cover
 => Maximum independent (stable) set = V - Minimum vertex cover

 Problem to compute maximum independent (stable) set is painting vertices with two colors (no adjacent vertices don't have the same color).
 Vertices in a color class with dominant set is the maximum independent (stable) set.
 See https://en.wikipedia.org/wiki/Graph_coloring#Vertex_coloring

 Vertex cover: selected vertices cover all the edges

 Minimum edge cover = Max matching + (V - 2*Max matching) = Max matching + V
 Intuitively it's matching + 𝛂 (extra vertices to be added)

 Matching is a problem to make as many pairs as possible in a graph.
 By adding additional edges to maximum matching to cover all the vertices which was out of matchings, we get minimum edge cover.

 References:
  - Minimum cost flow
    - https://en.wikipedia.org/wiki/Minimum-cost_flow_problem
  - Minimum cost bipartite matching
    - http://theory.stanford.edu/~tim/w16/l/l5.pdf
  - https://qiita.com/drken/items/7f98315b56c95a6181a4

 */

/*

 Dinic's max flow algorithm, O(E*V^2)

 Used problems:
  - https://github.com/hiroshi-maybe/fbhackercup/blob/master/2019-R1/LaddersAndSnakes.cpp#L45
   - min cut

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
template<class V> class Dinic {
public:
  int N;
  Dinic(int N) : N(N) {
    E=vector<vector<Edge>>(N),dist=vector<int>(N),iter=vector<int>(N);
  }
  void addEdge(int from, int to, V cap) {
    E[from].push_back((Edge){  to, (int)E[  to].size()  , cap});
    E[  to].push_back((Edge){from, (int)E[from].size()-1,   0}); // cancellation edge in residual graph
  }

  V maxFlow(int s, int t) {
    V res=0;
    while(true) {
      bfs(s);
      if(dist[t]<0) return res; // t is unreachable
      iter=vector<int>(N,0);
      V f;
      while((f=dfs(s,t,Inf))>0) res+=f;
    }

    return res;
  }
private:
  const V Inf=numeric_limits<V>::max();
  struct Edge { int to, rev; V cap; };
  vector<vector<Edge>> E; // Graph
  vector<int> dist; // distance from `s`
  vector<int> iter;

  // initialize shoftest path and store in `level`
  void bfs(int s) {
    dist=vector<int>(N,-1);

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
const int MAX_V=100;
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

 If you want to paint as many vertices as possible with the same color in bipartite graph, use this!

     maximum matching + maximum independent set = V
 <=> maximum independent set = V - maximum matching

 Intuitively maximum matching + 𝛂 (extra vertices to be added) = maximum independent set

 Properties of bipartite graph
  - 2-coloring is possible
  - Length of cycle is odd

 References:
  - Ant book 3-5 Network flow
  - CLRS 26.3 Maximum bipartite matching
  - https://en.wikipedia.org/wiki/Matching_(graph_theory)#In_unweighted_bipartite_graphs
  - http://topcoder.g.hatena.ne.jp/agw/20120716/1342405575
  - vertex cover: https://ja.wikipedia.org/wiki/%E9%A0%82%E7%82%B9%E8%A2%AB%E8%A6%86
  - independent set: https://ja.wikipedia.org/wiki/%E7%8B%AC%E7%AB%8B%E9%9B%86%E5%90%88
  - https://qiita.com/drken/items/7f98315b56c95a6181a4

 Used problem:
  - https://github.com/k-ori/topcoder/blob/master/PointyWizardHats/PointyWizardHats.cpp
  - https://github.com/k-ori/GCJ/blob/master/2018-R2/CostumeChange.cpp#L126
  - https://github.com/k-ori/atcoder/blob/master/solutions/Koukoku.cpp#L157

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
  MaxBipartiteMatching(int V) : V(V) {
    E=vector<vector<int>>(V), match=vector<int>(V,-1), viz=vector<int>(V);
  }

  void addEdge(int u, int v) {
    assert(u<V&&v<V);
    E[u].push_back(v),E[v].push_back(u);
  }

  int solve() {
    int res=0;
    for(int u=0; u<V; ++u) if(match[u]<0) {
      viz=vector<int>(V);
      res+=dfs(u);
    }
    return res;
  }
private:
  int V;
  vector<vector<int>> E;
  vector<int> match,viz;

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

/*

 Solver of minimum-cost flow problem, O(F*E*lg V) time

  - build residual graph with (cap, cost) and increase f following shortest path of cost
  - Ant book 3-5 network flow

 Usage:

  MinCostFlow f(V);
  f.addEdge(u0,v0,cap0,cost0);
  f.addEdge(u1,v1,cap1,cost1);

  int mcost=f.solve(s,t,F);

 */
// const int MAX_V=100;
struct MinCostFlow {
public:
  MinCostFlow(int V) : V(V) {}

  void addEdge(int from, int to, int cap, int cost) {
    E[from].push_back((Edge){  to, static_cast<int>(E[to].size()),     cap,  cost});
    E[  to].push_back((Edge){from, static_cast<int>(E[from].size()-1),   0, -cost}); // rev edge with (cap,cost)=(0,-cost)
  }

  int solve(int s, int t, int f) {
    int res=0;
    fill(h,h+V,0);
    while(f>0) {
      priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
      fill(dist,dist+V,Inf);
      dist[s]=0;
      Q.push({0,s});
      while(Q.size()) {
        auto p=Q.top(); Q.pop();
        int u=p.second;
        if(dist[u]<p.first) continue;
        for(int i=0; i<E[u].size(); ++i) {
          auto &e=E[u][i];
          int v=e.to;
          if(e.cap<=0) continue;
          int dd=dist[u]+e.cost+h[u]-h[v];
          if(dist[v]<=dd) continue;
          dist[v]=dd;
          prev_v[v]=u; prev_e[v]=i;
          Q.push({dist[v],v});
        }
      }

      // capacity is exhausted. no longer incrase flow
      if(dist[t]==Inf) return -1;

      for(int u=0; u<V; ++u) h[u]+=dist[u];

      // increase flow as much as possible on the shortest path
      int d=f;
      for(int v=t; v!=s; v=prev_v[v]) {
        // backtrack shortest path
        d=min(d,E[prev_v[v]][prev_e[v]].cap);
      }
      f-=d;
      res+=d*h[t];
      for(int v=t; v!=s; v=prev_v[v]) {
        auto &e=E[prev_v[v]][prev_e[v]];
        e.cap-=d;
        E[v][e.rev].cap+=d;
      }
    }
    return res;
  }
private:
  const int Inf = numeric_limits<int>::max();
  int V;
  struct Edge { int to, rev, cap, cost; };
  vector<Edge> E[MAX_V]; // Graph
  int h[MAX_V]; // potential
  int dist[MAX_V];
  int prev_v[MAX_V], prev_e[MAX_V];
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

  Dinic<int> d(C.size());
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
  Dinic<int> f2(100);
  for(int u=0; u<5; ++u) f2.addEdge(source,u,1);
  for(int v=5; v<9; ++v) f2.addEdge(v,sink,1);
  for(auto e : es) f2.addEdge(e.first,e.second,1);
  assert(f2.maxFlow(source,sink)==mm); // 3

  // Ant book 3-5 network flow
  vector<vector<tuple<int,int,int>>> G = {
    // u->{v,cap,cost}
    { {1,10,2}, {2,2,4} },
    { {2, 6,6}, {3,6,2} },
    { {4, 5,2} },
    { {2,3,3}, {4,8,6} },
    { },
  };

  MinCostFlow f(G.size());
  for(int u=0; u<G.size(); ++u) for(auto t : G[u]) {
    int v,cap,cost;
    tie(v,cap,cost)=t;
    f.addEdge(u,v,cap,cost);
  }
  assert(f.solve(0,4,9)==80);
}

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address flow.cpp && ./a.out