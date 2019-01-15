#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <numeric>
#include <math.h>
using namespace std;

typedef long long LL;

/*
 
 Solver of system of modular linear equations,
 
  - compute (b,m) s.t. x≡b(mod m), ∀i A[i]*x ≡ B[i] (mod M[i])
  - (0,-1) => no solution (∃i s.t. gcd(A[i],M[i]) ⧷ B[i])
   - There is a solution of a*x≡b(mod m) only when gcd(a,m) divides b
  - Implementtion coming from Ant book 4.1 complex math problems
 
 Proof of correctness:
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
 
 Usage:
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

/*
 
 Compute rank by Gaussian elimination in GF(2), O(N^2*lg N) time
 
 GF(2)
   - CLRS "D-2 Permutations defined by matrix-vector multiplication over GF(2)" Problems for Appendix D
   - https://www.cs.umd.edu/~gasarch/TOPICS/factoring/fastgauss.pdf
   - http://personals.ac.upc.edu/enricm/Pubs/pdp2015_slides.pdf
     - great overview of Gaussian elimination in GF(2) ✅
   - https://en.wikipedia.org/wiki/Finite_field#Field_with_four_elements
 
 Usage:
   int rank = gf2_rank<int>(V);
 
 Note of GF(2)
 
 Gaussian Elimination is defined over an algebraic field
   - Infinite fields: 𝐐, 𝐑
   - Finite fields: Galois field with 2 elements a.k.a. GF(2)
 
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
 
 Used problems:
  - https://github.com/hiroshi-maybe/topcoder/blob/bc4fd010dc1100360b7462bf38a190426084490c/solutions/MixingColors/MixingColors.cpp#L123
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/ZeroXORSubsetLess.cpp#L110
 
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

/*
 
 Solver of system of linear equations by Gauss–Jordan elimination, Θ(N^3) time
 
 - implementation from Ant book
 
 Basic steps:
 1. Setup matrices A*x=b where A=NxN, b=Nx1
 2. By row reduction, transform A to echelon form (triangular form) which is U matrix in LU-composition
 3. Compute x by back-substitution
 
 References:
  - https://en.wikipedia.org/wiki/Gaussian_elimination
  - https://en.wikipedia.org/wiki/LU_decomposition
  - https://en.wikipedia.org/wiki/Triangular_matrix#Forward_and_back_substitution
  - Ant book 4.1 more complex math problems
  - CLRS 28.1 Solving systems of linear equations
  - http://kmjp.hatenablog.jp/entry/2014/04/01/0930
 
 */
struct GaussJordanElimination {
  const double eps=1e-8;
  vector<double> solve(vector<vector<double>> A, vector<double> b) {
    const int N=A.size();
    vector<vector<double>> X(N, vector<double>(N+1)); // Augmented matrix which merges A with b
    for(int i=0; i<N; ++i) {
      for(int j=0; j<N; ++j) X[i][j] = A[i][j];
      X[i][N] = b[i];
    }
    
    for(int i=0; i<N; ++i) {
      // invariant: X[p][p]=1 for p=0..i-1
      int pivot=i;
      for(int j=i; j<N; ++j) {
        // find maximum coefficient to minimize precision error
        if (fabs(X[j][i])>fabs(X[pivot][i])) pivot=j;
      }
      swap(X[i], X[pivot]);
      // solution is undeterministic, or no solution exists
      if (fabs(X[i][i])<eps) return vector<double>();
      
      // X[i][i]=1
      for(int j=i+1; j<=N; ++j) X[i][j]/=X[i][i];
      for(int j=0; j<N; ++j) if (i != j) {
        // row reduction
        for(int k=i+1; k<=N; ++k) X[j][k]-=X[j][i]*X[i][k];
      }
    }
    
    vector<double> xs(N);
    for(int i=0; i<N; ++i) xs[i]=X[i][N];
    return xs;
  }
} GJE;

int main(int argc, char const *argv[]) {
  vector<int> V = { 534, 251, 76, 468, 909, 410, 264, 387, 102, 982, 199, 111, 659, 386, 151 };
  assert(gf2_rank<int>(V)==10);
  
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
  
  // test case from https://en.wikipedia.org/wiki/Gaussian_elimination
  auto xs = GJE.solve({
    {2,1,-1},
    {-3,-1,2},
    {-2,1,2}
  },{
    8,-11,-3
  });
  vector<double> sols={2.0,3.0,-1.0};
  assert(sols.size()==xs.size());
  for(int i=0; i<sols.size(); ++i) {
    assert(fabs(xs[i]-sols[i])<1e-9);
  }
}
