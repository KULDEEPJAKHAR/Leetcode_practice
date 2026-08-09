class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();

        // suffix sum
        vector<int> suffix(n + 1, 0);
        for (int i = n - 1; i >= 0; --i)
            suffix[i] = suffix[i + 1] + piles[i];

        vector<vector<int>> dp(n, vector<int>(n + 1, -1));

        function<int(int,int)> dfs = [&](int i, int M) {
            if (i >= n) return 0;

            // can take all remaining piles
            if (i + 2 * M >= n)
                return suffix[i];

            if (dp[i][M] != -1)
                return dp[i][M];

            int best = 0;

            for (int X = 1; X <= 2 * M; ++X) {
                // current player gets remaining stones minus what opponent can get
                best = max(best,
                           suffix[i] - dfs(i + X, max(M, X)));
            }

            return dp[i][M] = best;
        };

        return dfs(0, 1);
    }
};