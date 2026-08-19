class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> rows;

        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            // Store reserved seats as bits
            rows[row] |= (1 << col);
        }

        int answer = (n - rows.size()) * 2;

        for (auto &[row, mask] : rows) {
            bool left   = !(mask & (1 << 2)) &&
                          !(mask & (1 << 3)) &&
                          !(mask & (1 << 4)) &&
                          !(mask & (1 << 5));

            bool middle = !(mask & (1 << 4)) &&
                          !(mask & (1 << 5)) &&
                          !(mask & (1 << 6)) &&
                          !(mask & (1 << 7));

            bool right  = !(mask & (1 << 6)) &&
                          !(mask & (1 << 7)) &&
                          !(mask & (1 << 8)) &&
                          !(mask & (1 << 9));

            if (left && right)
                answer += 2;
            else if (left || middle || right)
                answer += 1;
        }

        return answer;
    }
};