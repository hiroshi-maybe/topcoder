#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>

using namespace std;

/*
 
 Subsequence query, initialization: O(|S|*|C|) time, query: O(|W|) time
 
 T[i][c] = if exists => first occurence of 'c' in S[i..] s.t. S[j]=c
           otherwise => -1
 
 If S = "ababc"..
 
 `T` is below:
 
    0 1 2 3 4 5
    a b a b c $
   ------------
 a| 0 2 2-1-1-1
 b| 1 1 3 3-1-1
 c| 4 4 4 4 4-1
 d|-1-1-1-1-1-1
 
 Usage:
 SubSeqQuery ss("abcdebdde");
 cout << ss.issubseq("ade") << endl; // true
 
 Used problems:
  - https://leetcode.com/problems/minimum-window-subsequence/description/
  - https://leetcode.com/problems/number-of-matching-subsequences/description/
 
 */

#define MAXL 20002
int T[MAXL][26];
struct SubSeqQuery {
public:
  SubSeqQuery(string S) {
    
    // Copy and paste this if convenient
    int N=S.size();
    memset(T,-1,sizeof(T));
    for(int i=N-1; i>=0; --i) {
      for(int c=0; c<26; ++c) T[i][c]=T[i+1][c];
      T[i][S[i]-'a']=i;
    }
    
  }
  
  bool issubseq(string s) {
    bool res=true;
    int j=0;
    for(int i=0; i<s.size(); ++i) {
      j=T[j][s[i]-'a'];
      if(j==-1) {
        res=false;
        break;
      }
      ++j;
    }
    return res;
  }
};

// Naiive subsequence solver, O(s+p) time
bool issubseq(string S, string SS) {
  int p=0;
  for(int i=0; i<S.size(); ++i) if(p<SS.size()&&S[i]==SS[p]) {
    ++p;
  }
  return p==SS.size();
}

int main(int argc, char const *argv[]) {
  string s="abcdebdde";
  SubSeqQuery ss(s);
  assert(T[0]['a'-'a']==0);
  assert(T[0]['d'-'a']==3);
  assert(T[4]['d'-'a']==6);
  assert(T[4]['z'-'a']==-1);
  assert(ss.issubseq("bde"));
  assert(!ss.issubseq("eca"));
  
  assert(issubseq("abcde","acd"));
  assert(!issubseq("acd","abcde"));
  assert(!issubseq("abcde","az"));
  /*
  s="ababc";
  ss = SubSeqQuery(s);
  for(int c=0; c<26; ++c) {
    for(int i=0; i<=s.size(); ++i) cout << ss.T[i][c]<<",";
    cout << endl;
  }*/
}
