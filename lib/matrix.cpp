#include <iostream>
#include <cassert>

using namespace std;

typedef long long LL;

const int MX=105;
LL A[MX][MX];
LL S[MX][MX];
int N;

// power matrix O(N^3*lg n)
// S = S*A^n (S=A=nxn matrix)
//
// prequisite: S and A are initialized
void powerMat(LL n, int N) {
  assert(n>=0);
  
  LL X[105][105];
  LL tmp[105][105];
  memset(X,0,sizeof(X));
  for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) X[i][j]=A[i][j];
  
  while(n) {
    // invariant: X = A^(2^i)
    memset(tmp,0,sizeof(tmp));
    if (n&1) {
      for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j)
          for(int k=0; k<N; ++k) tmp[i][j] += S[i][k]*X[k][j];
      }
      for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) S[i][j]=tmp[i][j];
    }
    memset(tmp,0,sizeof(tmp));
    for(int i=0; i<N; ++i) {
      for(int j=0; j<N; ++j)
        for(int k=0; k<N; ++k) tmp[i][j] += X[i][k]*X[k][j];
    }
    for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) X[i][j]=tmp[i][j];
    
    n>>=1;
  }
}

/***********************   test code below   ***********************/

int main(int argc, char const *argv[]) {
  memset(S,0,sizeof(S));
  memset(A,0,sizeof(A));

  S[0][0]=1; S[0][1]=2;
  S[1][0]=3; S[1][1]=4;
  
  A[0][0]=-13; A[0][1]=-10;
  A[1][0]=21; A[1][1]=16;
  
  powerMat(3,2);
  
  assert(S[0][0]==197);
  assert(S[0][1]==142);
  assert(S[1][0]==297);
  assert(S[1][1]==214);
}
