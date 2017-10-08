#include <iostream>
#include <cassert>
#include <tuple>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;

/*
 
 links
 http://sucrose.hatenablog.com/entry/2014/10/10/235805
 https://www.slideshare.net/kazumamikami1/ss-24712271
  - divisors, prime factorization, GCD
 
 */

/*
 
 check if N is prime, O(√N) time
 
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
 
 compute all the divisers of N, O(√N) time
 
  - size of result is upper-bounded by HCN(N)
   - highly composite number: http://wwwhomes.uni-bielefeld.de/achim/highly.txt
   - HCN(10^9)≈1440, HCN(10^6)≈256
  - result is sorted
 
 Usage:
  vector<int> divs = divisors(12) // divs={1,2,3,4,6,12}
 
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
  vector<int> facts = primeFactors(12) // facts={2,2,3}
  vector<int> ps = primes(12)          // ps   =  {2,3}

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
vector<LL> primes(LL n) {
  vector<LL> res=primeFactors(n);
  res.erase(unique(res.begin(),res.end()),res.end());
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
  
  vector<LL> divs = {1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 20, 24, 30, 40, 60, 120};
  assert(divs==divisors(120));
  
  vector<LL> fs = {2,2,2,3,5};
  vector<LL> ps = {2,3,5};
  assert(fs==primeFactors(120));
  assert(ps==primes(120));
  
//  getMaxFact(1e7);
}
