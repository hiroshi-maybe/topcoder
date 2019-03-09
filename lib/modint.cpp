#include <iostream>
#include <iterator>
#include <sstream>
#include <functional>
#include <vector>
#include <map>
#include <cassert>
#include <unordered_map>
#include <math.h>
using namespace std;

// debug cerr
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

const int MOD=1000000007;
//const int MOD=998244353;
struct ModInt {
  unsigned int val;
  ModInt(): val(0) {}
  ModInt(int v) { norm(v%MOD); }
  ModInt(long long v) { norm(v%MOD); }
  ModInt& norm(long long v) {
    v=v<0?v%MOD+MOD:v; // negative
    v=v>=MOD?v-MOD:v; // mod
    val=(unsigned int)v;
    return *this;
  }
  explicit operator bool() const { return val!=0; }
  ModInt operator-() const { return ModInt(0)-*this; }
  ModInt &operator+=(ModInt that) { return norm((long long)val+that.val); }
  ModInt &operator-=(ModInt that) { return norm((long long)val-that.val); }
  ModInt &operator*=(ModInt that) { val=(unsigned long long)val*that.val%MOD; return *this; }
  ModInt &operator/=(ModInt that) { return *this*=that.inv(); }
  ModInt operator+(ModInt that) const { return ModInt(*this)+=that; }
  ModInt operator-(ModInt that) const { return ModInt(*this)-=that; }
  ModInt operator*(ModInt that) const { return ModInt(*this)*=that; }
  ModInt operator/(ModInt that) const { return ModInt(*this)/=that; }
  ModInt pow(long long n) const {
    ModInt x=*this, res=1;
    while(n>0) {
      if(n&1) res*=x;
      x*=x,n>>=1;
    }
    return res;
  }
  ModInt inv() const { return (*this).pow(MOD-2); }
  bool operator==(ModInt that) const { return val==that.val; }
  bool operator!=(ModInt that) const { return val!=that.val; }
  friend ostream& operator<<(ostream& os, const ModInt& that) { return os<<that.val; }
};

void test_modint() {
  map<long long, unsigned int> inittests{
    {10ll,10},{(long long)MOD,0},{10ll*MOD,0},{-1ll,1000000006},{0ll,0}
  };
  for(auto it : inittests) {
    auto m=ModInt(it.first);
    assert(m.val==it.second);
  }
  
  assert(ModInt(1));
  assert(!ModInt(0));
  assert(!ModInt((int)MOD));
  
  assert(-ModInt(1)==ModInt(1000000006));
  assert(-ModInt(0)==ModInt(0));
  
  assert(ModInt((int)1e9)+ModInt(10)==ModInt(3));
  {
    auto m=ModInt(10); m+=ModInt(10);
    assert(m==ModInt(20));
  }
  
  assert(ModInt(10)-ModInt(110)==ModInt(999999907));
  {
    auto m=ModInt(100); m-=ModInt(10);
    assert(m==ModInt(90));
  }
  
  assert(ModInt(10)*ModInt(10)==ModInt(100));
  {
    auto m=ModInt(20000000); m*=ModInt(12345678);
    assert(m==ModInt(558271609));
  }
  
  assert(ModInt(12)/ModInt(3)==ModInt(4));
  {
    auto m=ModInt(20000000); m/=ModInt(12345678);
    assert(m==ModInt(914382029));
  }
  
  assert(ModInt(3).inv()==ModInt(333333336));
  assert(ModInt(12345678).inv()==ModInt(325842698));
  
  assert(ModInt(3)==ModInt(3));
  assert(ModInt(0)==ModInt(1000000007));
  assert(ModInt(-1)==ModInt(1000000006));
  assert(ModInt(-1)==-ModInt(1));
  
  assert(ModInt(2)!=ModInt(3));
  assert(ModInt(0)!=ModInt(1000000008));
}

/*
 
 Compute minimum discrete logarithm log_{a}(b) (mod M) in O(√M*lg M) time
 
  - result is `0` if b=1
  - Baby-step, Giant-step and meet-in-the-middle
  - a^x≡b (mod M), x=√M*p-q
   - `p` is giant-step, `q` is baby-step
 
     a^x≡b (mod M)
 <=> a^(√M*p-q)≡b (mod M)
 <=> a^(√M*p)≡b*a^q (mod M)
 <=> f1(p)≡f2(q) (mod M) where f1(p)=a^(√M*p), f2(q)=b*a^q
 
 Find (p,q) which satisfies f1(p)≡f2(q) (mod M)
 
 References:
  - https://cp-algorithms.com/algebra/discrete-log.html
  - https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a#6-%E9%9B%A2%E6%95%A3%E5%AF%BE%E6%95%B0-log_a-b
  - https://en.wikipedia.org/wiki/Baby-step_giant-step
 
 */
int powmod(int _a, int b, int MOD) {
  long long a=_a;
  long long res=1;
  for(int mask=1; mask<=b; mask<<=1) {
    if(b&mask) res*=a,res%=MOD;
    a*=a,a%=MOD;
  }
  return (int)res;
}
int modlog(int a, int b, int MOD) {
  int sqrtM=(int)sqrt(MOD+.0)+1;
  long long ga=powmod(a,sqrtM,MOD);
  unordered_map<int, int> G;
  long long cur=ga;
  for(int p=1; p<=sqrtM; ++p) {
    if(!G.count(cur)) G[cur]=p;
    cur=cur*ga%MOD;
  }
  int res=MOD+10;
  cur=b;
  for(int q=0; q<=sqrtM; ++q) {
    if(G.count(cur)) {
      res=min(res,G[cur]*sqrtM-q);
    }
    cur=cur*a%MOD;
  }
  if(res>MOD) res=-1;
  if(res>=0) assert(powmod(a,res,MOD)==b);
  return res;
}

void test_modlog() {
  // from https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a#6-%E9%9B%A2%E6%95%A3%E5%AF%BE%E6%95%B0-log_a-b
  int log_[9][10]={
    {0,1,385273928,2,-1,385273929,384931854,3,270547853,-1 },
    {0,316884446,1,133768889,-1,316884447,70669385,450653335,2,-1 },
    {0,250000002,192636964,1,-1,442636966,192465927,250000003,385273928,-1 },
    {0,381838282,884237698,763676564,1,266075974,936544532,145514840,768475390,381838283 },
    {0,367158949,132841055,234317895,-1,1,103274402,101476841,265682110,-1 },
    {0,91517237,167141706,183034474,-1,258658943,1,274551711,334283412,-1 },
    {0,166666668,461757978,333333336,-1,128424643,128310618,1,423515953,-1 },
    {0,158442223,250000002,316884446,-1,408442225,285334694,475326669,1,-1 },
    {0,323655130,504275348,647310260,676344877,827930478,500000012,970965390,8550690,1 },
  };
  
  for (long long a = 2; a <= 10; ++a) {
    for (long long b = 1; b <= 10; ++b) {
      assert(modlog(a,b,1000000007)==log_[a-2][b-1]);
    }
  }
  // no `x` s.t. a^x=0
  assert(modlog(123,0,MOD)==-1);
}

/*
 
 Compute one of minimum discrete root √_{k}(a) (mod M) in O(res*log^2(n)+√M*lg M) time
 
 - Reduce to discrete logarithm problem
 - x^k≡a (mod M)
 
 1. find primitive root `g` of `M`
 
 https://cp-algorithms.com/algebra/primitive-root.html
 
 find `g`∈{1,..,M} s.t. f[i] is distinct where f[i] = g^(𝜑(n)/p_i)
 
 2. compute discrete logarithm of (g^k)^y ≡ a (mod M)
 
     x^k≡a (mod M)
 <=> (g^y)^k ≡ a (mod M)
 <=> (g^k)^y ≡ a (mod M)
 
 Compute `y` s.t. y = log_{g^k}(a) (mod M)
 
 x = g^y (mod M)
 
 References:
  - https://cp-algorithms.com/algebra/discrete-root.html
   - code is broken
  - http://kmjp.hatenablog.jp/entry/2019/02/01/0930
  - https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a#7-%E5%B9%B3%E6%96%B9%E5%89%B0%E4%BD%99-a
  - http://kirika-comp.hatenablog.com/entry/2018/03/12/210446
 
 Used problem:
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/LunarNewYearAndARecursiveSequence.cpp#L260
 
 */
int primitiveroot(int M) {
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
  for(int i=2; i*i<=n; ++i) if(n%i==0) {
      P.push_back(i);
      while (n%i==0) n/=i;
  }
  if(n>1) P.push_back(n);
  for(int res=2; res<=M; ++res) {
    bool ok = true;
    for (int i=0; i<P.size()&&ok; ++i) ok&=powmod(res,phi/P[i],M)!=1;
    if(ok) return res;
  }
  return -1;
}
int modroot(int k, int a, int MOD) {
  if(a==0) return 0;
  function<int(int,int)> gcd=[&](int a, int b)->int { return b==0?a:gcd(b,a%b); };
  int g=primitiveroot(MOD);
  int y=modlog(powmod(g,k,MOD),a,MOD);
  if(y==-1) return -1;

  assert(powmod(powmod(g,y,MOD),k,MOD)==a);
  int x=powmod(g,y,MOD);
  assert(powmod(x,k,MOD)==a);
  
  return x;
  /*
  cout<<x<<endl;
  int delta=(MOD-1)/gcd(k,MOD-1);
  vector<int> res;
  for(int cur=x%delta; cur<MOD-1; cur+=delta) res.push_back(powmod(g,cur,MOD));
  sort(res.begin(),res.end());
  return res;*/
}

void test_modroot() {
  {
    // primitive root
    assert(primitiveroot(1000000007)==5);
    assert(primitiveroot(998244353)==3);
  }
  
  {
    assert(modroot(123456,0,998244353)==0);
    assert(modroot(123456,789,998244353)==-1);
    assert(modroot(123,456,998244353)==816683442);
    assert(modroot(12345,6789,998244353)==150873265);

    assert(modroot(123456,0,1000000007)==0);
    assert(modroot(123456,789,1000000007)==-1);
    assert(modroot(123,456,1000000007)==169072236);
    assert(modroot(12345,6789,1000000007)==540590301);
  }
}

/*
 
 Solver of system of modular linear equations,
 
  - compute (b,m) s.t. x≡b(mod m), ∀i A[i]*x ≡ B[i] (mod M[i])
  - (0,-1) => no solution (∃i s.t. gcd(A[i],M[i]) ⧷ B[i])
   - There is a solution of a*x≡b(mod m) only when gcd(a,m) divides b
  - Implementtion coming from Ant book 4.1 complex math problems
 
 # Proof of correctness
 
 Suppose we have x[i] ≡ b[i] (mod m[i]) after solving A[i]*x[i]≡B[i](mod M[i]).
 
 Thus x[i]=b[i]+m[i]*t[i]
 
 We have A[i+1]*x[i]≡B[i+1](mod M[i+1]).
 If d=gcd(A[i+1],M[i+1]), A[i+1]'*x[i]≡B[i+1]' (mod M[i+1]')
 where A[i+1]'=A[i+1]/d, B[i+1]'=B[i+1]/d, M[i+1]'=M[i+1]/d
 x[i] in this formula can be substituted by b[i]+m[i]*t[i]
 
   A[i+1]'*x[i]≡B[i+1]' (mod M[i+1]')
   A[i+1]'*(b[i]+m[i]*t[i])≡B[i+1]' (mod M[i+1]')
   A[i+1]'*m[i]*t[i] ≡ B[i+1]' - A[i+1]'*b[i] (mod M[i+1]')
   p * t[i] ≡ q (mod M[i+1]') where p=A[i+1]'*m[i], q=B[i+1]'-A[i+1]'*b[i]
 
 This can be solved by mod inverse p^-1
 t[i] ≡ p^-1*q (mod M[i+1]')
 Now we get t[i] = M[i+1]' * t[i+1] + p^-1*q
 
   x[i+1]
   = x[i]
   = b[i]+m[i]*t[i]
   = b[i]+m[i]*(M[i+1]' * t[i+1] + p^-1*q)
   = (b[i]+m[i]*p^-1*q) + (m[i]*M[i+1]')*t[i+1]
   = b[i+1] + m[i+1] * t[i+1]
 
 Thus we have recurrence relations:
 
   b[i+1] = b[i] + m[i] * p^-1*q
   m[i+1] = m[i] * M[i+1]'
 
 We can recursively calculate b[i] and m[i] (base case: x[0]=0, t[0]=1) by DP.
 
 Result of system of modular linear equations is (b[N], m[N]), x ≡ b[N] (mod m[N])
 
 If { m[i] } is relatively prime AND ∀i a[i]==1, m[N] = ∏ M[i] by Chinese Remainder Theorem.
 
 Reference:
  - Ant book 4.1 complex math problems
  - https://en.wikipedia.org/wiki/Chinese_remainder_theorem
  - "CLRS 31.4 Solving modular linear equations" shows solver of single equation
   - this solver is generalized to solve system of equations
 
 # Usage
 
 // x≡2(mod 3), x≡3(mod 5), x≡2(mod 7)
 vector<int> A={1,1,1};
 vector<int> B={2,3,2};
 vector<int> M={3,5,7};
 auto p = MLE.solve(A,B,M); // p.first==23, p.second==105
 
 Used problems:
  - https://github.com/k-ori/topcoder/blob/646f1e95c346aaaef68428e5825027350d4bf707/QuadraticIdentity/QuadraticIdentity.cpp#L122
 
 */
struct ModularLinearEquations {
public:
  ModularLinearEquations() {}
  
  pair<int, int> solve(const vector<int>& A, const vector<int>& B,
                       const vector<int>& M) {
    int b=0,m=1;
    for(int i=0; i<A.size(); i++) {
      int p=A[i]*m,q=B[i]-A[i]*b,d=gcd(M[i],p),mi=M[i]/d;
      if (q%d!=0) return make_pair(0,-1); // solution not found
      int t=(_modinv(p/d,mi)*q/d)%(mi);
      b=b+m*t;
      m*=mi;
    }
    b=(b+m)%m; // ensure that x is non-negative
    return make_pair(b%m,m);
  }
  
  /*
   
   compute mod inverse of n, O(lg max(a,m)) time
   
    - compute x s.t. a*x≡1(mod m)
    - a and m should be co-prime (gcd(a,m)==1)
    - from Ant book 4.1 complex math problems
    - CLRS 31.4 Solving modular linear equations
   
     a*x≡1(mod m)
     <=> ∃k, a*x=k*m+1
     <=> a*x-k*m=1 // x can be computed by extgcd(a,m)
   
   Usage:
   
   int d = modinv(5,11) // d=9
   
   */
  int _modinv(int a, int m) {
    assert(gcd(a,m)==1);
    int x,y;
    _extgcd(a,m,x,y);
    return (m+x%m)%m; // ensure mod inverse is non-negative
  }
  
  /*
   
   extended GCD, O(lg max(a,b)) time
   
    - compute (x,y,z) s.t. a*x+b*y=z, z=gcd(a,b)
    - from Ant book 2.6 elementary math techniques
    - CLRS "31.3 Modular arithmetic" and "31.4 Solving modular linear equations"
   
   Usage:
   
   int x, y;
   int z = extgcd(99,78,x,y); // (x,y)=(-11,14), z=gcd(99,78)=3
   
   */
  int _extgcd(int a, int b, int& x, int& y) {
    if(b==0) {
      x=1,y=0;
      return a;
    }
    int d=_extgcd(b, a%b, y, x);
    y-=(a/b)*x;
    return d;
  }
private:
  int gcd(int a, int b) {
    return b==0?a:gcd(b,a%b);
  }
} MLE;

void test_mle() {
  assert(MLE._modinv(5,11)==9);
  int x,y;
  int d=MLE._extgcd(99,78,x,y);
  assert(d==3);
  assert(x==-11);
  assert(y==14);
  
  vector<int> A={1,1,1};
  vector<int> B={2,3,2};
  vector<int> M={3,5,7};
  auto p = MLE.solve(A,B,M);
  assert(p.first==23);
  assert(p.second==105);
}

int main(int argc, char const *argv[]) {
  test_modint();
  test_modlog();
  test_modroot();
  test_mle();
}
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address modint.cpp && ./a.out
