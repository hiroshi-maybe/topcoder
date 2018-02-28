#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>

using namespace std;

/*
 
 Binary search tree
 
 https://en.wikipedia.org/wiki/Binary_search_tree
 https://en.wikipedia.org/wiki/Tree_traversal
 
 - Inorder traversal of BST gives sorted list
 - Either pre-order or post-order paired with in-order is sufficient to describe the tree uniquely
 
 */

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Morris traversal, O(1) space inorder tranversal

vector<int> xs;
void proc(TreeNode* n) {
  xs.push_back(n->val);
}
void inorder(TreeNode* root) {
  while (root) {
    if (!root->left) {
      proc(root);
      root = root->right;
    } else {
      TreeNode* pre = root->left;
      while(pre->right!=NULL&&pre->right!=root) pre = pre->right;
      
      if (!pre->right) {
        // create back link
        pre->right = root;
        root = root->left;
      } else {
        // reached parent
        pre->right = NULL;
        
        proc(root);
        root = root->right;
      }
    }
  }
}

int main(int argc, char const *argv[]) {
  
}
