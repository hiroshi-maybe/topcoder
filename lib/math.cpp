#include <iostream>
#include <cassert>
#include <tuple>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;
constexpr int MOD = 1e9+7;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
int lcm(int a, int b) {
    return (a*b) / gcd(a,b);
}

// CLRS 31.2
// returns (gcd,x,y) s.t. gcd = a*x + b*y
tuple<int,int,int> gcd_extended(int a, int b) {
  if (b==0) return make_tuple(a, 1, 0);
  
  int d2,x2,y2;
  tie(d2,x2,y2) = gcd_extended(b, a%b);
  return make_tuple(d2,y2,x2-(a/b)*y2);
}

// CLRS 31.6 and https://kimiyuki.net/blog/2017/03/27/srm-711-med/
// compute (a^b) `mod` mod, mod=1e9+7 by default
// O(lg b)
LL powmod(LL a, LL b, LL mod=MOD) {
  assert(0<=a && a<mod);
  assert(0<=b);

  LL res=1;
  for(LL mask=1; mask<=b; mask<<=1) {
    if(b&mask) res*=a, res%=mod;
    a*=a; a%=mod;
  }
  return res;
}

// https://en.wikipedia.org/wiki/Modular_multiplicative_inverse#Computation
// Modular multiplicative inverse by Euler's theorem
// a^-1 (`mod` mod) = a^(mod-2), a should be coprime to mod, mod=1e9+7 by default
// O(lg m)
LL modinv(LL a, LL mod=MOD) {
  return powmod(a, mod-2);
}

// memoized factorial(n) (mod m)
// O(n) before cache warmup
LL factmod(LL n, LL mod=MOD) {
  static vector<LL> memo(1,1);
  if(memo.size()<=n) {
    LL l=memo.size();
    memo.resize(n+1);
    for(LL i=l; i<=n; ++i) memo[i]=memo[i-1]*i, memo[i]%=mod;
  }
  return memo[n];
}

// main

int main(int argc, char const *argv[]) {
  assert(gcd(899,493)==29);

  auto t = gcd_extended(899,493);
  assert(get<0>(t)==29);
  assert(get<1>(t)==-6);
  assert(get<2>(t)==11);

  int m1 = powmod(7,560,561);
  assert(m1==1);
  
  int m2 = powmod(7,560);
  assert(m2==108725231);
  
  LL m = 560;
  LL mi = modinv(m,MOD);
  assert((m*mi)%MOD==1);
  
  assert(factmod(560)==597965522);
}
