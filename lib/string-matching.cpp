#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int SMT[1024][26];

// build string match transition table `SMT[][]` for character set ∑={'a'-'z'}
// in CLRS 32.3
//
// input: P (|P|<=1024)
// output: SMT
//
// SMT[i][j] = length (or next matching index) of longest prefix of P for string P[0..i]+('a'+j)
// SMT[i][j] = max { k+1 : P[0..k] ⊐ P[0..i]+('a'+j) }
//
// O(|P|^3*|∑|) time
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

// for string match
vector<int> kmpFT(string s) {
  int L = s.size();
  vector<int> lps(L+1, 0);
  
  if (L==0) return lps;
  
  int j=0;
  for(int i=2; i<L; ++i) {
    j = lps[i-1];
    while(true) {
      if (s[j]==s[i-1]) {
        lps[i] = j+1; break;
      }
      if (j==0) {
        lps[i] = 0; break;
      }
      j = lps[j];
    }
  }
  
  return lps;
}

// COMPUTE-PREFIX-FUNCTION(P) in CLRS 32.4
// longest prefix/suffix
vector<int> lps(string s) {
  int L = s.size();
  vector<int> lps(L, 0);
  
  if (L==0) return lps;
  int j=0;
  for(int i=1; i<L; ++i) {
    if (s[i]==s[j]) {
      lps[i] = lps[i-1]+1;
      j++;
    } else {
      j = lps[i-1];
      while(j>0 && s[i]!=s[j]) {
        j = lps[j-1];
      }
      if (s[i]==s[j]) j++;
      lps[i] = j;
    }
  }
  
  return lps;
}

// KMP algorithm - returns index of T where P begins
int KMP(string s, string p) {
  int i = 0, j = 0, L = s.size(), M = p.size();
  
  vector<int> lps = kmpFT(p);
  while (i<L) {
    if (s[i]==p[j]) {
      i++; j++;
      if (j==M) return i-M;
    } else if (j > 0) {
      j = lps[j];
    } else {
      i++;
    }
  }
  
  return -1;
}

int main(int argc, char const *argv[]) {
  // CLRS Ex 32.4-1
  auto act = lps("ababbabbabbababbabb");
  vector<int> exp = { 0,0,1,2,0,1,2,0,1,2,0,1,2,3,4,5,6,7,8 };
  for(int i=0; i<act.size(); ++i) {
    assert(act[i]==exp[i]);
  }

  // CLRS Figure 32.7
  string P = "ababaca";
  int idx = KMP("abababacaba", P);
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
}
