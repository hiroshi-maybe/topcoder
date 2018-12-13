#include <iostream>
#include <map>
#include <cassert>
using namespace std;

const int MOD=1e9+7;
struct ModInt {
  uint val;
  ModInt(): val(0) {}
  ModInt(int v) { norm(v%MOD); }
  ModInt(long long v) { norm(v%MOD); }
  ModInt& norm(long long v) {
    v=v<0?v%MOD+MOD:v; // negative
    v=v>=MOD?v-MOD:v; // mod
    val=(uint)v;
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
  map<long long, uint> inittests{
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

int main(int argc, char const *argv[]) {
  test_modint();
}
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address modint.cpp && ./a.out
