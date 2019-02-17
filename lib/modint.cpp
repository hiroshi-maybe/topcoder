#include <iostream>
#include <map>
#include <cassert>
#include <unordered_map>
#include <math.h>
using namespace std;

const int MOD=1e9+7;
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

/*
 
 Compute minimum log_{a}(b) (mod M) in O(sqrt(M)) time, O(√M*lg M) time
 
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
int modlog(int a, int b) {
  int sqrtM=(int)sqrt(MOD+.0)+1;
  ModInt ga=ModInt(a).pow(sqrtM);
  unordered_map<int, int> G;
  ModInt cur=ModInt(ga);
  for(int p=1; p<=sqrtM; ++p) {
    if(!G.count(cur.val)) G[cur.val]=p;
    cur*=ga;
  }
  int res=MOD+10;
  cur=ModInt(b);
  for(int q=0; q<=sqrtM; ++q) {
    if(G.count(cur.val)) res=min(res,G[cur.val]*sqrtM-q);
    cur*=ModInt(a);
  }
  return res>MOD?-1:res;
}

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
      assert(modlog(a,b)==log_[a-2][b-1]);
    }
  }
}

int main(int argc, char const *argv[]) {
  test_modint();
  test_modlog();
}
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address modint.cpp && ./a.out
