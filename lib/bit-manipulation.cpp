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

// Returns all the submasks of given mask
// https://e-maxx-eng.appspot.com/algebra/all-submasks.html
// https://www.topcoder.com/community/data-science/data-science-tutorials/a-bit-of-fun-fun-with-bits/
//
// // O(3^N) time for all the super sets
// REP(mask,1<<N) for(int s=mask; s>0; s=(s-1)&mask) { ... }
//
// Proof of O(3^N) runtime:
//
// If k bits set, there are 2^k subset for C(n,k) combination of bits.
// Thus total computation is...
// ∑ { C(n,k)*2^k : k=0..n }
//  = ∑ { C(n,k)*1^(n-k)*2^k : k=0..n }
//  = (1+2)^n = 3^n (binomial theorem)
//
// Binomial theorem:
//  ∑ { C(n,k)*x^k*y^(n-k) : k=0..n } = (x+y)^n
//
//
vector<int> submasks(int mask) {
  vector<int> S;
  for(int s=mask; s>0; s=(s-1)&mask) {
    S.push_back(s);
  }
  return S;
}

// test if number is power of 2
bool isPowerOfTwo(int n) {
  return (n&(n-1))==0;
}

// unset least significant (right-most) bit
int unsetLSB(long long n) {
  assert(n>0);
  return n&(n-1);
}

// get number with least significant (right-most) bit
int getLSB(long long n) {
  assert(n>0);
  return n&-n;
  // or 1LL<<__builtin_ctzll(n)
}

// get position of LSB
int getLSBPos(long long n) {
  return __builtin_ctzll(n);
}

string n2bin(long long n) {
  assert(n>=0);
  string res="";
  while(n>0) res+=(n%2LL?'1':'0'),n/=2LL;
  return string(res.rbegin(), res.rend());
}

long long bin2n(string s) {
  long long res=0;
  for(int i=0; i<s.size(); ++i) {
    res=2LL*res+(s[i]=='1');
  }
  return res;
}

/*
 
 GCC built-in libraries:
 
  __builtin_popcount(mask) // count number of ON bit
  __builtin_ctz(mask)      // count number of trailing zeros
  __builtin_clz(mask)      // count number of leading zeros

 __builtin_popcountll(mask)
 __builtin_ctzll(mask)
 __builtin_clzll(mask)
 
 */

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

  vector<int> exp3 = {26, 24, 18, 16, 10, 8, 2};
  vector<int> S = submasks(26);
  assert(S.size()==exp3.size());
  for(int i=0; i<S.size(); ++i) assert(exp3[i]==S[i]);
  
  assert(isPowerOfTwo(32));
  assert(!isPowerOfTwo(31));
  
  assert(unsetLSB(26)==24);
  assert(getLSB(26)==2);
  assert(1LL<<__builtin_ctzll(26)==2);
  
  assert(n2bin(2384185791015625LL)=="1000011110000110011110000011001001101110101011001001");
  assert(bin2n("1000011110000110011110000011001001101110101011001001")==2384185791015625LL);
}
