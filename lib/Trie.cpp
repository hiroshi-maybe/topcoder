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
