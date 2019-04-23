#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

typedef long long LL;
constexpr int MOD = 1e9+7;

/*
 
 Power mod by repeated squaring, O(lg b)
 
 powmod(a,b) = (a^b) % MOD
 
 Reference:
  - CLRS 31.6 powers of an element
  - Ant boo 2-6 how to solve math problem
 
 */
LL powmod(LL a, LL b) {
  assert(0<=a);
  assert(0<=b);
  a%=MOD;
  
  LL res=1;
  for(LL mask=1; mask<=b; mask<<=1) {
    if(b&mask) res*=a, res%=MOD;
    a*=a; a%=MOD;
  }
  return res;
}

/*
 
 Compute modular multiplicative inverse, O(lg a)
 
 - compute a^-1 (mod p) p is prime AND p ⧷ a
 - proved by Fermat's little theorem
 
 Fermat's little theorem:
 
 a^p     ≡ a (mod p)       if p is prime
 a^(p-1) ≡ 1 (mod p)       if p is prime AND p ⧷ a
 a^-1    ≡ a^(p-2) (mod p) if p is prime AND p ⧷ a

 References:
  - https://en.wikipedia.org/wiki/Modular_multiplicative_inverse#Computation
  - https://en.wikipedia.org/wiki/Fermat%27s_little_theorem
 
 */
LL modinv(LL a, LL p=MOD) {
  return powmod(a, p-2);
}

/*
 
 factorial(n) % MOD, O(n)
 
 - lazily computed and cached
 - O(1) time if cached
 
 */
LL factmod(LL n) {
  static vector<LL> memo(1,1);
  if(memo.size()<=n) {
    LL l=memo.size();
    memo.resize(n+1);
    for(LL i=l; i<=n; ++i) memo[i]=memo[i-1]*i, memo[i]%=MOD;
  }
  return memo[n];
}

/*
 
 n chooses k (% MOD) (binomial coefficient), O(n)
 
 C(n,k) = n!/((n-k)!*k!)
 
  - compute on-demand by mod inverse and factorial mod
  - deprecated because it's not efficient for large n
   - use O(k) version
 
 */
LL choose_deprecated(LL n, LL k) {
  if (n<k) return 0;
  k = min(n-k,k);
  LL res=factmod(n);
  res *= modinv(factmod(n-k)), res%=MOD;
  res *= modinv(factmod(  k)), res%=MOD;
  
  return res;
}

/*
 
 n chooses k (% MOD) (binomial coefficient), O(k)
 
   C(n,k)
 = ∏ {(n-i): i=0..k } * 1/k!
 = ∏ {(n-i): i=0..k } * modinv(k!)
 
 - dependency to modinv() and factmod()
 - compute k! first and get its mod inverse
 
 */
LL choose_factmod(LL n, LL k) {
  if(n<k) return 0;
  k = min(n-k,k);
  LL res=modinv(factmod(k));
  for(int i=0; i<k; ++i) res*=(n-i)%MOD,res%=MOD;
  return res;
}

/*
 
 n chooses k (% MOD) (binomial coefficient), O(k) in cache warmup, O(1) per query on average
 
   C(n,k)
 = ∏ {(n-i): i=0..k } * 1/k!
 = ∏ {(n-i): i=0..k } * ∏ { modinv(i): i=1..k }
 
  - Pre-compute factorial of mod inverse of k (<=MAXK) first in O(k)
  - N<=1e7
 
 Mod inverse is pre-computed based on below formula:

     i*(MOD/i)+MOD%i = MOD
 <=> inv(i) ≡ (inv(MOD%a) * -(MOD/i)) (mod MOD)
 
 References:
  - https://www37.atwiki.jp/uwicoder/pages/2118.html
  - https://discuss.codechef.com/questions/3869/best-known-algos-for-calculating-ncr-m
  - https://comeoncodeon.wordpress.com/2011/10/09/modular-multiplicative-inverse/
   - compute mod multiplicative inverse in linear time used in this function
  - https://twitter.com/meguru_comp/status/694547019885449216
 
 Used problems:
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/NewYearAndThePermutationConcatenation.cpp#L144
  - https://github.com/hiroshi-maybe/atcoder/blob/master/solutions/Factorization.cpp#L121
 
 */
LL choose(LL n, LL k) {
  if(n<k) return 0;
  
  const int MAX_N = 1e6+1;
  assert(0<=k&&k<=MAX_N);
  static LL fact[MAX_N+1],revfact[MAX_N+1],rev[MAX_N+1];
  
  if(rev[1]==0) {
    rev[1]=1;
    for(int i=2;i<=MAX_N;i++) rev[i]=rev[MOD%i]*(MOD-MOD/i)%MOD;
    fact[0]=1,revfact[0]=1;
    for(int i=1;i<=MAX_N;i++) {
      fact[i]=fact[i-1]*i%MOD;
      revfact[i]=revfact[i-1]*rev[i]%MOD;
    }
  }
  return fact[n]*revfact[n-k]%MOD*revfact[k]%MOD;
}

/*
 
 Create n chooses k (% MOD) table (k=0..n), O(N^2) time (N<=3000)
 
 C(n,k) = C(n-1,k)+C(n-1,k-1)
 
 - Precompute n chooses k for n={1..N},k={1..N}
 - DP following Pascal's triangle
  - https://en.wikipedia.org/wiki/Pascal%27s_triangle
 
 */
void choose(LL N, vector<vector<int>> &C) {
  for(int i=0; i<=N; ++i) {
    C[i][0]=1;
    for(int j=1; j<=i; ++j) {
      // i chooses j
      C[i][j] = C[i-1][j]+C[i-1][j-1], C[i][j]%=MOD;
    }
  }
}

/*
 
 Multichoose k of n elements (% MOD), O(n+k) time

 H(n,k) = C(n+k-1,k) % MOD
 
 - Compute on-demand by binomial coefficient
 - Populate k slots by infinite n elements with repetion
 
 */
LL multichoose(LL n, LL k) {
  if(n==0&&k==0) return 1;
  return choose(n+k-1,k);
}

/*
 
 IEP (inclusion-exclusion principle) for union set when family of sets is homogeneous
 
 - O(N*T(f)) time to compute
 - O(N^2) to initialize combinatorics table
 
 Compute cardinality of union set A[0]∪A[1]∪..∪A[N] when cardinality of intersection of `k` sets can be computed by f(k) (family of sets is homogeneous)
 
   |∪ { A[i] : i=0..N-1 }|
 = ∑ { (-1)^|X| * |∩ { A[i] : i∈X }| : X ⊆ {0..N-1} } // IEP
 = ∑ { (-1)^|k+1| * C(N,k) * f(k) : k = 1..N }
     where f(k) = |∩ { A[i] : i∈X, X⊆{0..N-1}, |X|=k }|
 
 With homogeneous property, cardinality of intersection of C(N,k) families of sets is computed in the last step.
 
 References:
  - https://en.wikipedia.org/wiki/Inclusion%E2%80%93exclusion_principle#A_special_case
  - Ant book 4-1 complex math (basic form)
  - https://qiita.com/urutom/items/f192350c74394ae56e19
 
 Usage:
  // implement f(k)
  IEP iep(N);
  LL res=iep.solve();
 
 */
// segmentation fault if MAX_N>723
#define MAX_N 723
struct IEP {
public:
  IEP(int N, long long MOD=1000000007): N(N), MOD(MOD) {
    for(int i=0; i<=N; ++i) {
      C[i][0]=1;
      for(int j=1; j<=i; ++j) {
        C[i][j] = C[i-1][j]+C[i-1][j-1], C[i][j]%=MOD;
      }
    }
  }
  long long solve() {
    long long res=0;
    for(int k=1; k<=N; ++k) {
      long long sign=k%2==0?-1:1;
      long long x=sign;
      x*=C[N][k],x%=MOD;
      x*=f(k),x%=MOD;
      x+=MOD,x%=MOD;
      res+=x,res%=MOD;
    }
    return res;
  }
  
  // ⚠️ Implement this function
  // Compute f(k) = |∩ { A[i] : i∈X, X⊆{0..N-1}, |X|=k }|
  // Return size of intersection of `k` sets out of A[i], i=0..N-1
  long long f(int k) {
    // https://qiita.com/urutom/items/f192350c74394ae56e19
    // example to compute number of derangement
    // https://en.wikipedia.org/wiki/Derangement
    // https://oeis.org/A000166/list
    // f(k) = (N-k)!
    long long res=1;
    for(int n=1; n<=N-k; ++n) res*=n,res%=MOD;
    return res;
  }
private:
  int N;
  long long MOD;
  long long C[MAX_N][MAX_N];
};

/*
 
 IEP (inclusion-exclusion principle) in COMPLEMENTARY form when family of sets is homogeneous
 
 - O(N*T(f)) time to compute
 - O(N^2) to initialize combinatorics table
 
 https://en.wikipedia.org/wiki/Inclusion%E2%80%93exclusion_principle#Statement
 > In applications it is common to see the principle expressed in its complementary form.
 
 Compute cardinality of intersection set Ā[0]∩Ā[1]∩..∩Ā[N] when family of sets is homogeneous.
 
   |∩ { Ā[i] : i=1..N }|
 = |Ū { A[i] : i=0..N-1 }|                            // De Morgan's laws
 = |U| - |∪ { A[i] : i=0..N-1 }|                      // U is universal set
 = ∑ { (-1)^|X| * |∩ { A[i] : i∈X }| : X ⊆ {0..N-1} } // IEP
 = ∑ { (-1)^|k| * C(N,k) * f(k) : k = 0..N }
     where f(k) = |∩ { A[i] : i∈X, X⊆{0..N-1}, |X|=k }|
 
 Note that universal set corresponds to k=0 case.
 Also parity of exponent of `-1` is different.
 
 References:
 - https://en.wikipedia.org/wiki/Inclusion%E2%80%93exclusion_principle#A_special_case
 - https://yukicoder.me/wiki/algorithm_summary
 - https://qiita.com/urutom/items/f192350c74394ae56e19
 
 Used problems:
  - https://github.com/k-ori/topcoder/blob/master/NoRepeatPlaylist/NoRepeatPlaylist.cpp#L152
 
 Usage:
  // implement f(k)
  IEP_comp iep(N);
  LL res=iep.solve();
 
 */
struct IEP_comp {
public:
  IEP_comp(int N, long long MOD=1000000007): N(N), MOD(MOD) {
    for(int i=0; i<=N; ++i) {
      C[i][0]=1;
      for(int j=1; j<=i; ++j) {
        C[i][j] = C[i-1][j]+C[i-1][j-1], C[i][j]%=MOD;
      }
    }
  }
  long long solve() {
    long long res=0;
    for(int k=0; k<=N; ++k) {
      long long sign=k%2==0?1:-1;
      long long x=sign;
      x*=C[N][k],x%=MOD;
      x*=f(k),x%=MOD;
      x+=MOD,x%=MOD;
      res+=x,res%=MOD;
    }
    return res;
  }
  
  // ⚠️ Implement this function
  // Compute f(k) = |∩ { A[i] : i∈X, X⊆{0..N-1}, |X|=k }|
  // Return size of intersection of `k` sets out of A[i], i=0..N-1
  long long f(int k) {
    // https://qiita.com/urutom/items/f192350c74394ae56e19
    // example to compute number of derangement
    // https://en.wikipedia.org/wiki/Derangement
    // https://oeis.org/A000166/list
    // f(k) = (N-k)!
    long long res=1;
    for(int n=1; n<=N-k; ++n) res*=n,res%=MOD;
    return res;
  }
private:
  int N;
  long long MOD;
  long long C[MAX_N][MAX_N];
};

/*
 
 Twelvefold way
 
 References:
  - https://en.wikipedia.org/wiki/Twelvefold_way
  - https://mathtrain.jp/twelveway
  - http://kuno4n.hateblo.jp/entry/2013/12/14/140104#count8
 
 Counting of how N balls are mapped to K boxes.
 Depending on permutation of balls/boxes and number of balls in a box (at most 1 or at least 1),
 there are twelve cases as shown below:
 
 d10able = "distinguishable", A[i] = number of balls in a box
 
 n balls     | k boxes     || any       | A[i]<=1 | A[i]>=1
 ========================================================================================
 d10able     | d10able     || k^n       | P(k,n)  | ∑ { (-1)^(k-i)*C(k,i)*i^n : i=1..k }
 NOT d10able | d10able     || H(k,n)    | C(k,n)  | H(k-n,n)
 d10able     | NOT d10able || Bell(n,k) | 1       | Stirling(n,k)
 NOT d10able | NOT d10able || Part(n,k) | 1       | Part(n-k,k)
 
 */

/*
 
 Query stirling number in O(n^2) time by dp
 
 References:
  - https://mathtrain.jp/stnum
  - http://drken1215.hatenablog.com/entry/2018/02/01/200628
  - https://mathtrain.jp/zensya
  - https://en.wikipedia.org/wiki/Stirling_numbers_of_the_second_kind
  - https://oeis.org/A008277
 
 Usage:
  Stirling S;
  cout<<S.query(n,k)<<endl;
 
 */
//#define MAX_N 300
struct Stirling {
public:
  long long memo[MAX_N][MAX_N];
  Stirling() {
    memset(memo, -1, sizeof memo);
  }
  long long query(int n, int k) {
    assert(n<MAX_N&&k<MAX_N);
    assert(n>=k);
    return f(n,k);
  }
private:
  long long f(int n, int k) {
    if(n==k) return 1;
    if(k<=0) return 0;
    if(k==1) return 1;
    long long &res=memo[n][k];
    if(res>=0) return res;
    
    long long a=f(n-1,k-1),b=f(n-1,k)*k%MOD;
    return res=(a+b)%MOD;
  }
} Stir;

void test_stirlingNumber() {
  vector<vector<long long>> exp={
    /*0*/  {1},
    /*1*/  {0,  1},
    /*2*/  {0,  1,  1},
    /*3*/  {0,  1,  3,  1},
    /*4*/  {0,  1,  7,  6,  1},
    /*5*/  {0,  1,  15,  25,  10,  1},
    /*6*/  {0,  1,  31,  90,  65,  15,  1},
    /*7*/  {0,  1,  63,  301,  350,  140,  21,  1},
    /*8*/  {0,  1,  127,  966,  1701,  1050,  266,  28,  1},
    /*9*/  {0,  1,  255,  3025,  7770,  6951,  2646,  462,  36,  1},
    /*10*/ {0,  1,  511,  9330,  34105,  42525,  22827,  5880,  750,  45,  1}
  };
  
  for(int n=0; n<=10; ++n) for(int k=0; k<=n; ++k) {
    assert(exp[n][k]==Stir.query(n,k));
  }
}

/*
 
 Query partition number in O(n^2) time by dp
 
 References:
  - http://drken1215.hatenablog.com/entry/2018/01/16/222843
  - https://mathtrain.jp/zensya
  - http://d.hatena.ne.jp/incognita/20110305/1299344781
  - https://oeis.org/A000041
  - https://ja.wikipedia.org/wiki/%E5%88%86%E5%89%B2%E6%95%B0
  - https://en.wikipedia.org/wiki/Partition_(number_theory)#Restricted_part_size_or_number_of_parts
 
 Parition number for P(N,N)
 
 1   :                                1
 10  :                               42
 50  :                           204226 (≈2e5)
 100 :                        190569292 (≈2e5)
 200 :                    3972999029388 (≈4e12)
 300 :                 9253082936723602 (≈1e16)
 400 :              6727090051741041926 (≈6e18)
 500 :           2300165032574323995027 (≈2e21)
 1000: 24061467864032622473692149727991 (≈2e31)
 
 Usage:
  Part P;
  cout<<P.query(n,k)<<endl;
 
 */

//#define MAX_N 300
struct Partition {
public:
  long long memo[MAX_N][MAX_N];
  Partition() {
    memset(memo, -1, sizeof memo);
  }
  long long query(int n, int k) {
    assert(n<MAX_N&&k<MAX_N);
    return f(n,k);
  }
private:
  long long f(int n, int k) {
    if(n<0) return 0;
    if(k==0) return n==0;
    if(n==0) return 1;
    
    long long &res=memo[n][k];
    if(res>=0) return res;
    
    long long a=f(n-k,k),b=f(n,k-1);
    return res=(a+b)%MOD;
  }
} Part;

void test_partitionNumber() {
  vector<vector<long long>> exp = {
    /*0*/  {1},
    /*1*/  {0,  1},
    /*2*/  {0,  1,  2},
    /*3*/  {0,  1,  2,  3},
    /*4*/  {0,  1,  3,  4,  5},
    /*5*/  {0,  1,  3,  5,  6,  7},
    /*6*/  {0,  1,  4,  7,  9,  10, 11},
    /*7*/  {0,  1,  4,  8,  11, 13, 14, 15},
    /*8*/  {0,  1,  5,  10, 15, 18, 20, 21, 22},
    /*9*/  {0,  1,  5,  12, 18, 23, 26, 28, 29, 30},
    /*10*/  {0, 1,  6,  14, 23, 30, 35, 38, 40, 41, 42}
  };

  /*
  int dp[1005][1005]={};
  dp[0][0] = 1;
  for(int i=1; i<1005; ++i) {
    for(int j=0; j<1005; ++j) {
      if(j-i >= 0) {
        dp[i][j] = (dp[i-1][j] + dp[i][j-i]) % MOD;
      } else {
        dp[i][j] = dp[i-1][j];
      }
    }
  }
  for(int n=0; n<=10; ++n) {
    for(int k=0; k<=n; ++k) cout<<dp[k][n]<<" ";
    cout<<endl;
  }*/
  
  for(int x=1; x<=1e3; x*=10) {
//    cout<<x<<":"<<Part.query(x,x);
  }
  
  for(int n=0; n<=10; ++n) for(int k=0; k<=n; ++k) {
    assert(exp[n][k]==Part.query(n,k));
  }
}

// main

int main(int argc, char const *argv[]) {
  int m2 = powmod(7,560);
  assert(m2==108725231);
  
  LL m = 560;
  LL mi = modinv(m);
  assert((m*mi)%MOD==1);
  
  assert(factmod(560)==597965522);
  assert(choose(771,50)==275127687);
  assert(multichoose(771,50)==954694855);
  
  vector<vector<int>> dp(201,vector<int>(201,0));
  choose(200,dp);
  assert(dp[200][23]==choose(200,23));
  
  int N=20;
  long long dear20 = 895014631192902121LL%MOD;
  long long factN=1;
  for(int n=1; n<=N; ++n) factN*=n,factN%=MOD;
  IEP ie(N);
  long long dearrangement1=(factN-ie.solve()+MOD)%MOD;
  assert(dearrangement1==dear20);
  IEP_comp ie2(N);
  assert(ie2.solve()==dear20);
  
  test_stirlingNumber();
  test_partitionNumber();
}
