#include <vector>
#include <queue>
#include <cassert>
#include <iostream>

using namespace std;

#define MAX_V 100
#define Inf 1<<28

struct Edge { int to, cap, rev; };

vector<Edge> G[MAX_V]; // Graph
int level[MAX_V]; // distance from `s`
int iter[MAX_V]; // 

void addEdge(int from, int to, int cap) {
  G[from].push_back((Edge){to, cap, (int)G[to].size()});
  G[to].push_back((Edge){from, 0, (int)G[from].size()-1});
}

// initialize shoftest path and store in `level`
void bfs(int s) {
  memset(level, -1, sizeof(level));

  queue<int> Q;
  level[s] = 0;
  Q.push(s);

  while (!Q.empty()) {
    int u = Q.front(); Q.pop();

     for (int i = 0; i < G[u].size(); i++) {
       Edge &e = G[u][i];
       int v = e.to;
       if (e.cap<=0) continue;
       if (level[v]>=0) continue; // visited

       level[v] = level[u] + 1;
       Q.push(v);
     }
  }
}

// find augmenting path in residual network and update f
int dfs(int u, int t, int f) {
  if (u == t) return f;
  for (int &i = iter[u]; i < G[u].size(); i++) {
    Edge &e = G[u][i];
    int v = e.to;
    if (e.cap <= 0) continue;
    if (level[u] >= level[v]) continue;    

    int d = dfs(v, t, min(f, e.cap));
    if (d <= 0) continue;
    e.cap -= d;
    G[v][e.rev].cap += d;
    return d;
  }

  return 0;
}

// Max flow algorithm Dinic, O(E*V^2)
// precondition: G should be initialized
int maxFlow(int s, int t) {
  int flow = 0;
  while (true) {
    bfs(s);
    if (level[t] < 0) return flow; // t is unreachable

    memset(iter, 0, sizeof(iter));
    int f;
    while ((f = dfs(s, t, Inf)) > 0) {
      flow += f;
    }
  }

  return flow;
}

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
  for(int u=0; u<C.size(); ++u) {
    for(int v=0; v<C.size(); ++v) {
      if (C[u][v]==0) continue;
      addEdge(u,v,C[u][v]);      
    }
  }
  int maxf = maxFlow(0,C.size()-1);
  assert(maxf == 23);
}
