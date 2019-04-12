class TrieNode {
public:
    bool hasWord = false;
    vector<TrieNode *> children;
    // Initialize your data structure here.
    TrieNode() {
        this->children = vector < TrieNode * > (26, NULL);
    }
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
        TrieNode *n = root;
        for(int i=0; i<word.size(); i++) {
            int w = word[i]-'a';
            TrieNode *next = n->children[w];
            if (next==NULL) {
            	next = new TrieNode();
            	n->children[w] = next;
            }
            n = next;
        }
        n->hasWord = true;
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode *n = find(word);
                
        return n!=NULL ? n->hasWord : false;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode *n = find(prefix);
                
        return n!=NULL;
    }
        
    TrieNode* find(string s) {
        TrieNode *n = root;
        for(int i=0; i<s.size(); i++) {
            int w = s[i]-'a';
            TrieNode *next = n->children[w];
            if (next==NULL) {
            	return NULL;
            }
            n = next;
        }
                
        return n;
    }

    void release() {
        releaseNode(root);
    }
private:
    TrieNode* root;
    void releaseNode(TrieNode* n) {
        if (!n) return;
        for(auto &c : n->children) releaseNode(c);
        delete n;
    }
};

/*
 
 Binary Trie tree specialized to process binary number
 
 Used problem(s):
  - https://github.com/hiroshi-maybe/topcoder/blob/master/solutions/MojisBag/MojisBag.cpp#L59
 
 */
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
};
