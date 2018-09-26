#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

/*
 
 build string match automaton, O(|P|^3*|∑|) time

 input: P (|P|<=1024)
 output: SMT
 
 build string match transition table `SMT[][]` for character set ∑={'a'-'z'} in CLRS 32.3
 SMT[i][j] = length (or next matching index) of longest prefix of P for suffix of P[0..i]+('a'+j)
 SMT[i][j] = max { k : P[0..<k] ⊐ P[0..i]+('a'+j) }
 
 Used problems:
  - https://github.com/k-ori/topcoder/blob/master/LinenCenterEasy/LinenCenterEasy.cpp
  - https://github.com/k-ori/topcoder/blob/master/FoxAndMountain/FoxAndMountain.cpp
 
 */
int SMT[1024][26];
void buildSMT(string P) {
  memset(SMT, 0, sizeof SMT);
  int L=P.size();
  for(int i=0; i<=L; ++i) {
    for(int j=0; j<26; ++j) {
      char c = 'a'+j;
      if (i<L&&c==P[i]) {
        // matched
        SMT[i][j]=i+1;
      } else {
        // unmatched
        string suf = P.substr(0,i)+c;
        int SL=(int)suf.size();
        // find longest prefix P[0..<k]
        for(int k=1; k<=i; ++k) if(P.substr(0,k)==suf.substr(SL-k)) SMT[i][j]=k;
      }
    }
  }
}

/*
 
 Build prefix function for KMP string matching, Θ(|P|) time
 
 input: P
 output: 𝞹[|P|]
 
 Build prefix function 𝞹 `pi` of pattern string P for KMP string matching
 Implementation of COMPUTE-PREFIX-FUNCTION(P) in CLRS 32.4
 Note that this 𝞹 is slightly different from `computeLongestPrefixSuffix()` due to 0-based array index.
 
 𝝅[q] = next matching index of P when P[q] unmatched
 𝝅[q] = max { k : k<=q AND P[0..<k] ⊐ P[0..<q] }
                   ^ k<q in `computeLongestPrefixSuffix()`
 
 Example:
 
 S  = aabaabaaa
 pi = _010123452
 
 References:
  - COMPUTE-PREFIX-FUNCTION(P) in CLRS 32.4
  - http://snuke.hatenablog.com/entry/2014/12/01/235807
  - http://potetisensei.hatenablog.com/entry/2017/07/10/174908
  - http://www-igm.univ-mlv.fr/~lecroq/string/node8.html
 
 Used problems:
  - https://github.com/k-ori/topcoder/blob/master/FoxAndMountain/FoxAndMountain.cpp
 
 */
vector<int> buildPrefixFunction(const string S) {
  int L=S.size();
  vector<int> pi(L+1,-1);
  int j=-1;
  for(int i=0; i<L; ++i) {
    while(j>=0&&S[i]!=S[j]) j=pi[j];
    pi[i+1]=++j;
  }
  return pi;
}

/*
 
 Find minimum cycle in substring S[0..i], O(N) time
 
 T = A+A+A+A', |T|=L, |A|=x, A': prefix of A

 A+A+A+A'
   A+A+A+A' (x-slide)
 _         : x
   _____   : L-x
   _______ : L
 
     Length of min cycle = x
 <=> {L-x}-suffix = {L-x}-prefix (S[1..L-x] = S[x+1..L])
 <=> x = L - MP[L] where MP[L]: longest prefix suffix of S[1..L] computed by MP algorithm
 
 Example:

 abababcaa
 122222778
 
 References:
  - http://snuke.hatenablog.com/entry/2015/04/05/184819
  - https://github.com/k-ori/topcoder/blob/master/MagicWords/MagicWords.cpp#L65
 
 */
vector<int> findMinCycles(const string S) {
  vector<int> mp=buildPrefixFunction(S);
  int N=S.size();
  vector<int> res(N);
  for(int i=0; i<N; ++i) res[i]=i+1-mp[i+1];
  return res;
}
void test_mincycles() {
  string S="abababcaa";
  vector<int> exp={1,2,2,2,2,2,7,7,8};
  vector<int> res=findMinCycles(S);
  int N=exp.size();
  for(int i=0; i<N; ++i) assert(exp[i]==res[i]);
}

/*
 
 Compute length of longest prefix of S for suffix of S[0..q], Θ(|S|) time
 
 input: S
 output: 𝝅[|S|]
 
 𝝅[q] = max { k : k<q AND S[0..<k] ⊐ S[0..q] }
                   ^ k<=q in `buildPrefixFunction()`
 
 */
vector<int> computeLongestPrefixSuffix(const string P) {
  int L = P.size();
  vector<int> pi(L, 0);
  
  if (L==0) return pi;
  int j=0;
  for(int i=1; i<L; ++i) {
    if (P[i]==P[j]) {
      // matched
      pi[i] = pi[i-1]+1;
      j++;
    } else {
      // unmatched
      j = pi[i-1];
      while(j>0 && P[i]!=P[j]) {
        j = pi[j-1];
      }
      if (P[i]==P[j]) j++;
      pi[i] = j;
    }
  }
  
  return pi;
}

/*
 
 KMP string matching algorithm, amortized Θ(M+N) time
 
 Returns index of T where P begins.
 
 References:
  - CLRS 32.4 The Knuth-Morris-Pratt algorithm
  - http://snuke.hatenablog.com/entry/2017/07/18/101026
  - http://potetisensei.hatenablog.com/entry/2017/07/10/174908
  - http://www-igm.univ-mlv.fr/~lecroq/string/node8.html
 
 */
int doKMP(string s, string p) {
  int i = 0, j = 0, L = s.size(), M = p.size();
  
  vector<int> pi = buildPrefixFunction(p);
  while (i<L) {
    if (s[i]==p[j]) {
      i++; j++;
      if (j==M) return i-M;
    } else if (j > 0) {
      j = pi[j];
    } else {
      i++;
    }
  }
  
  return -1;
}

// Rabbin Karp algorithm by rolling hash, O(M+N) time
//
// Note that this implementation uses implicit `int` representation of `char`.
//
// Usage:
//    RollingHash rh("abcabc",131,qe9+7);
//    int idx = rh.doRabbinKarpMatch("ca");
template<class T> struct RollingHash {
public:
  int M;
  string P;
  T d; // radix
  T MOD; // MOD
  T h; // d^(M-1) % MOD, helper to adjust rolling hash
  T p; // hash code of P
  RollingHash(string P, T d=131, T MOD=1e9+7): M(P.size()), P(P), d(d), MOD(MOD) {
    this->h=powmod(d,M-1,MOD);
    this->p=calcRollingHash(P);
  }
  
  // Rolling hash x for X[i..<M]
  // x=d^(M-1)*X[i]+d^(M-2)*X[i+1]+..+d^0*X[i+M-1]
  T calcRollingHash(string X) {
    T res=0;
    for(int i=0; i<min((int)X.size(), M); ++i) {
      res=(d*res)%MOD+X[i],res%=MOD;
    }
    return res;
  }
  // incremental update of hash code
  T updateRollingHash(T base, string S, int i) {
    T res=d*(base+MOD-((T)S[i]*h)%MOD)%MOD+S[i+M];
    res%=MOD;
    return res;
  }
  
  int doRabbinKarpMatch(string S) {
    int N=S.size();
    
    // preprocessing
    T s=calcRollingHash(S);
    
    for(int i=0; i<N-M; ++i) {
      if(s==p && S.substr(i,M)==P) return i;
      // incremental update of hash code
      // s=d(t-S[i]h)+S[i+M]
      s=updateRollingHash(s,S,i);
    }
    return -1;
  }
private:
  T powmod(T a, T b, T MOD) {
    T res=1;
    for(T mask=1; mask<=b; mask<<=1) {
      if(b&mask) res*=a, res%=MOD;
      a*=a; a%=MOD;
    }
    return res;
  }
};

int main(int argc, char const *argv[]) {
  // CLRS Ex 32.4-1
  string P1="ababbabbabbababbabb";
  auto pi1_a = computeLongestPrefixSuffix(P1);
  vector<int> pi1_e = { 0,0,1,2,0,1,2,0,1,2,0,1,2,3,4,5,6,7,8 };
  for(int i=0; i<pi1_e.size(); ++i) {
    assert(pi1_a[i]==pi1_e[i]);
  }
  auto pi2_a = buildPrefixFunction(P1);
  vector<int> pi2_e = { -1,0,0,1,2,0,1,2,0,1,2,0,1,2,3,4,5,6,7,8 };
  for(int i=0; i<pi2_e.size(); ++i) {
    assert(pi2_a[i]==pi2_e[i]);
  }
  
  // CLRS Figure 32.7
  string P = "ababaca";
  int idx = doKMP("abababacaba", P);
  assert(idx==2);
  
  // CLRS Figure 32.7
  buildSMT(P);
  vector<vector<int>> expected = {
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,4,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  };
  for(int i=0; i<expected.size(); ++i) {
    for(int j=0; j<26; ++j) {
      assert(SMT[i][j]==expected[i][j]);
    }
  }
  
  string P2 = "qwertyuiop1234567890ZXCVBNM";
  RollingHash<long long> rh(P2,131,1e9+7);
  int idx2 = rh.doRabbinKarpMatch("asdfghjklqwertyuiop1243567890ZXCVBNMqwertyuiop1234567890ZXCVBNMLKJHGFDSA");
  assert(idx2==36);
}
