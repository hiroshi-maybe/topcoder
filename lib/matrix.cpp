#include <iostream>
#include <cassert>
#include <vector>
#include <math.h>
using namespace std;

// debug cerr
#include <iterator>
#include <sstream>
template<class Iter> void __kumaerrc(Iter begin, Iter end) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; }
void __kumaerr(istream_iterator<string> it) { (void)it; cerr<<endl; }
template<typename T, typename... Args> void __kumaerr(istream_iterator<string> it, T a, Args... args) { cerr<<*it<<"="<<a<<", ",__kumaerr(++it, args...); }
template<typename S, typename T> std::ostream& operator<<(std::ostream& _os, const std::pair<S,T>& _p) { return _os<<"{"<<_p.first<<','<<_p.second<<"}"; }
#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

/*
 
 Matrix class
 
 Features:
  - addition
  - subtraction
  - multiplication
  - power
 
 Used problems:
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/LunarNewYearAndARecursiveSequence.cpp#L123
   - matrix power
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/MagicGems.cpp#L73
   - matrix power
 
 */
template <typename T> struct MX {
  int N,M;
  MX(int N, int M) : N(N), M(M) {
    assert(N>0&&M>0);
    dat=vector<vector<T>>(N, vector<T>(M, 0));
  }
  MX(vector<vector<T>> &d) : dat(d) {
    assert(dat.size()>0&&dat[0].size()>0);
    N=dat.size(),M=dat[0].size();
  }
  inline vector<T>& operator [] (int i) {return dat[i]; }
  MX<T> &operator+=(MX<T> that) { dat=add(dat,that.dat); return *this; }
  MX<T> &operator-=(MX<T> that) { that*=-1,dat=add(dat,that.dat); return *this; }
  MX<T> &operator*=(MX<T> that) { dat=mult(dat,that.dat); return *this; }
  MX<T> &operator*=(T k) { dat=mult(dat,k); return *this; }
  MX<T> operator + (const MX<T> &that) const { return MX<T>(*this)+=that; }
  MX<T> operator - (const MX<T> &that) const { return MX<T>(*this)-=that; }
  MX<T> operator * (const MX<T> &that) const { return MX<T>(*this)*=that; }
  MX<T> operator * (const T &k) const { return MX<T>(*this)*=k; }
  bool operator==(MX<T> that) const { return dat==that.dat; }
  bool operator!=(MX<T> that) const { return dat!=that.dat; }
  // res = A^n, O(N^3*lg n) time
  MX<T> pow (long long n) const {
    assert(N==M);
    MX<T> res(N,N); for(int i=0; i<N; ++i) res.dat[i][i]=1;
    MX<T> a=MX<T>(*this);
    while(n>0) {
      if(n%2) res*=a;
      a*=a,n>>=1;
    }
    return res;
  }
  friend ostream& operator<<(ostream& os, const MX<T>& that) {
    for(int i=0; i<that.N; ++i) for(int j=0; j<that.M; ++j) os<<that.dat[i][j]<<",\n"[j==that.M-1];
    return os;
  }
private:
  vector<vector<T>> dat;
  // O(N^2) time
  vector<vector<T>> add(vector<vector<T>> &A, vector<vector<T>> &B) {
    assert(A.size()==B.size()&&A[0].size()==B[0].size());
    int N=A.size(),M=A[0].size();
    vector<vector<T>> res=vector<vector<T>>(N,vector<T>(M));
    for(int i=0; i<N; ++i) for(int j=0; j<M; ++j) res[i][j]=A[i][j]+B[i][j];
    return res;
  }
  // O(N^3) time
  vector<vector<T>> mult(vector<vector<T>> &A, vector<vector<T>> &B) {
    assert(A[0].size()==B.size());
    int NN=A.size(),MM=B[0].size(),L=A[0].size();
    vector<vector<T>> res=vector<vector<T>>(NN,vector<T>(MM));
    for(int i=0; i<NN; ++i) for(int j=0; j<MM; ++j) for(int k=0; k<L; ++k) res[i][j]+=A[i][k]*B[k][j];
    return res;
  }
  vector<vector<T>> mult(vector<vector<T>> &A, T k) {
    int N=A.size(),M=A[0].size();
    vector<vector<T>> res=vector<vector<T>>(N,vector<T>(M));
    for(int i=0; i<N; ++i) for(int j=0; j<M; ++j) res[i][j]=k*A[i][j];
    return res;
  }
};

void test_mx() {
  {
    // addition
    vector<vector<int>> datA={{1,2},{3,4}},datB={{5,6},{7,8}},datAB={{6,8},{10,12}};
    MX<int> A(datA),B(datB);
    MX<int> C=A+B;
    assert(C==MX<int>(datAB));
  }
  
  {
    // subtraction
    vector<vector<int>> datA={{1,2},{3,4}},datB={{5,6},{7,8}},datAB={{-4,-4},{-4,-4}};
    MX<int> A(datA),B(datB);
    MX<int> C=A-B;
    assert(C==MX<int>(datAB));
  }
  
  {
    // multiplication (mx)
    vector<vector<int>> datA={{1,2},{3,4},{5,6}},datB={{1,2,3},{4,5,6}},datAB={{9,12,15},{19,26,33},{29,40,51}};
    MX<int> A(datA),B(datB);
    MX<int> C=A*B;
    assert(C==MX<int>(datAB));
  }
  
  {
    // multiplication (mx)
    vector<vector<int>> datA={{1,2},{3,4}},datKA={{2,4},{6,8}};
    MX<int> A(datA);
    A*=2;
    assert(A==MX<int>(datKA));
  }
  
  {
    // pow
    vector<vector<int>> datA={{1,2},{3,4}};
    MX<int> A(datA);
    MX<int> exp=A;
    exp=exp*exp*exp;
    assert(exp==A.pow(3));
  }
}

const int MOD=1000000007;
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

void test_modmx() {
  vector<vector<ModInt>> dat={{ModInt(10000),ModInt(20000)},{ModInt(30000),ModInt(40000)}},I={{ModInt(1),ModInt(0)},{ModInt(0),ModInt(1)}};
  MX<ModInt> A(dat),exp(I);
  int p=100;
  for(int i=0; i<p; ++i) exp*=A;
  assert(A.pow(100)==exp);
}

/*
 
 Compute rank by Gaussian elimination in GF(2), O(N^2*lg N) time
 
 GF(2)
  - CLRS "D-2 Permutations defined by matrix-vector multiplication over GF(2)" Problems for Appendix D
  - https://www.cs.umd.edu/~gasarch/TOPICS/factoring/fastgauss.pdf
  - http://personals.ac.upc.edu/enricm/Pubs/pdp2015_slides.pdf
   - great overview of Gaussian elimination in GF(2) ✅
  - https://en.wikipedia.org/wiki/Finite_field#Field_with_four_elements
 
 # Usage
 
 int rank = gf2_rank<int>(V);
 
 # Note of GF(2)
 
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
   - bitmask
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/ZeroXORSubsetLess.cpp#L110
   - bitmask
  - https://github.com/hiroshi-maybe/atcoder/blob/master/solutions/OddSubrectangles.cpp#L150
   - 2d vector
 
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
// gf2 in matrix representation
int gf2_rank(MX<int> mx) {
  int res=0;
  for(int j=0; j<mx.M; j++) {
    int pivot=-1;
    for(int i=res; i<mx.N; i++) if(mx[i][j]) {
      pivot=i;
      break;
    }
    if(pivot>=0) {
      if(pivot!=res) for(int k=0; k<mx.M; k++) swap(mx[pivot][k], mx[res][k]);
      for(int i=res+1; i<mx.N; i++) if(mx[i][j]) for(int k=0; k<mx.M; k++) mx[i][k]^=mx[res][k];
      res++;
    }
  }
  return res;
}

void test_gf2() {
  vector<int> V = { 534, 251, 76, 468, 909, 410, 264, 387, 102, 982, 199, 111, 659, 386, 151 };
  assert(gf2_rank<int>(V)==10);
  
  {
    vector<vector<int>> A={
      {1,0,1,1},
      {1,1,1,0},
      {0,1,0,1},
      {0,0,1,1}
    };
    MX<int> mx(A);
    assert(gf2_rank(mx)==3);
  }
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

void test_gje() {
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

int main(int argc, char const *argv[]) {
  test_mx();
  test_modmx();
  test_gf2();
  test_gje();
}

// g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address matrix.cpp && ./a.out
