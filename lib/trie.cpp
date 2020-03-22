#include <bits/stdc++.h>
using namespace std;

/*
 
 Trie tree, O(∑len(str)) time
 
 Usage:
  TrieNode* trie=new TrieNode();
  REP(i,N) {
    string w=W[i];
    reverse(w.begin(),w.end());
    trie->insert(i,w);
  }
  int id=trie->search(query);
 
 Used problems:
  - https://github.com/hiroshi-maybe/leetcode/blob/master/208-Implement-Trie/Trie.cpp#L23
   - verifier
  - https://github.com/hiroshi-maybe/GCJ/blob/master/2019-R1A/AlienRhyme.cpp#L40
  - https://github.com/hiroshi-maybe/topcoder/blob/master/solutions/MojisBag/MojisBag.cpp#L59
   - binary trie tree (maximize XOR pair query)
  - https://github.com/hiroshi-maybe/leetcode/blob/master/1032-stream-of-characters/stream-of-characters.cpp#L43
   - search by reversed order
  - https://github.com/hiroshi-maybe/GCJ/blob/master/kickstart/2020A/Bundling.cpp#L48
 
 */

class TrieNode {
public:
  const char C_SIZE=26;
  const char BASE='a';
  int cnt=0; // # of strs in subtree
  set<int> ids; // str ending here
  vector<TrieNode*> cs;
  TrieNode() { this->cs=vector<TrieNode*>(C_SIZE,nullptr); }
  void release() { for(auto c : cs) if(c!=nullptr) c->release(), delete c; }
  void insert(int id, string &s, int p=0) {
    ++cnt;
    if(p==s.size()) {
      ids.emplace(id);
      return;
    }
    int i=index(s[p]);
    auto x=cs[i];
    if(x==nullptr) x=new TrieNode(),cs[i]=x;
    x->insert(id,s,p+1);
  }
  // true: erase success, false: failure, id:-1=>wildcard
  bool erase(int id, string &s, int p=0) {
    if(p==s.size()) {
      bool res=false;
      if(ids.count(id)) ids.erase(id),res=true;
      else if(id==-1) { // wildcard
        if(ids.size()) res=true,ids.erase(ids.begin());
        return res;
      }
      return res;
    }
    int i=index(s[p]);
    auto x=cs[i];
    if(x==nullptr) return false;
    bool res=x->erase(id,s,p+1);
    if(res) --cnt;
    return res;
  }
  TrieNode* find(string &s, int p=0) {
    if(p==s.size()) return this;
    int i=index(s[p]);
    if(cs[i]==nullptr) return nullptr;
    return cs[i]->find(s,p+1);
  }
  // success: id, failure: -1
  int search(string s) {
    TrieNode* n=find(s);
    return (n!=nullptr&&n->ids.size())?*(n->ids.begin()):-1;
  }
  // # of strs with prefix `p`
  int prefix(string p) {
    TrieNode* n=find(p);
    return n!=nullptr?n->cnt:0;
  }
private:
  int index(char c) {
    int i=c-BASE;
    assert(0<=i&&i<C_SIZE);
    return i;
  }
};

void test_trie() {
  TrieNode* trie=new TrieNode();
  string s1="apple";
  trie->insert(0,s1);
  assert(trie->search("apple")==0);
  assert(trie->search("app")==-1);

  string s2="app";
  trie->insert(1,s2);
  assert(trie->prefix("app")==2);
  assert(trie->search("app")==1);
  assert(trie->search("appl")==-1);
  
  assert(!trie->erase(0,s2));
  assert(trie->erase(-1,s2));
  
  assert(trie->search(s2)==-1);
  
  trie->release(), delete trie;
}

/*
 
 Binary Trie tree specialized to process binary digits
 
 Used problem(s):
  - https://github.com/hiroshi-maybe/topcoder/blob/master/solutions/MojisBag/MojisBag.cpp#L59
 
 */
/*
class BinaryTrieNode {
public:
  int cnt=0;
  set<int> ids;
  LL val=-1;
  BinaryTrieNode* children[2];
  // Initialize your data structure here.
  BinaryTrieNode() {
    children[0]=children[1]=nullptr;
  }
};

class BinaryTrie {
public:
  const int MAX_D=30;
  BinaryTrie() {
    root=new BinaryTrieNode();
  }
  void insert(LL X, int id) {
    dump("add",X,id);
    BinaryTrieNode *n=root; n->cnt++;
    for(int i=MAX_D; i>=0; --i) {
      int b=(X>>i)&1;
      assert(n!=nullptr);
      assert(0<=b&&b<2);
      BinaryTrieNode *next=n->children[b];
      if(next==nullptr) {
        next=new BinaryTrieNode();
        n->children[b]=next;
      }
      assert(next!=nullptr);
      next->cnt++;
      n=next;
    }
    n->val=X;
    n->ids.emplace(id);
  }
  void erase(LL X, int id) {
    dump("rem",X,id);
    BinaryTrieNode *n=root; n->cnt--;
    for(int i=MAX_D; i>=0; --i) {
      int b=(X>>i)&1;
      BinaryTrieNode *next=n->children[b];
      if(next==nullptr) return;
      next->cnt--;
      n=next;
    }
    assert(n!=nullptr);
    n->ids.erase(id);
  }
  // id, value
  pair<int,LL> xorcp(LL X) {
    BinaryTrieNode *n=root;
    for(int i=MAX_D; i>=0; --i) {
      int b=(X>>i)&1;
      BinaryTrieNode *next=n->children[b^1];
      if(next==nullptr||next->cnt==0) next=n->children[b];
      assert(next!=nullptr);
      n=next;
    }
    assert(n!=nullptr);
    return {*(n->ids.begin()), n->val};
  }
  set<int> search(LL q) {
    BinaryTrieNode *n=find(q);
    return n!=nullptr?n->ids:set<int>();
  }
  
  BinaryTrieNode* find(LL q) {
    BinaryTrieNode *n=root;
    for(int i=MAX_D; i>=0; --i) {
      int b=(q>>i)&1;
      BinaryTrieNode *next=n->children[b];
      if(next==nullptr) return nullptr;
      n=next;
    }
    return n;
  }
  
  void release() {
    releaseNode(root);
  }
private:
  BinaryTrieNode* root;
  void releaseNode(BinaryTrieNode* n) {
    if (!n) return;
    REP(i,2) releaseNode(n->children[i]);
    delete n;
  }
};*/

int main() {
  test_trie();
  return 0;
}

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG trie.cpp && ./a.out
