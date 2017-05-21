//
//  graph.cpp
//
//
//  Created by Hiroshi Kori on 5/21/17.
//
//

#include <iostream>
#include <vector>

using namespace std;

vector<vector<long>> floydWarshall(vector<vector<long>> W) {
  if (W.empty()) return W;
  int N=W.size();
  
  for(int k=0; k<N; ++k) {
    for(int i=0; i<N; ++i) {
      for(int j=0; j<N; ++j) {
        W[i][j] = min(W[i][j], W[i][k]+W[k][j]);
        W[i][j] = min(W[i][j], (long)INT_MAX);
      }
    }
  }
  
  return W;
}

/*
void print(vector<vector<long>> Mx) {
  int M=Mx.size(), N=Mx[0].size();
  for(int i=0; i<M; ++i) {
    for(int j=0; j<N; ++j) {
      cout << Mx[i][j] << ",";
    }
    cout << endl;
  }
}

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
  print(W);
}
*/
