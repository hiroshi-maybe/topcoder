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

// CLRS 31.6 powers of an element
// compute (a^b) `mod` 1e9+7
// O(lg b)
// famous for name of "repeated squaring"
LL powmod(LL a, LL b) {
  assert(0<=a && a<MOD);
  assert(0<=b);

  LL res=1;
  for(LL mask=1; mask<=b; mask<<=1) {
    if(b&mask) res*=a, res%=MOD;
    a*=a; a%=MOD;
  }
  return res;
}

// https://en.wikipedia.org/wiki/Modular_multiplicative_inverse#Computation
// Modular multiplicative inverse by Euler's theorem
// a^-1 (`mod` mod) = a^(mod-2), a should be coprime to mod, mod=1e9+7
// O(lg m)
LL modinv(LL a) {
  return powmod(a, MOD-2);
}

// memoized factorial(n) (`mod` 1e9+7)
// O(n) before cache warmup
LL factmod(LL n) {
  static vector<LL> memo(1,1);
  if(memo.size()<=n) {
    LL l=memo.size();
    memo.resize(n+1);
    for(LL i=l; i<=n; ++i) memo[i]=memo[i-1]*i, memo[i]%=MOD;
  }
  return memo[n];
}

// n chooses k
// C(n,k) = n!/((n-k)!*k!)
LL choose(LL n, LL k) {
  if (n<k) return 0;
  k = min(n-k,k);
  LL res=factmod(n);
  res *= modinv(factmod(n-k)), res%=MOD;
  res *= modinv(factmod(  k)), res%=MOD;
  
  return res;
}

#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

// Populate n chooses k (n={1..N},k={1..N}) (accumulate by DP)
// C(n,k) = C(n-1,k)+C(n-1,k-1)
// O(N^2) time
void choose(LL N, vector<vector<int>> &dp) {
  // i chooses j
  for(int i=0; i<=N; ++i) {
    dp[i][0]=1;
    for(int j=1; j<=i; ++j) {
      dp[i][j] = dp[i-1][j]+dp[i-1][j-1], dp[i][j]%=MOD;
    }
  }
}

// multichoose
// H(n,k) = C(n+k-1,k)
LL multichoose(LL n, LL k) {
  if(n==0&&k==0) return 1;

  return choose(n+k-1,k);
}

// main

int main(int argc, char const *argv[]) {
  assert(gcd(899,493)==29);

  auto t = gcd_extended(899,493);
  assert(get<0>(t)==29);
  assert(get<1>(t)==-6);
  assert(get<2>(t)==11);

  int m2 = powmod(7,560);
  assert(m2==108725231);
  
  LL m = 560;
  LL mi = modinv(m);
  assert((m*mi)%MOD==1);
  
  assert(factmod(560)==597965522);
  assert(choose(771,50)==275127687);
  assert(multichoose(771,50)==954694855);
  
  vector<vector<int>> dp(201,vector<int>(201,0));
  choose(200,dp);
  assert(dp[200][23]==choose(200,23));
}
