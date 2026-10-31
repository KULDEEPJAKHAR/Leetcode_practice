#include <vector>

using namespace std;

class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        const int MOD = 1e9 + 7;

        vector<vector<vector<long long>>> dp(m, vector<vector<long long>>(n, vector<long long>(2, 0)));

        if (n > 1) {
            dp[0][1][0] = 1;
        }
        if (m > 1) {
            dp[1][0][1] = 1;
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) continue;

                if (grid[i][j] == 1) {
                    if (i + 1 < m) {
                        dp[i + 1][j][1] = (dp[i + 1][j][1] + dp[i][j][0]) % MOD;
                    }
                } else {
                    if (j + 1 < n) {
                        dp[i][j + 1][0] = (dp[i][j + 1][0] + dp[i][j][0]) % MOD;
                    }
                    if (i + 1 < m) {
                        dp[i + 1][j][1] = (dp[i + 1][j][1] + dp[i][j][0]) % MOD;
                    }
                }

                if (grid[i][j] == 1) {
                    if (j + 1 < n) {
                        dp[i][j + 1][0] = (dp[i][j + 1][0] + dp[i][j][1]) % MOD;
                    }
                } else {
                    if (i + 1 < m) {
                        dp[i + 1][j][1] = (dp[i + 1][j][1] + dp[i][j][1]) % MOD;
                    }
                    if (j + 1 < n) {
                        dp[i][j + 1][0] = (dp[i][j + 1][0] + dp[i][j][1]) % MOD;
                    }
                }
            }
        }

        return (dp[m - 1][n - 1][0] + dp[m - 1][n - 1][1]) % MOD;
    }
};