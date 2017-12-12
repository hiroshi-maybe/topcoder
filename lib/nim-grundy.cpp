#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <unordered_set>

using namespace std;

/*
 
 Grundy number calculator, O(K*N) time (for single heap Nim game)
 
 grundy number:
  - Ant book 4-2 game theory
  - https://www.hackerrank.com/topics/game-theory-and-grundy-numbers
  - https://github.com/k-ori/topcoder/blob/master/GameOfSegments/GameOfSegments.cpp
 
 Usage:
 
   string solve() {
     calcGrundy(N);
     return G[N]!=0?"Alice":"Bob"
   }
 
 */

#define MAX_N 1005
int G[MAX_N]; // Grundy number
// Grundy number for x smaller than `a` must be calculated.
int grundy(int a, int K) {
  unordered_set<int> S;

  // Iterate all the possible state transitions from `a`.
  // This is sample implementation of Nim game. Customize if needed.
  for(int i=1; i<=K; ++i) if(a>=i) {
    S.emplace(G[a-i]); // if devided into multiple independent problems, G[x]^G[y]^..
  }
  
  int mex=0;
  while(S.count(mex)) ++mex;
  return mex;
}
// Compute grundy number by DP
void calcGrundy(int N) {
  assert(N<MAX_N);
  G[0]=0;
  for(int n=1; n<=N; ++n) G[n]=grundy(n,N);
}

/*
 
 Nim game solver with N heaps of coins and maximum K coins removal, O(N*A+N^2) time
 
 https://en.wikipedia.org/wiki/Nim
 
 */
string solveNim(vector<int> ns) {
  int A=*max_element(ns.begin(),ns.end());
  calcGrundy(A);
  int N=ns.size();
  int res=0;
  for(int i=0; i<N; ++i) res^= G[ns[i]];
  return res!=0?"Alice":"Bob"; // Grundy number == 0 => "LOST"
}

int main(int argc, char const *argv[]) {
  // from http://www.archimedes-lab.org/How_to_Solve/Win_at_Nim.html
  vector<int> ns={1,3,5,7};
  string winner=solveNim(ns);
  assert(winner=="Bob");
}
