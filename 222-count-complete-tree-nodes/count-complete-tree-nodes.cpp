class Solution {
public:
    
    int height(TreeNode* node) {
        int h = 0;
        while (node) {
            h++;
            node = node->left;
        }
        return h;
    }
    
    int countNodes(TreeNode* root) {
        if (!root) return 0;

        int lh = height(root->left);
        int rh = height(root->right);

        if (lh == rh) {
            return (1 << lh) + countNodes(root->right);
        } else {
            return (1 << rh) + countNodes(root->left);
        }
    }
};