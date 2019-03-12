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
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/CampSchedule.cpp#L58
 
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
 
 KMP string matching algorithm, amortized Θ(M+N) time
 
 Returns index of T where P begins.
 
 References:
  - CLRS 32.4 The Knuth-Morris-Pratt algorithm
  - http://snuke.hatenablog.com/entry/2017/07/18/101026
  - http://potetisensei.hatenablog.com/entry/2017/07/10/174908
  - http://www-igm.univ-mlv.fr/~lecroq/string/node8.html
 
 Used problems:
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/Refactoring.cpp#L193
 
 */
vector<int> doKMP(string s, string p) {
  vector<int> res;
  vector<int> pi=buildPrefixFunction(p);
  
  int j=0, L=s.size(), M=p.size();
  for(int i=0; i<L; ++i) {
    while(j>=0&&s[i]!=p[j]) j=pi[j];
    ++j;
    if(j>=M) { // matched
      res.push_back(i-j+1);
      j=pi[j];
    }
  }
  return res;
}
void test_kmp() {
  // CLRS Figure 32.7
  string P="ababaca";
  vector<int> exp={2};
  vector<int> res=doKMP("abababacaba", P);
  assert(res==exp);
}

/*
 
 String hash library to match substrings in O(1) time (preprocessing O(N) time)
 
 References:
  - https://cp-algorithms.com/string/string-hashing.html
  - CLRS 32-2
  - https://github.com/hiroshi-maybe/topcoder/blob/master/lib/modint.cpp
 
 Used problems:
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/Refactoring.cpp#L97
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/CheckTranscription.cpp#L131
 
 ```
 Usage:
   RollingHash::H s("abcabcabcabc"),p("bca");
   assert(s.hash(4,7)==p.hash(3));
 
   RollingHash::H s("abcabcabcabc"),p("bca");
   vector<int> mathces=match(s,p);
 ```
 
 */
namespace RollingHash {
template<int MOD> struct ModInt {
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
};
const int MOD0=1e9+7,MOD1=1e9+9;
using M0=ModInt<MOD0>;
using M1=ModInt<MOD1>;
M0 p0=rand()%MOD0,pinv0=p0.inv();
M1 p1=rand()%MOD1,pinv1=p1.inv();
vector<M0> P0{1}, PINV0{1};
vector<M1> P1{1}, PINV1{1};
struct H {
  vector<pair<M0,M1>> hcum;
  string str;
  H(string s) : str(s) {
    int N=(int)s.size();
    while ((int)P0.size()<=N) {
      P0.push_back(P0.back()*p0);
      PINV0.push_back(PINV0.back()*pinv0);
      P1.push_back(P1.back()*p1);
      PINV1.push_back(PINV1.back()*pinv1);
    }
    hcum.resize(N+1);
    hcum[0]={M0(0),M1(0)};
    for(int i=0; i<N; ++i) {
      hcum[i+1]={hcum[i].first+M0(s[i])*P0[i],hcum[i].second+M1(s[i])*P1[i]};
    }
  }
  // half-open range [l,r)
  pair<M0,M1> hash(int r) {
    assert(0<=r&&r<hcum.size());
    return { hcum[r].first, hcum[r].second };
  }
  pair<M0,M1> hash(int l, int r) {
    assert(0<=l&&l<hcum.size()),assert(0<=r&&r<hcum.size());
    return {
      (hcum[r].first-hcum[l].first)*PINV0[l],
      (hcum[r].second-hcum[l].second)*PINV1[l]
    };
  }
};
// Rabin-Karp algorithm
vector<int> match(H &s, H &p) {
  int N=s.str.size(),M=p.str.size();
  auto pp=p.hash(0,M);
  vector<int> res;
  for(int i=0; i<=N-M; ++i) if(s.hash(i,i+M)==pp) res.push_back(i);
  return res;
}
};
void test_rollinghash() {
  // test hash of substring
  {
    RollingHash::H h("abcabcabcabc");
    assert(h.hash(3)==h.hash(0,3));
    assert(h.hash(3)==h.hash(3,6));
    assert(h.hash(3,6)==h.hash(6,9));
    assert(h.hash(3,5)!=h.hash(6,9));
    assert(h.hash(3,7)!=h.hash(6,9));
  }
  
  // test rabin karp
  {
    RollingHash::H P("a");
    RollingHash::H S("aaaaaaaa");
    vector<int> ms=match(S,P);
    vector<int> exp={0,1,2,3,4,5,6,7};
    assert(ms==exp);
  }
  
  {
    RollingHash::H P("qwertyuiop1234567890ZXCVBNM");
    RollingHash::H S("asdfghjklqwertyuiop1243567890ZXCVBNMqwertyuiop1234567890ZXCVBNMLKJHGFDSA");
    vector<int> ms=match(S,P);
    assert(ms==vector<int>{36});
  }
  
  {
    RollingHash::H P("abcd");
    RollingHash::H S("aabcd");
    vector<int> ms=match(S,P);
    assert(ms==vector<int>{1});
  }
  
  {
    RollingHash::H P("abcd");
    RollingHash::H S("abcd");
    vector<int> ms=match(S,P);
    assert(ms==vector<int>{0});
  }
  
  {
    RollingHash::H P("abc");
    RollingHash::H S("dcba");
    vector<int> ms=match(S,P);
    assert(ms==vector<int>{});
  }
}

/*
 
 Longest palindromic substring (Manacher's algorithm), O(N) time
 
 Usage:
 ```
  // "abaaababa" => "^#a#b#a#a#a#b#a#b#a#$"
  Manacher man("abaaababa");
  // "^#a#b#a#a#a#b#a#b#a#$"
  //  112141238321416141211 (abaaaba is the longest)
  vector<int> P=man.solve();
  cout<<*max_element(P.begin(),P.end())<<endl; // show length of longest palindrome
 ```
 
 References:
  - https://www.hackerrank.com/topics/manachers-algorithm
  - https://articles.leetcode.com/longest-palindromic-substring-part-ii/
  - http://snuke.hatenablog.com/entry/2014/12/02/235837
  - https://en.wikipedia.org/wiki/Longest_palindromic_substring
 
 Used problems(s):
  - https://github.com/k-ori/leetcode/blob/master/5-longest-palindromic-substring/longest-palindromic-substring.swift#L40
 
 */
struct Manacher {
public:
  string S,T;
  Manacher(string S) : S(S) {
    int N=S.size();
    T="^";
    for(int i=0; i<N; ++i) T+="#"+S.substr(i,1)+(i==N-1?"#":"");
    T+="$";
  }
  vector<int> solve() {
    int M=T.size();
    vector<int> P(M);
    int C=0, R=-1, rad;
    for(int i=0; i<M; ++i) {
      if(i<=R) rad=min(P[2*C-i], R-i);
      else rad=0;

      // expand rad based on `i`-mirror
      while (i+rad<M&&i-rad>=0&&T[i-rad]==T[i+rad]) ++rad;
      P[i]=rad;
      if(i+rad-1>R) C=i,R=i+rad-1;
    }
    return P;
  }
  string longestPalindrome() {
    vector<int> P=solve();
    int c=-1,M=T.size();
    for(int i=1; i<M-1; ++i) if(c==-1||P[i]>P[c]) c=i;
    if(c==-1) return "";
    int s=c-P[c]+2,ss=s/2-1;
    int l=P[c]-1;
    return S.substr(ss,l);
  }
};
void test_manacher() {
  string S="xabaaababa";
  vector<int> exp={1,1,2,1,2,1,4,1,2,3,8,3,2,1,4,1,6,1,4,1,2,1,1};
  Manacher man1(S);
  vector<int> P=man1.solve();
  for(int i=0; i<P.size(); ++i) assert(P[i]==exp[i]);
  assert(man1.longestPalindrome()=="abaaaba");
  
  string S2="cdbaabcd";
  vector<int> exp2={1,1,2,1,2,1,2,1,2,5,2,1,2,1,2,1,2,1,1};
  Manacher man2(S2);
  vector<int> P2=man2.solve();
  for(int i=0; i<P2.size(); ++i) assert(P2[i]==exp2[i]);
  assert(man2.longestPalindrome()=="baab");
  
  string S3="x";
  vector<int> exp3={1,1,2,1,1};
  Manacher man3(S3);
  vector<int> P3=man3.solve();
  for(int i=0; i<P3.size(); ++i) assert(P3[i]==exp3[i]);
  assert(man3.longestPalindrome()=="x");
  
  Manacher man4("");
  vector<int> exp4={1,1};
  vector<int> P4=man4.solve();
  for(int i=0; i<P4.size(); ++i) assert(P4[i]==exp4[i]);
  assert(man4.longestPalindrome()=="");
}

/*
 
 Create an array with common prefix between S and S[i..] with Z-algorithm, O(N) time
 
 Ex.
 
 S = "aaabaaaab"
 A =  921034210
 
 S(1)=*aa*baaaab
 S(2)=*a*baaaab
 S(3)=baaaab
 S(4)=*aaa*ab
 S(5)=*aaab*
 S(6)=*aa*b
 S(7)=*a*b
 S(8)=b
 
 References:
  - http://snuke.hatenablog.com/entry/2014/12/03/214243
  - https://codeforces.com/blog/entry/3107
 
 Used problem(s):
  - https://github.com/k-ori/codeforces/blob/master/solutions/VasyaAndBigIntegers.cpp#L97
  - https://github.com/hiroshi-maybe/codeforces/blob/master/solutions/CompressString.cpp#L67
 
 */
vector<int> zalgo(string &S) {
  int N=S.size();
  vector<int> Z(N,0);
  int l=0;
  for(int i=1; i<N; ++i) {
    // S[l..r] is current right most prefix-substring
    int r=l+Z[l],pre=Z[i-l];
    if (i+pre<r) {
      Z[i]=pre;
    } else {
      int j=max(0, r-i);
      while(i+j<N&&S[j]==S[i+j]) ++j;
      Z[i]=j;
      l=i;
    }
  }
  Z[0]=N;
  return Z;
}
void test_zalgo() {
  string S="aaabaaaab";
  vector<int> exp={9,2,1,0,3,4,2,1,0};
  vector<int> res=zalgo(S);
  assert(res==exp);
}

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
  
  test_kmp();
  
  // CLRS Figure 32.7
  string P="ababaca";
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

  test_rollinghash();
  test_manacher();
  test_zalgo();
}
