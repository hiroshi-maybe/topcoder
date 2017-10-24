#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;
constexpr int MOD = 1e9+7;

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

/*
 
 Compute modular multiplicative inverse, O(lg a)
 
 - compute a^-1 (mod p) p is prime AND p ⧷ a
 - proved by Fermat's little theorem
 
 Fermat's little theorem:
 
 a^p     ≡ a (mod p)       if p is prime
 a^(p-1) ≡ 1 (mod p)       if p is prime AND p ⧷ a
 a^-1    ≡ a^(p-2) (mod p) if p is prime AND p ⧷ a

 References:
  - https://en.wikipedia.org/wiki/Modular_multiplicative_inverse#Computation
  - https://en.wikipedia.org/wiki/Fermat%27s_little_theorem
 
 */
LL modinv(LL a, LL p=MOD) {
  return powmod(a, p-2);
}

/*
 
 Compute Euler's totient function φ(n) (phi function), O(√n)
 
 - φ(n) counts the positive integers up to a given integer n that are relatively prime to n
 - X^(φ(n)) ≡ 1 (mod n) if gcd(X,n)=1 (X and n are relatively prime)
   - Known as Euler's theorem or Fermat–Euler theorem
   - generalization of Fermat's little theorem
 
 φ(n) = n * ∏ { (p-1)/p : p|n and p is prime }
 
 If n is prime, φ(n) = n-1. Thus X^(φ(n)) ≡ X^(n-1) ≡ 1 (mod n) as shown in Fermat's little theorem
 
 References:
  - CLRS 31.3 Modular arithmetic
  - Ant book 4.1 more complex math problems
  - https://en.wikipedia.org/wiki/Euler%27s_theorem
  - https://en.wikipedia.org/wiki/Euler%27s_totient_function
 
 */
int euler_phi(int n) {
  int res=n;
  // prime factorization
  for(int p=2; p*p<=n; ++p) if(n%p==0) {
    res=res/p*(p-1);
    while(n%p==0) n/=p;
  }
  if(n!=1) res=res/n*(n-1);
  return res;
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
  int m2 = powmod(7,560);
  assert(m2==108725231);
  
  LL m = 560;
  LL mi = modinv(m);
  assert((m*mi)%MOD==1);
  
  assert(euler_phi(36)==12);
  
  assert(factmod(560)==597965522);
  assert(choose(771,50)==275127687);
  assert(multichoose(771,50)==954694855);
  
  vector<vector<int>> dp(201,vector<int>(201,0));
  choose(200,dp);
  assert(dp[200][23]==choose(200,23));
}
