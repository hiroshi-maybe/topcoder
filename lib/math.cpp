#include <cassert>
#include <tuple>
using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
int lcm(int a, int b) {
    return (a*b) / gcd(a,b);
}

// CLRS 31.2
// returns (gcd,x,y) s.t. gcd = a*x + b*y
tuple<int,int,int> gcd_extended(int a, int b) {
  if (b==0) return make_tuple(a, 1, 0);
  
  int d2,x2,y2;
  tie(d2,x2,y2) = gcd_extended(b, a%b);
  return make_tuple(d2,y2,x2-(a/b)*y2);
}

// CLRS 31.6
// compute (a^b) mod n
int mod_exp(int a, int b, int n) {
  assert(a>=0);
  assert(b>=0);
  assert(n>0);

  int d=1;
  for(int i=31; i>=0; --i) {
    d = (d*d)%n;
    if ((b&(1<<i))!=0) {
      d = (d*a)%n;
    }
  }
  return d;
}

// main

int main(int argc, char const *argv[]) {
  assert(gcd(899,493)==29);

  auto t = gcd_extended(899,493);
  assert(get<0>(t)==29);
  assert(get<1>(t)==-6);
  assert(get<2>(t)==11);

  int m = mod_exp(7,560,561);
  assert(m==1);
}
