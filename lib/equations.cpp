#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

typedef long long LL;

/*
 
 Solver of system of modular linear equations,
 
  - compute (b,m) s.t. x≡b(mod m), A[i]*x≡B[i](mod M[i])
  - (0,-1) => no solution
  - from Ant book 4.1 complex math problems
  - https://en.wikipedia.org/wiki/Chinese_remainder_theorem
 
 Usage:
   auto p = MLE.solve(A,B,M);
 
 */
struct ModularLinearEquations {
public:
  ModularLinearEquations() {}
  
  pair<int, int> solve(const vector<int>& A, const vector<int>& B,
                       const vector<int>& M) {
    int x=0,m=1;
    for(int i=0; i<A.size(); i++) {
      int a=A[i]*m,b=B[i]-A[i]*x,d=gcd(M[i],a);
      if (b%d!=0) return make_pair(0,-1); // solution not found
      int t=b/d*modinv(a/d,M[i]/d)%(M[i]/d);
      x=x+m*t;
      m*=M[i]/d;
    }
    x=(x+m)%m; // ensure that x is non-negative
    return make_pair(x%m,m);
  }
  
  /*
   
   compute mod inverse of n, O(lg max(a,m)) time

    - compute x s.t. a*x≡1(mod m)
    - a and m should be co-prime (gcd(a,m)==1)
    - from Ant book 4.1 complex math problems
   
   a*x≡1(mod m)
   <=> ∃k, a*x=k*m+1
   <=> a*x-k*m=1 // x can be computed by extgcd(a,m)
   
   Usage:
     int d = modinv(5,11) // d=9
   
   */
  int modinv(int a, int m) {
    assert(gcd(a,m)==1);
    int x,y;
    extgcd(a, m, x, y);
    return (m+x%m)%m; // ensure mod inverse is non-negative
  }
  
  /*
   
   extended GCD, O(lg max(a,b)) time
   
    - compute (x,y,z) s.t. a*x+b*y=1, z=gcd(a,b)
    - from Ant book 2.6 elementary math techniques

   Usage:
     int x, y;
     int z = extgcd(899,493,x,y); // (x,y)=(29,-6), z=gcd(899,493)=11
   
   */
  int extgcd(int a, int b, int& x, int& y) {
    if(b==0) {
      x=1,y=0;
      return a;
    }
    int d=extgcd(b, a%b, y, x);
    y-=(a/b)*x;
    return d;
  }
private:
  int gcd(int a, int b) {
    return b==0?a:gcd(b,a%b);
  }
} MLE;

/*
 
 Compute rank by Gaussian elimination in GF(2), O(N^2*lg N) time
 
 GF(2)
   - CLRS "D-2 Permutations defined by matrix-vector multiplication over GF(2)" Problems for Appendix D
   - https://www.cs.umd.edu/~gasarch/TOPICS/factoring/fastgauss.pdf
   - http://personals.ac.upc.edu/enricm/Pubs/pdp2015_slides.pdf
     - great overview of Gaussian elimination in GF(2) ✅
 
 Usage:
   int rank = gf2_rank<int>(V);
 
 Note of GF(2)
 
 Gaussian Elimination is defined over an algebraic field
   - Infinite fields: 𝐐, 𝐑
   - Finite fields: Galoius field with 2 elements a.k.a. GF(2)
 
 In GF(2)={0,1}, algebraic operations are represented as below:
   - addition ≡ XOR ≡ subtraction (+1=-1)
   - multiplication ≡ AND
 
 Implementation remarks:
   - Gaussian elimination in infinite fields can be specialized for GF(2)
   - Gauss-Jordan Elimination can be easily merged into GE
   - Pivotting is unnecessary
   - computer arithmetic over GF(2) is always exact
 Applications
   - factoring large integer numbers, cryptography, pattern matching...
 
 Thus Gaussian elimination works in GF(2).
 We can just compute rank of GF(2) matrix.
 If we have linearly independent vectors X_a and X_b,
 Any X[i] can be represented as below:
 
 X[i] = (C_a & X_a) ^ (C_b & X_b), C_x ∈ {0,1}
 like... V[i] = C_a * V_a + C_b * V_b in infinite field
 
 Note that ^(XOR) and &(AND) are algebraic operation in GF(2).
 So we have same property as seen in linear algebra in infinite field.
 
 GE in GF(2) gives us linearly independent vectors.
 Expected result is number of those vectors (= rank of original matrix)
 
 We can do LU-decomposition in GF(2) by reducing MSB.
 
 */
template<class T> void gf2_GE(vector<T>& V) {
  // gaussian elimination in GF(2)
  int N=V.size();
  for(int i=0; i<N; ++i) {
    sort(V.begin()+i,V.end(),greater<T>());
    if(V[i]==0) break;
    T msb=1;
    while((msb<<1)<=V[i]) msb<<=1;
    for(int j=i+1; j<N; ++j) if(V[j]&msb) V[j]^=V[i];
  }
}
template<class T> int gf2_rank(vector<T>& V) {
  gf2_GE<T>(V);
  return (int)V.size()-count(V.begin(),V.end(),0);
}

int main(int argc, char const *argv[]) {
  vector<int> V = { 534, 251, 76, 468, 909, 410, 264, 387, 102, 982, 199, 111, 659, 386, 151 };
  assert(gf2_rank<int>(V)==10);
  
  vector<int> A={1,1,1};
  vector<int> B={2,3,2};
  vector<int> M={3,5,7};
  auto p = MLE.solve(A,B,M);
  assert(p.first==23);
  assert(p.second==105);
}
