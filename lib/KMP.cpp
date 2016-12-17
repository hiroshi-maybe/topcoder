#include <iostream>
#include <algorithm> // max,min
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <utility>
#include <set>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// type alias
const int INF = 1e9;
typedef unsigned long UL;
typedef long long LL;

typedef vector < bool > VB;
typedef vector < int > VI;
typedef vector < string > VS;
typedef vector < vector < int > > VVI;
typedef unordered_map < int, int > MAPII;
typedef unordered_map < string, int > MAPSI;
typedef unordered_set < int > SETI;
typedef unordered_set < string > SETS;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
#define REPS(i,arr)  for(int i=0; i<(arr).size(); ++i)

// debug cout
#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

// for string match
VI kmpFT(string s) {
  int L = SZ(s);
  VI lps(L+1, 0);
  
  if (L==0) return lps;
  
  int j=0;
  FOR(i,2,L) {
    dump2(i,j);
    j = lps[i-1];
    while(true) {
      if (s[j]==s[i-1]) {
        lps[i] = j+1; break;
      }
      if (j==0) {
        lps[i] = 0; break;
      }
      dump(j);
      j = lps[j];
    }
  }
  
  return lps;
}

// longest prefix/suffix
VI lps(string s) {
  int L = SZ(s);
  VI lps(L, 0);
  
  if (L==0) return lps; 
  int j=0;
  FOR(i,1,L) {
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

int KMP(string s, string p) {
  int i = 0, j = 0, L = SZ(s), M = SZ(p);
  
  VI lps = kmpFT(p);
  dumpAR(lps);
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
  VI f = lps("ABAAB");
  dumpAR(f);
  int idx = KMP("ABABABAABAAB", "ABAAB");
  dump(idx);
}
