#include <iostream>
#include <cassert>
#include <vector>
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
  vector<vector<T>> dat;
  MX(int N, int M) : N(N), M(M) {
    assert(N>0&&M>0);
    dat=vector<vector<T>>(N, vector<T>(M, 0));
  }
  MX(vector<vector<T>> &d) : dat(d) {
    assert(dat.size()>0&&dat[0].size()>0);
    N=dat.size(),M=dat[0].size();
  }
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
  void debug() {
    cerr<<N<<"x"<<M<<endl;
    for(int i=0; i<N; ++i) for(int j=0; j<M; ++j) cerr<<dat[i][j]<<",\n"[j==M-1];
  }
private:
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
    assert(C.dat==datAB);
  }
  
  {
    // subtraction
    vector<vector<int>> datA={{1,2},{3,4}},datB={{5,6},{7,8}},datAB={{-4,-4},{-4,-4}};
    MX<int> A(datA),B(datB);
    MX<int> C=A-B;
    assert(C.dat==datAB);
  }
  
  {
    // multiplication (mx)
    vector<vector<int>> datA={{1,2},{3,4},{5,6}},datB={{1,2,3},{4,5,6}},datAB={{9,12,15},{19,26,33},{29,40,51}};
    MX<int> A(datA),B(datB);
    MX<int> C=A*B;
    assert(C.dat==datAB);
  }
  
  {
    // multiplication (mx)
    vector<vector<int>> datA={{1,2},{3,4}},datKA={{2,4},{6,8}};
    MX<int> A(datA);
    A*=2;
    assert(A.dat==datKA);
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

/***********************   test code below   ***********************/

int main(int argc, char const *argv[]) {
  test_mx();
  test_modmx();
}

// g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address matrix.cpp && ./a.out
