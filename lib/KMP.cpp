#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

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
  int idx = KMP("abababacaba", "ababaca");
  assert(idx==2);
}
