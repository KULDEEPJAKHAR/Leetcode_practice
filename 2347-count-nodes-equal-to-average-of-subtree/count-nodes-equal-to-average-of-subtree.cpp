class Solution {
public:
    int ans = 0;

    pair<int, int> dfs(TreeNode* root) {
        if (!root) return {0, 0};

        auto [ls, lc] = dfs(root->left);
        auto [rs, rc] = dfs(root->right);

        int sum = ls + rs + root->val;
        int count = lc + rc + 1;

        if (sum / count == root->val)
            ans++;

        return {sum, count};
    }

    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return ans;
    }
};