/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==NULL) return NULL;
        if(root==p||root==q)return root;
        TreeNode* leftCA = lowestCommonAncestor(root->left,p,q);
           TreeNode* rightCA = lowestCommonAncestor(root->right,p,q);
        if(leftCA&&rightCA){
            return root;
        }
        else if(leftCA!=NULL) return leftCA;
        else return rightCA;
    }
    
};