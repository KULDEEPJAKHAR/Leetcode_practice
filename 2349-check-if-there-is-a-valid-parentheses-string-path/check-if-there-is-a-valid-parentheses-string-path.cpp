class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();

        if (grid[0][0] == ')' || grid[n - 1][m - 1] == '(')
            return false;

        if ((n + m - 1) % 2)
            return false;

        vector<vector<vector<bool>>> dp(
            n, vector<vector<bool>>(m, vector<bool>(n + m + 1, false))
        );

        dp[0][0][1] = true;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int bal = 0; bal <= n + m; bal++) {
                    if (!dp[i][j][bal]) continue;

                    if (i + 1 < n) {
                        int nb = bal + (grid[i + 1][j] == '(' ? 1 : -1);
                        if (nb >= 0)
                            dp[i + 1][j][nb] = true;
                    }

                    if (j + 1 < m) {
                        int nb = bal + (grid[i][j + 1] == '(' ? 1 : -1);
                        if (nb >= 0)
                            dp[i][j + 1][nb] = true;
                    }
                }
            }
        }

        return dp[n - 1][m - 1][0];
    }
};