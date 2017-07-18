#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int f[1<<20];

// Suppose there is a set S (|S|=N) and subsets T[0],..,T[2^N-1] and we already know f(T[0]),..,f(T[2^n-1]).
// Then z-transform(N) computes g(T[i]) = ∑{f(U),T[i]⊆U}.
// Note that actually computation does not need to be summation ∑ if it's ring (max, *, gcd works too)
//
// Input: f[i] has f(T[i]) where T[i] is subset mask of S
// Output: f[i] = g(T[i]) by summation
// O(N*2^N) time
void ztransform_superset(int N) {
  for(int i=0; i<N; ++i) {
    for(int T=0; T<(1<<N); ++T) {
      if ((T&(1<<i))==0) f[T]+=f[T|(1<<i)];
    }
  }
}
void ztransform_subset(int N) {
  for(int i=0; i<N; ++i) {
    for(int T=0; T<(1<<N); ++T) {
      if ((T>>i)&1) f[T]+=f[T^(1<<i)];
    }
  }
}

/***********************   test code below   ***********************/

int main(int argc, char const *argv[]) {
  int N=3;
  for(int i=0; i<(1<<N); ++i) f[i]=i;
  ztransform_superset(N);
  vector<int> exp1 = {28,16,18,10,22,12,13,7};
  for(int i=0; i<(1<<N); ++i) assert(f[i]==exp1[i]);
  
  for(int i=0; i<(1<<N); ++i) f[i]=i;
  ztransform_subset(N);
  vector<int> exp2 = {0,1,2,6,4,10,12,28};
  for(int i=0; i<(1<<N); ++i) assert(f[i]==exp2[i]);

}
