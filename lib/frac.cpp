#include <iostream>
#include <sstream>
#include <cassert>
#include <utility>

using namespace std;

/*
 
 Fraction computation library
 
  - N^2 should fit in signed long long (<1e18) in operators
 
 Used problems:
  - https://github.com/k-ori/topcoder/blob/master/MinimizeAbsoluteDifferenceDiv1/MinimizeAbsoluteDifferenceDiv1.cpp#L119
  - https://github.com/k-ori/topcoder/blob/master/BestView/BestView.cpp#L64
  - https://github.com/hiroshi-maybe/leetcode/blob/master/972-equal-rational-numbers/equal-rational-numbers.cpp#L37
  - https://github.com/hiroshi-maybe/GCJ/blob/master/2019-R2/NewElementsPart1.cpp#L103
  - https://github.com/hiroshi-maybe/GCJ/blob/master/2019-R2/NewElementsPart2.cpp#L47
  - https://github.com/hiroshi-maybe/topcoder/blob/master/solutions/AddPeriodic/AddPeriodic.cpp#L42
 
 */

struct Frac {
public:
  // numerator / denominator
  long long n,d;
  Frac(): n(0),d(1) {}
  Frac(int nn) : n(nn), d(1) {}
  Frac(long long nn, long long dd) { norm(nn,dd); }
  Frac(int nn, int dd) { norm(nn,dd); }
  Frac& norm(long long nn, long long dd) {
    assert(dd!=0);
    if(dd<0) nn*=-1,dd*=-1;
    bool neg=nn<0;
    nn=neg?-nn:nn;
    long long g=gcd(nn,dd);
    nn/=g,dd/=g;
    this->n=nn;
    if(neg) this->n=-1*this->n;
    this->d=dd;
    return *this;
  }
  Frac abs() { return Frac(n<0?-n:n,d); }
  Frac inv() { return Frac(d,n); }
  Frac &operator -() { n=-n; return *this; }
  Frac &operator += (Frac that) { long long nn=(long long)n*that.d+(long long)that.n*d,dd=(long long)d*that.d; return norm(nn,dd); }
  Frac &operator -= (Frac that) { *this+=-that; return *this; }
  Frac &operator *=(Frac that) { long long nn=(long long)n*that.n,dd=(long long)d*that.d; return norm(nn,dd); }
  Frac &operator /= (Frac that) { *this*=Frac(that.d,that.n); return *this; }
  Frac operator+(Frac that) const { return Frac(*this)+=that; }
  Frac operator-(Frac that) const { return Frac(*this)-=that; }
  Frac operator*(Frac that) const { return Frac(*this)*=that; }
  Frac operator/(Frac that) const { return Frac(*this)/=that; }
  bool operator < (Frac that) { return (long long)n*that.d<(long long)that.n*d; }
  bool operator > (Frac that) { return that<Frac(*this); }
  bool operator == (Frac that) { return n==that.n&&d==that.d; }
  bool operator <= (Frac that) { return Frac(*this)<that||Frac(*this)==that; }
  bool operator >= (Frac that) { return Frac(*this)>that||Frac(*this)==that; }
  friend ostream& operator<<(ostream& os, const Frac& that) { return os<<that.n<<"/"<<that.d; }
private:
  long long gcd(long long a, long long b) {
    return b==0?a:gcd(b,a%b);
  }
};

int main(int argc, char const *argv[]) {
  Frac p(10,20);
  assert(p.n==1&&p.d==2);
  
  Frac x(5,6),y(3,4);
  auto a=x+y;
  assert(a.n==19&&a.d==12);
  
  auto s=x-y;
  assert(s.n==1&&s.d==12);

  auto m=x*y;
  assert(m.n==5&&m.d==8);

  auto d=x/y;
  assert(d.n==10&&d.d==9);

  Frac z(-5,6);
  auto a1=z.abs();
  assert(a1.n==5&&a1.d==6);
  auto a2=x.abs();
  assert(a2.n==5&&a2.d==6);

  assert(x>y);
  Frac x2(2,6),y2(1,3);
  assert(x2==y2);
  assert(y<x);
}
// g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address frac.cpp && ./a.out
