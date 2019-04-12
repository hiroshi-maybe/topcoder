#include <iostream>
#include <map>
#include <vector>
#include <math.h>
#include <iterator>
#include <sstream>
using namespace std;

// debug cerr
#define FORR(x,arr) for(auto& x:arr)
template<class Iter> void __kumaerrc(Iter begin, Iter end) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; }
void __kumaerr(istream_iterator<string> it) { (void)it; cerr<<endl; }
template<typename T, typename... Args> void __kumaerr(istream_iterator<string> it, T a, Args... args) { cerr<<*it<<"="<<a<<", ",__kumaerr(++it, args...); }
template<typename S, typename T> std::ostream& operator<<(std::ostream& _os, const std::pair<S,T>& _p) { return _os<<"{"<<_p.first<<','<<_p.second<<"}"; }
#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// a^b
/*
long long modpow(long long a, long long n, long long mod) {
  long long res = 1;
  while (n > 0) {
    if (n & 1) res = res * a % mod;
    a = a * a % mod;
    n >>= 1;
  }
  return res;
}

// a^-1
long long modinv(long long a, long long m) {
  long long b = m, u = 1, v = 0;
  while (b) {
    long long t = a / b;
    a -= t * b; swap(a, b);
    u -= t * v; swap(u, v);
  }
  u %= m;
  if (u < 0) u += m;
  return u;
}

// a^x ≡ b (mod. m) となる最小の正の整数 x を求める
long long modlog(long long a, long long b, int m) {
  a %= m, b %= m;
  
  // calc sqrt{M}
  long long lo = -1, hi = m;
  while (hi - lo > 1) {
    long long mid = (lo + hi) / 2;
    if (mid * mid >= m) hi = mid;
    else lo = mid;
  }
  long long sqrtM = hi;
  
  // {a^0, a^1, a^2, ..., a^sqrt(m)}
  map<long long, long long> apow;
  long long amari = 1;
  for (long long r = 0; r < sqrtM; ++r) {
    if (!apow.count(amari)) apow[amari] = r;
    (amari *= a) %= m;
  }
  
  // check each A^p
  long long A = modpow(modinv(a, m), sqrtM, m);
  amari = b;
  for (long long q = 0; q < sqrtM; ++q) {
    if (apow.count(amari)) {
      long long res = q * sqrtM + apow[amari];
      if (res > 0) return res;
    }
    (amari *= A) %= m;
  }
  
  // no solutions
  return -1;
}

int solve(int a, int b, int m) {
  int n = (int) sqrt (m + .0) + 1;
  
  int an = 1;
  for (int i = 0; i < n; ++i)
    an = (an * a) % m;
  
  map<int, int> vals;
  for (int p = 1, cur = an; p <= n; ++p) {
    if (!vals.count(cur))
      vals[cur] = p;
    cur = (cur * an) % m;
  }
  
  for (int q = 0, cur = b; q <= n; ++q) {
    if (vals.count(cur)) {
      int ans = vals[cur] * n - q;
      return ans;
    }
    cur = (cur * a) % m;
  }
  return -1;
}
*/
/*
int powmod (int a, int b, int p) {
  int res = 1;
  while (b)
    if (b & 1)
      res = int (res * 1ll * a % p),  --b;
    else
      a = int (a * 1ll * a % p),  b >>= 1;
  return res;
}

int generator (int p) {
  vector<int> fact;
  int phi = p-1,  n = phi;
  for (int i=2; i*i<=n; ++i)
    if (n % i == 0) {
      fact.push_back (i);
      while (n % i == 0)
        n /= i;
    }
  if (n > 1)
    fact.push_back (n);
  
  for (int res=2; res<=p; ++res) {
    bool ok = true;
    for (size_t i=0; i<fact.size() && ok; ++i)
      ok &= powmod (res, phi / fact[i], p) != 1;
    if (ok)  return res;
  }
  return -1;
}*/
/*
int main() {
  // 使い方の一例: a <= 10, b <= 10 に対して計算してみる
  const int MOD = 1000000007;

  cout<<generator(998244353)<<endl;
}*/

/*
int gcd(int a, int b) {
  return a ? gcd(b % a, a) : b;
}

int powmod(int _a, int b, int p) {
  long long a=_a;
  long long res = 1;
  while (b > 0) {
    if (b & 1) {
      res = res * a % p;
    }
    a = a * a % p;
    b >>= 1;
  }
  return (int)res;
}

// Finds the primitive root modulo p
int generator(int p) {
  vector<int> fact;
  int phi = p-1, n = phi;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      fact.push_back(i);
      while (n % i == 0)
        n /= i;
    }
  }
  if (n > 1)
    fact.push_back(n);
  
  dumpc(fact);
  
  for (int res = 2; res <= p; ++res) {
    bool ok = true;
`
    for (int i=0; i<fact.size()&&ok; ++i) {
      int fuckfuck1=phi/fact[i];
      int fuck1=powmod(res,phi/fact[i],p);
      dump(i,fuckfuck1,fuck1);
      ok&=powmod(res,phi/fact[i],p)!=1;
    }
    dump(res,ok);
    if(ok) return res;
  }
  return -1;
}

int primitiveroot(int M) {
  auto powmod=[&](int _a, int b, int MOD)->int {
    long long a=_a;
    long long res=1;
    for(int mask=1; mask<=b; mask<<=1) {
      if(b&mask) res*=a,res%=MOD;
      a*=a,a%=MOD;
    }
    return (int)res;
  };
  auto totient=[&](int n)->int {
    int res=n;
    for(int p=2; p*p<=n; ++p) if(n%p==0) {
      res=res/p*(p-1);
      while(n%p==0) n/=p;
    }
    if(n!=1) res=res/n*(n-1);
    return res;
  };
  
  vector<int> P;
  int phi=totient(M),n=phi;
  assert(phi==M-1);
  for(int i=2; i*i<=n; ++i) if(n%i==0) {
    P.push_back(i);
    while (n%i==0) n/=i;
  }
  if(n>1) P.push_back(n);
  
  dumpc(P);
  
  for(int res=2; res<=M; ++res) {
    bool ok = true;
    for (int i=0; i<P.size()&&ok; ++i) {
      int fuckfuck2=phi/P[i];
      int fuck2=powmod(res,phi/P[i],M);
      dump(i,fuckfuck2,fuck2);
      ok&=powmod(res,phi/P[i],M)!=1;
    }
    dump(res,ok);
    if(ok) return res;
  }
  return -1;
}

// This program finds all numbers x such that x^k = a (mod n)
int main() {
  assert(primitiveroot(998244353)==3);
  assert(primitiveroot(1000000007)==5);
  assert(generator(998244353)==3);
  assert(generator(1000000007)==5);
  int n, k, a;
  scanf("%d %d %d", &n, &k, &a);
  if (a == 0) {
    puts("1\n0");
    return 0;
  }
  
  int g = generator(n);
  
  // Baby-step giant-step discrete logarithm algorithm
  int sq = (int) sqrt (n + .0) + 1;
  vector<pair<int, int>> dec(sq);
  for (int i = 1; i <= sq; ++i)
    dec[i-1] = {powmod(g, i * sq * k % (n - 1), n), i};
  sort(dec.begin(), dec.end());
  int any_ans = -1;
  for (int i = 0; i < sq; ++i) {
    int my = powmod(g, i * k % (n - 1), n) * a % n;
    auto it = lower_bound(dec.begin(), dec.end(), make_pair(my, 0));
    if (it != dec.end() && it->first == my) {
      any_ans = it->second * sq - i;
      break;
    }
  }
  
  if (any_ans == -1) {
    puts("0");
    return 0;
  }
  
  int y=any_ans,gy=powmod(g,y,n),gyk=powmod(gy,k,n);
  int gk=powmod(g,k,n),gky=powmod(gk,y,n);
  dump(g,y,k,gy,gyk,gk,gky);
    assert(powmod(powmod(g,any_ans,n),k,n)==a);
  
  // Print all possible answers
  int delta = (n-1) / gcd(k, n-1);
  vector<int> ans;
  for (int cur = any_ans % delta; cur < n-1; cur += delta)
    ans.push_back(powmod(g, cur, n));
  sort(ans.begin(), ans.end());
  printf("%d\n", ans.size());
  for (int answer : ans)
    printf("%d ", answer);
}
*/

typedef long long ll;
int K;
int B[101];
int N,M;
//ll mo=998244353;
ll mo=1000000007;

int gcd(int a, int b) {
  return a ? gcd(b % a, a) : b;
}

ll modpow(ll a, ll n = mo-2, ll m=mo) {
  ll r=1;
  while(n) r=r*((n%2)?a:1)%m,a=a*a%m,n>>=1;
  return r;
}

int totient(int v) {
  int ret=v;
  for(int i=2;i*i<=v;i++) if(v%i==0) {
    ret=ret/i*(i-1);
    while(v%i==0) v/=i;
  }
  if(v>1) ret=ret/v*(v-1);
  return ret;
}

int mod_root(int p,int a) { // x^p=a mod mo
  vector<int> D;
  for(int i=2;i*i<=mo-1;i++) if((mo-1)%i==0) D.push_back(i),D.push_back((mo-1)/i);
  int g=2;
  while(1) {
    int ng=0;
    FORR(d,D) if(modpow(g,d)==1) ng=1;
    if(ng==0) break;
    g++;
  }
  
  ll cur=a;
  int rg=modpow(g);
  int mstep=sqrt(mo);
  
  dump(p,a,mo,mstep,g);
  
  map<int,int> M;
  int i;
  for(i=0; i<mstep+3; ++i) {
    M[cur]=i;
    cur=cur*rg%mo;
  }
  dump(M.size());
  ll pg=modpow(g,mstep);
  int x=-1,step=0;
  cur=1;
  int cnt=0;
  while(x==-1) {
    if(M.count(cur)) {
      x=step+M[cur];
      dump(cur,M[cur],cnt,x);
      break;
    }
//    M[cur]=step;
    cur=cur*pg%mo;
    step+=mstep;
    ++cnt;
  }

  dump(x,mstep,cnt,M[cur],1ll*mstep*cnt+M[cur],modpow(g,x));
  assert(x==mstep*cnt+M[cur]);
  assert(modpow(g,x)==a);
  
  // g^x=aなのでg^(p*q)=g^x=aとしてq=x/p (mod mo-1) mo-1は合成数なのでGCDで割って対応
  int tmo=mo-1;
  int gcd2=gcd(tmo,p);
  if(x%gcd2) return -1;
  tmo/=gcd2;
  x/=gcd2;
  p/=gcd2;
  return modpow(g,1LL*x*modpow(p,totient(tmo)-1,tmo)%tmo);
}

int main() {
  {
    int k=123456,a=789;
    int x=mod_root(k,a);
//    dump(x);
//    assert(modpow(x,k)==a);
  }
  
  {
    int a=4, p=7;
    int cur=1;
    for(int x=0; x<2*p; ++x) {
      cur=cur*a%p;
      dump(x+1,cur);
    }
  }
}
