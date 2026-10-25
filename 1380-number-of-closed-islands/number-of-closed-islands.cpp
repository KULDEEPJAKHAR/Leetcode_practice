class Solution {
private:
    bool dfs(vector<vector<int>>& grid, int r, int c) {
        int rows = grid.size();
        int cols = grid[0].size();
        
        if (r < 0 || r >= rows || c < 0 || c >= cols) {
            return false;
        }
        
        if (grid[r][c] == 1) {
            return true;
        }
        
        grid[r][c] = 1;
        
        bool left = dfs(grid, r, c - 1);
        bool right = dfs(grid, r, c + 1);
        bool up = dfs(grid, r - 1, c);
        bool down = dfs(grid, r + 1, c);
        
        return left && right && up && down;
    }

public:
    int closedIsland(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int closedIslandsCount = 0;
        
        for (int c = 0; c < cols; ++c) {
            if (grid[0][c] == 0) dfs(grid, 0, c);
            if (grid[rows - 1][c] == 0) dfs(grid, rows - 1, c);
        }
        
        for (int r = 0; r < rows; ++r) {
            if (grid[r][0] == 0) dfs(grid, r, 0);
            if (grid[r][cols - 1] == 0) dfs(grid, r, cols - 1);
        }
        
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 0) {
                    closedIslandsCount++;
                    dfs(grid, r, c);
                }
            }
        }
        
        return closedIslandsCount;
    }
};