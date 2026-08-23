class Solution {
public:
    bool sumGame(string num) {
        int n = num.size(), diff = 0, leftQ = 0, rightQ = 0;

        for (int i = 0; i < n; i++) {
            if (num[i] == '?') {
                if (i < n / 2) leftQ++;
                else rightQ++;
            } else {
                if (i < n / 2) diff += num[i] - '0';
                else diff -= num[i] - '0';
            }
        }

        if ((leftQ + rightQ) % 2) return true;

        return diff != (rightQ - leftQ) / 2 * 9;
    }
};