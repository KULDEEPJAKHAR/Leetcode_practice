class Solution {
public:
    int rows[9] = {0}, cols[9] = {0}, boxes[9] = {0};

    bool solve(vector<vector<char>>& board, int r, int c) {
        if (r == 9) return true;
        if (c == 9) return solve(board, r + 1, 0);
        if (board[r][c] != '.') return solve(board, r, c + 1);

        for (int num = 1; num <= 9; num++) {
            int mask = 1 << num;
            int boxIndex = (r / 3) * 3 + (c / 3);

            if (!(rows[r] & mask) && !(cols[c] & mask) && !(boxes[boxIndex] & mask)) {
                board[r][c] = num + '0';
                rows[r] |= mask;
                cols[c] |= mask;
                boxes[boxIndex] |= mask;

                if (solve(board, r, c + 1)) return true;

                board[r][c] = '.';
                rows[r] ^= mask;
                cols[c] ^= mask;
                boxes[boxIndex] ^= mask;
            }
        }
        return false;
    }

    void solveSudoku(vector<vector<char>>& board) {
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (board[r][c] != '.') {
                    int num = board[r][c] - '0';
                    int mask = 1 << num;
                    rows[r] |= mask;
                    cols[c] |= mask;
                    boxes[(r / 3) * 3 + (c / 3)] |= mask;
                }
            }
        }
        solve(board, 0, 0);
    }
};
