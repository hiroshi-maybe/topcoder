//
//  graph.cpp
//
//
//  Created by Hiroshi Kori on 5/21/17.
//
//

#include <iostream>
#include <vector>
#include <unordered_map>
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
  Q.emplace(INT_MAX, 0);
  
  while(Q.size()) {
    auto it = *(Q.begin()); Q.erase(it);
    int u = it.second;
    visited[u] = true;
    
    for(auto &kvp : E[u]) {
      int v = kvp.first, w = kvp.second;
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

vector<vector<long>> floydWarshall(vector<vector<long>> W) {
  if (W.empty()) return W;
  int V=W.size();
  
  for(int k=0; k<V; ++k) {
    for(int i=0; i<V; ++i) {
      for(int j=0; j<V; ++j) {
        W[i][j] = min(W[i][j], W[i][k]+W[k][j]);
        W[i][j] = min(W[i][j], (long)INT_MAX);
      }
    }
  }
  
  return W;
}

// helper

void print(vector<vector<long>> Mx) {
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

// main

int main(int argc, char const *argv[]) {
  int Inf = INT_MAX;
  vector<vector<long>> W = {
    {   0, Inf, Inf, Inf,  -1, Inf },
    {   1,   0, Inf,   2, Inf, Inf },
    { Inf,   2,   0, Inf, Inf,  -8 },
    {  -4, Inf, Inf,   0,   3, Inf },
    { Inf,   7, Inf, Inf,   0, Inf },
    { Inf,   5,  10, Inf, Inf,   0 }
  };
  
  W = floydWarshall(W);
  // print(W);
  
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
}
