#include <iostream>
#include <sstream>
#include <cassert>
#include <utility>

using namespace std;

struct Frac {
public:
  // numerator / denominator
  long long n,d;
  Frac(int n, int d) {
    assert(d>0);
    bool neg=n<0;
    n=abs(n);
    long long g=gcd(n,d);
    this->n=n/g;
    if(neg) this->n=-1*this->n;
    this->d=d/g;
  }
  Frac add(Frac &y) {
    long long l=lcm(d,y.d);
    long long n1=n*l/d,n2=y.n*l/y.d;
    return Frac(n1+n2,l);
  }
  Frac sub(Frac &y) {
    Frac yy(-y.n,y.d);
    return add(yy);
  }
  Frac mul(Frac &y) {
    long long nn=n*y.n,dd=d*y.d;
    long long g=gcd(nn,dd);
    return Frac(nn/g, dd/g);
  }
  Frac div(Frac &y) {
    Frac yy(y.d,y.n);
    return mul(yy);
  }
  int comp(Frac &y) {
    Frac a=sub(y);
    if(a.n==0) return 0;
    return a.n>0?1:-1;
  }
private:
  long long gcd(long long a, long long b) {
    return b==0?a:gcd(b,a%b);
  }
  long long lcm(long long a, long long b) {
    return a*b/gcd(a,b);
  }
};

int main(int argc, char const *argv[]) {
  Frac p(10,20);
  assert(p.n==1&&p.d==2);
  
  Frac x(5,6),y(3,4);
  auto a=x.add(y);
  assert(a.n==19&&a.d==12);
  
  auto s=x.sub(y);
  assert(s.n==1&&s.d==12);

  auto m=x.mul(y);
  assert(m.n==5&&m.d==8);

  auto d=x.div(y);
  assert(d.n==10&&d.d==9);
  
  int lg=x.comp(y);
  assert(lg==1);
  Frac x2(2,6),y2(1,3);
  int eq=x2.comp(y2);
  assert(eq==0);
  int sm=y.comp(x);
  assert(sm==-1);
}
