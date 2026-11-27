class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        const int MAX_F = 1500;
        vector<int> freq(MAX_F + 1, 0);
        for (const auto& item : items) {
            freq[item[0]]++;
        }

        // multCount[f] = total number of items whose factor is divisible by f
        vector<int> multCount(MAX_F + 1, 0);
        for (int f = 1; f <= MAX_F; ++f) {
            for (int m = f; m <= MAX_F; m += f) {
                multCount[f] += freq[m];
            }
        }

        // dp[b] = max total items with cost <= b
        vector<int> dp(budget + 1, 0);

        for (const auto& item : items) {
            int f = item[0];
            int p = item[1];
            if (p > budget) continue;

            int firstGain = multCount[f]; // 1 purchased + (multCount[f] - 1) free
            vector<int> ndp = dp;

            // Step 1: Buy the 1st copy of this item (0/1 transition)
            vector<int> withItem(budget + 1, -1);
            for (int b = p; b <= budget; ++b) {
                withItem[b] = dp[b - p] + firstGain;
            }

            // Step 2: Buy 2nd, 3rd, ... copies of this item (unbounded transition)
            for (int b = 2 * p; b <= budget; ++b) {
                if (withItem[b - p] != -1) {
                    withItem[b] = max(withItem[b], withItem[b - p] + 1);
                }
            }

            // Merge back into main DP
            for (int b = p; b <= budget; ++b) {
                ndp[b] = max(ndp[b], withItem[b]);
            }
            dp = move(ndp);
        }

        return *max_element(dp.begin(), dp.end());
    }
};