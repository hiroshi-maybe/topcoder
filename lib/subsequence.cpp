#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>

using namespace std;

/*
 
 Make transition table to match string
 
 jump[i][c] = j+1 s.t. S[j]=c, j>=i
 
 If there is no 'c' in S[i..], jump[i][c]=|S|+1
 
 Usage:
  makeJ("abcdebdde");
  int next=jump[4]['c'-'a'] // next=7
 
 */
#define MAXL 20001
int jump[MAXL][26];
void makeJ(string S) {
  int N=S.size();
  for(int c=0; c<26; ++c) jump[N][c]=N+1;
  for(int i=N-1; i>=0; --i) {
    for(int c=0; c<26; ++c) jump[i][c]=jump[i+1][c];
    jump[i][S[i]-'a']=i+1;
  }
}

int main(int argc, char const *argv[]) {
  // https://leetcode.com/problems/minimum-window-subsequence/description/
  string S="abcdebdde";
  makeJ(S);
  assert(jump[4]['d'-'a']==7);
  string T="bde";
  int i=0,j=0;
  vector<int> exp={1,3,4}; // a(0)->b(1)->d(3)->e(4)
  while(i<S.size()&&j<T.size()) {
    i=jump[i][T[j++]-'a'];
    assert(i-1==exp[j-1]);
  }
  assert(i==5&&j==T.size());
}
