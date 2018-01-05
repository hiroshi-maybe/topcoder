#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <unordered_set>

using namespace std;

/*
 
 Sample implementation of Grundy number, O(K*N) time
 
 Grundy number is applicable for finite 2-person impartial games with perfect information.
 Grundy number is a technique to reduce a problem to Nim game.
 One problem corresponds to one pile of stones in Nim.
 
 If problem is separated to combination of multiple subproblems...
   G(original problem) = G(subproblem 0)^G(subproblem 1)^..
 
 ⚠️ This is sample implementation for Nim game. Customize state transition.
 Note that grundy number of Nim with `n` remaining stone is n (G[n]=n),
 because grundy number reduces games to Nim with `n` remaining stones.
 
 Reference (grundy number):
  - Ant book 4-2 game theory
  - https://www.hackerrank.com/topics/game-theory-and-grundy-numbers
  - https://www.topcoder.com/community/data-science/data-science-tutorials/algorithm-games/
  - https://github.com/k-ori/topcoder/blob/master/GameOfSegments/GameOfSegments.cpp
  - https://github.com/k-ori/topcoder/blob/master/CatAndRabbit/CatAndRabbit.cpp
   - Nim game
 
 Usage:
 
   string solve() {
     calcGrundy(N);
     return G[N]==0?"Bob":"Alice"
   }
 
 */

#define MAX_N 1005
int G[MAX_N]; // Grundy number
// Grundy number for x smaller than `a` must be calculated.
int grundy(int a, int K) {
  unordered_set<int> S;

  // Iterate all the possible state transitions from `a`.
  // ⚠️ This is sample implementation of Nim game. Customize here to apply other game
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
  return res==0?"Bob":"Alice"; // Grundy number == 0 => "LOST"
}

int main(int argc, char const *argv[]) {
  // from http://www.archimedes-lab.org/How_to_Solve/Win_at_Nim.html
  vector<int> ns={1,3,5,7};
  string winner=solveNim(ns);
  assert(winner=="Bob");
}
