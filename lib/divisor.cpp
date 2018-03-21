#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

typedef long long LL;

/*
 
 links:
 - http://sucrose.hatenablog.com/entry/2014/10/10/235805
  - Prime factorization, Sieve of Eratosthenes
 - https://www.slideshare.net/kazumamikami1/ss-24712271
  - divisors, prime factorization, GCD
 - http://d.hatena.ne.jp/uwitenpen/20111203
  - finding primes
 
 */

/*
 
 check if N is prime by trial division, O(√N) time
 
 Usage:
  isPrime(131) // true
  isPrime(120) // false
 
 */
bool isPrime(LL N) {
  if(N<2) return false;
  for(LL p=2; p*p<=N; ++p) if(N%p==0) return false;
  return true;
}

/*
 
 primes in range [1,N] by sieve of eratosthenes, O(N*lg lg N) time, O(N) space
 
 - this works if approximately N <= 10^7
 
 Sieve of Eratosthenes
  - http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 
 Usage:
   vector<int> ps = findPrimes(10); // ps={2,3,5,7}
 
 */
vector<int> findPrimes(int N) {
  vector<int> fs(N+1, true);
  fs[0]=fs[1]=false;
  for(int p=2; p*p<=N; ++p) if(fs[p]) {
    for(int q=p*p; q<=N; q+=p) fs[q]=false;
  }
  vector<int> res;
  for(int n=2; n<=N; ++n) if(fs[n]) res.push_back(n);
  return res;
}

/*
 
 compute all the divisers of N by trial division, O(√N) time
 
 Trial division:
  - https://en.wikipedia.org/wiki/Trial_division

 Summary:
  - size of result is upper-bounded by HCN(N)
   - highly composite number: http://wwwhomes.uni-bielefeld.de/achim/highly.txt
   - HCN(10^9)≈1440, HCN(10^6)≈256
  - result is sorted
 
 Usage:
  vector<int> divs = divisors(12); // divs={1,2,3,4,6,12}
 
 */
vector<LL> divisors(LL N) {
  assert(N>=1);
  vector<LL> res;
  for(LL p=1; p*p<=N; ++p) if(N%p==0) {
    res.push_back(p);
    if(p!=N/p) res.push_back(N/p);
  }
  sort(res.begin(),res.end());
  return res;
}

/*
 
 prime factorization of N by trial division, O(√N) time
 
 Prime factor
  - https://en.wikipedia.org/wiki/Prime_factor
 Trial division
  - https://en.wikipedia.org/wiki/Trial_division
 
 primeFactors()
  - returns list of factors with multiple primes
    - special version of divisor computation
  - result is sorted
  - size of result equals to 𝛺(n)
   - https://oeis.org/A001222

 𝛺'(n) = max { 𝛺(x) : 1<=x<=n }
 𝛺'(10^6) = 19, n=   524288, prime factors = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
 𝛺'(10^7) = 23, n=  8388608, prime factors = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
 𝛺'(10^8) = 26, n= 67108864, prime factors = { 2x26 }
 𝛺'(10^9) = 29, n=536870912, prime factors = { 2x29 }

 primes()
  - take distinct factors out of prime factors
  - result is sorted
  - size of result equals to 𝜔(n)
   - https://oeis.org/A001221

 𝜔'(n) = max { 𝜔(x) : 1<=x<=n }
 𝜔'(10^6) = 7, n=   510510, prime factors = {2,3,5,7,11,13,17}
 𝜔'(10^7) = 8, n=  9699690, prime factors = {2,3,5,7,11,13,17,19}
 𝜔'(10^9) = 9, n=223092870, prime factors = {2,3,5,7,11,13,17,19,23}

 Usage:
  vector<int> facts = primeFactors(12);      // facts={2,2,3}
  vector<int> ps = distinctPrimeFactors(12); // ps   ={2,3}

 Used problems:
  - https://github.com/k-ori/topcoder/blob/master/FractionInDifferentBases/FractionInDifferentBases.cpp
  - https://github.com/k-ori/topcoder/blob/master/MagicDiamonds/MagicDiamonds.cpp#L107
  - https://github.com/k-ori/topcoder/blob/master/DivideAndShift/DivideAndShift.cpp#L147
 
 */
vector<LL> primeFactors(LL n) {
  assert(n>=1);
  vector<LL> res;
  for(LL p=2; p*p<=n; ++p) while(n%p==0) {
    res.push_back(p);
    n/=p;
  }
  if(n>1) res.push_back(n);
  return res;
}
vector<LL> distinctPrimeFactors(LL n) {
  /*
  vector<LL> res=primeFactors(n);
  res.erase(unique(res.begin(),res.end()),res.end());
  return res;
   */
  assert(n>=1);
  vector<LL> res;
  for(LL p=2; p*p<=n; ++p) if(n%p==0) {
    res.push_back(p);
    while(n%p==0) n/=p;
  }
  if(n>1) res.push_back(n);
  return res;
}

/*
 
 Count the positive integers up to a given integer n that are relatively prime to n, O(√N) time
 (compute Euler's totient function φ(n) (phi function))
 
 - φ(n) counts the positive integers up to a given integer n that are relatively prime to n
 - X^(φ(n)) ≡ 1 (mod n) if gcd(X,n)=1 (X and n are relatively prime)
  - Known as Euler's theorem or Fermat–Euler theorem
  - generalization of Fermat's little theorem
 
 φ(n) = n * ∏ { (p-1)/p : p|n and p is prime factor of n }
 
 If n is prime, φ(n) = n-1. Thus X^(φ(n)) ≡ X^(n-1) ≡ 1 (mod n) as shown in Fermat's little theorem
 
 References:
  - CLRS 31.3 Modular arithmetic
  - Ant book 4.1 more complex math problems
  - https://en.wikipedia.org/wiki/Euler%27s_theorem
  - https://en.wikipedia.org/wiki/Euler%27s_totient_function
 
 Usage:
  int phi_n = totient(100);
 
 */
int totient(LL N) {
  vector<LL> ps=distinctPrimeFactors(N);
  int res=N;
  for(auto p : ps) {
    res=res/p*(p-1);
  }
  return res;
}
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

/*
 
 Find numbers coprime to N in range [1,N], O(N*lg N) time
 
 If you want to find only number of coprimes, `totient(N)` is more efficient (O(√N) time).
 
 Usage:
   vector<int> cops = findCoprimes(10); // cops={1,3,7,9}
 
 */
int gcd(int a, int b) { return b==0?a:gcd(b,a%b); }
vector<int> findCoprimes(int N) {
  vector<int> res;
  for(int n=1; n<=N; ++n) if(gcd(n,N)==1) res.push_back(n);
  return res;
}

// main and test
void getMaxFact(int maxn) {
  vector<LL> xs1,xs2;
  int x1=0,x2=0,n1=0,n2=0;
  for(int n=1; n<=maxn; ++n) {
    vector<LL> xs=primeFactors(n);
    if(xs.size()>x1) {
      n1=n;
      x1=xs.size();
      xs1=xs;
    }
    xs.erase(unique(xs.begin(),xs.end()),xs.end());
    if(xs.size()>x2) {
      n2=n;
      x2=xs.size();
      xs2=xs;
    }
  }
  cout << x1 << "(" << n1 << ")" <<endl;
  for(LL x : xs1) cout << x << ",";
  cout << endl;
  cout << x2 << "(" << n2 << ")" <<endl;
  for(LL x : xs2) cout << x << ",";
  cout << endl;
}

int main(int argc, char const *argv[]) {
  assert(isPrime(131));
  assert(!isPrime(120));

  vector<int> primes100 = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
  assert(findPrimes(100)==primes100);
  
  vector<LL> divs = {1,2,3,4,5,6,8,10,12,15,20,24,30,40,60,120};
  assert(divs==divisors(120));
  
  vector<LL> fs = {2,2,2,3,5};
  vector<LL> ps = {2,3,5};
  assert(fs==primeFactors(120));
  assert(ps==distinctPrimeFactors(120));
//  getMaxFact(1e7);
  assert(totient(36)==12);

  vector<int> coprimes100 = {1,3,7,9,11,13,17,19,21,23,27,29,31,33,37,39,41,43,47,49,51,53,57,59,61,63,67,69,71,73,77,79,81,83,87,89,91,93,97,99};
  assert(findCoprimes(100)==coprimes100);
}

