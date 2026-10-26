class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int islandCount = 0;

        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] > 0 && !visited[i][j]) {
                    long long currentSum = 0;
                    queue<pair<int, int>> q;
                    
                    q.push({i, j});
                    visited[i][j] = true;

                    while (!q.empty()) {
                        auto [r, c] = q.front();
                        q.pop();
                        currentSum += grid[r][c];

                        for (int d = 0; d < 4; ++d) {
                            int nr = r + dr[d];
                            int nc = c + dc[d];

                            if (nr >= 0 && nr < m && nc >= 0 && nc < n && 
                                grid[nr][nc] > 0 && !visited[nr][nc]) {
                                visited[nr][nc] = true;
                                q.push({nr, nc});
                            }
                        }
                    }

                    if (currentSum % k == 0) {
                        islandCount++;
                    }
                }
            }
        }

        return islandCount;
    }
};