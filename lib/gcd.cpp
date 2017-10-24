#include <iostream>
#include <cassert>
#include <tuple>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;

LL gcd(LL a, LL b) {
  return b == 0 ? a : gcd(b, a % b);
}
LL lcm(LL a, LL b) {
  return (a*b) / gcd(a,b);
}

/*
 
 The extended form of Euclid’s algorithm
 
 computes (gcd,x,y) s.t. d=gcd(a,b)=a*x+b*y, O(lg max(a,b)) time
 
   - From CLRS 31.2 Greatest common divisor
   - If gcd(a,b)=1, x=a^-1(mod b) (mod inverse of a in mod b) because a*x≡1(mod b)
     - this is useful to solve modular equation a*x≡b(mod m)
     - see CLRS 31.4 and `lib/equations.cpp`
 
 Proof:
 
 (dd,xx,yy) = gcde(a,b)
 
   d = dd
   = b*xx+(a%B)*yy
   = b*xx+(a-b*floor(a/b))*yy
   = a*yy + b*(xx-floor(a/b)*yy)
       ^      ^
 Thus return (d,yy,xx-floor(a/b)*yy)
 
 Usage:

   int d,x,y;
   auto t = extended_euclid(899,493);
   tie(d,x,y) = t; // (d,x,y)=(29,-6,11)
 
 */
tuple<int,int,int> extended_euclid(int a, int b) {
  if (b==0) return make_tuple(a, 1, 0);
  
  int d2,x2,y2;
  tie(d2,x2,y2) = extended_euclid(b, a%b);
  return make_tuple(d2,y2,x2-(a/b)*y2);
}

// main

int main(int argc, char const *argv[]) {
  assert(gcd(899,493)==29);
  
  auto t = extended_euclid(899,493);
  assert(get<0>(t)==29);
  assert(get<1>(t)==-6);
  assert(get<2>(t)==11);
}
