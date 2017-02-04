// Morris traversal
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
