#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }
LL lcm(LL a, LL b) { return a/gcd(a,b)*b; }

void test_gcd() {
  assert(gcd(899,493)==29);
  assert(gcd(15646365345434LL,64364363463464LL)==2);
  assert(lcm(943349532LL,156464LL)==36900060293712LL);
}

/*

 The extended form of Euclid’s algorithm, O(lg max(a,b)) time

 computes (gcd,x,y) s.t. g=gcd(a,b)=a*x+b*y

   - From CLRS 31.2 Greatest common divisor
   - If gcd(a,b)=1, x=a^-1(mod b) (mod inverse of a in mod b) because a*x≡1(mod b)
     - this is useful to solve modular equation a*x≡b(mod m)
     - see CLRS 31.4 and `lib/equations.cpp`

 Proof:

 (gg,xx,yy) = gcde(a,b)

   g = gg
   = b*xx+(a%B)*yy
   = b*xx+(a-b*floor(a/b))*yy
   = a*yy + b*(xx-floor(a/b)*yy)
       ^      ^
 Thus return (g,yy,xx-floor(a/b)*yy)

 Usage:

   int g,x,y;
   tie (g,x,y) = extended_euclid(899,493);
   // (g,x,y)=(29,-6,11) s.t. 29 = -6*899 + 11*493

 Used problems:
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/InfiniteFence.cpp#L64
  - https://github.com/hiroshi-maybe/atcoder/blob/4800c7aa222aee403acd9b0012ee94e203116461/solutions/Oversleeping.cpp#L123

 */

template<typename integer>
tuple<integer,integer,integer> extended_euclid(integer a, integer b) {
  if (b==0) return make_tuple(a, 1, 0);

  integer d2,x2,y2;
  tie(d2,x2,y2) = extended_euclid(b, a%b);
  return make_tuple(d2,y2,x2-(a/b)*y2);
}

/*

  Solver of two equations for Chinese Remainder Theorem, O(lg max(n1,n2)) time

  Constructs (x, M) s.t. x ≡ a1 (mod n1), x ≡ a2 (mod n2)

  Returns (0,-1) if no solutions are found
  ( e.g. a1 (mod gcd(n1,n2)) !≡ a2 (mod gcd(n1,n2)) )

  https://qiita.com/drken/items/ae02240cd1f8edfc86fd

  Use https://github.com/hiroshi-maybe/topcoder/blob/master/lib/equations.cpp#L73 for more than two equations.

  Used problems:
   - https://github.com/hiroshi-maybe/atcoder/blob/4800c7aa222aee403acd9b0012ee94e203116461/solutions/Oversleeping.cpp#L132

 */
template<typename integer>
pair<integer,integer> crt2(integer a1, integer n1, integer a2, integer n2) {
  integer g,x,y; tie(g,x,y)=extended_euclid(n1,n2);
  if(a1%g!=a2%g) return {0,-1};
  integer lcm=n1/g*n2;

  integer res=a1+(a2-a1)/g*x%(n2/g)*n1;
  res=(res%lcm+lcm)%lcm;

  return {res,lcm};
}

void test_extendedeuclid() {
  auto t = extended_euclid(899,493);
  assert(get<0>(t)==29);
  assert(get<1>(t)==-6);
  assert(get<2>(t)==11);
}

void test_crt2() {
  {
    int a1=2, n1=3, a2=3, n2=5;
    auto [x,g]=crt2(a1,n1,a2,n2);
    assert(x==8);
    assert(g==1);
  }

  {
    LL a1=2698054, n1=7949779, a2=5550023, n2=7970645;
    auto [x,g]=crt2(a1,n1,a2,n2);
    assert(x==35027849890893);
    assert(g==1);
  }

  {
    LL a1=1350427, n1=4250955, a2=3475255, n2=4164018;
    auto [x,g]=crt2(a1,n1,a2,n2);
    assert(x==4992365411977);
    assert(g==3);
  }

  {
    LL a1=4, n1=6, a2=8, n2=15;
    auto [x,g]=crt2(a1,n1,a2,n2);
    assert(x==0);
    assert(g==-1);
  }
}

int main(int argc, char const *argv[]) {
  test_gcd();
  test_extendedeuclid();
  test_crt2();
}

//$ g++ -std=c++17 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address gcd.cpp && ./a.out
