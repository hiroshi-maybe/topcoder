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
 
 */

struct Frac {
public:
  // numerator / denominator
  int n,d;
  Frac(int nn, int dd) {
    assert(dd>0);
    bool neg=nn<0;
    nn=neg?-nn:nn;
    long long g=gcd(nn,dd);
    this->n=nn/g;
    if(neg) this->n=-1*this->n;
    this->d=dd/g;
  }
  Frac abs() {
    Frac res(n<0?-n:n,d);
    return res;
  }
  void debug() {
    printf("%d/%d\n",n,d);
  }
private:
  long long gcd(long long a, long long b) {
    return b==0?a:gcd(b,a%b);
  }
};
Frac operator + (Frac a, Frac b) { return Frac((long long)a.n * b.d + (long long)b.n * a.d, (long long)a.d * b.d); }
Frac operator - (Frac a, Frac b) { return a + Frac(-b.n, b.d); }
Frac operator * (Frac a, Frac b) { return Frac((long long)a.n * b.n, (long long)a.d * b.d); }
Frac operator / (Frac a, Frac b) { return a * Frac(b.d, b.n); }
bool operator < (Frac a, Frac b) { return a.n *(long long) b.d < b.n *(long long) a.d; }
bool operator > (Frac a, Frac b) { return b < a; }
bool operator == (Frac a, Frac b) { return a.n == b.n && a.d == b.d; }

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
