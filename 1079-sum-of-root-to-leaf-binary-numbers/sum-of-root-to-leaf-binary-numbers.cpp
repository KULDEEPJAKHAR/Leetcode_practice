class Solution {
public:

    int dfs(TreeNode* root, int current) {
        if(root == NULL)
            return 0;

        current = current * 2 + root->val;

        // If leaf node
        if(root->left == NULL && root->right == NULL)
            return current;

        return dfs(root->left, current) + 
               dfs(root->right, current);
    }

    int sumRootToLeaf(TreeNode* root) {
        return dfs(root, 0);
    }
};