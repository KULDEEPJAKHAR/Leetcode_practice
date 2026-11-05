#include <vector>
#include <set>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
    // Helper structure to maintain sliding window median and sums
    struct SlidingMedian {
        multiset<long long> left, right;
        long long sum_left = 0, sum_right = 0;
        int k; // window size x

        SlidingMedian(int window_size) : k(window_size) {}

        void balance() {
            while (left.size() > right.size() + 1) {
                auto it = prev(left.end());
                long long val = *it;
                left.erase(it);
                sum_left -= val;
                right.insert(val);
                sum_right += val;
            }
            while (left.size() < right.size()) {
                auto it = right.begin();
                long long val = *it;
                right.erase(it);
                sum_right -= val;
                left.insert(val);
                sum_left += val;
            }
        }

        void add(long long val) {
            if (left.empty() || val <= *left.rbegin()) {
                left.insert(val);
                sum_left += val;
            } else {
                right.insert(val);
                sum_right += val;
            }
            balance();
        }

        void remove(long long val) {
            auto it_left = left.find(val);
            if (it_left != left.end()) {
                sum_left -= val;
                left.erase(it_left);
            } else {
                auto it_right = right.find(val);
                if (it_right != right.end()) {
                    sum_right -= val;
                    right.erase(it_right);
                }
            }
            balance();
        }

        long long get_cost() {
            long long median = *left.rbegin();
            long long left_cost = (long long)left.size() * median - sum_left;
            long long right_cost = sum_right - (long long)right.size() * median;
            return left_cost + right_cost;
        }
    };

public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        vector<long long> window_cost(n, 0);
        SlidingMedian sm(x);

        // Precompute cost for all x-sized windows
        for (int i = 0; i < n; ++i) {
            sm.add(nums[i]);
            if (i >= x) {
                sm.remove(nums[i - x]);
            }
            if (i >= x - 1) {
                window_cost[i] = sm.get_cost();
            }
        }

        // DP state: dp[j][i] = min cost to choose j subarrays up to index i
        const long long INF = 1e18;
        vector<vector<long long>> dp(k + 1, vector<long long>(n + 1, INF));

        for (int i = 0; i <= n; ++i) {
            dp[0][i] = 0; // 0 subarrays cost 0
        }

        for (int j = 1; j <= k; ++j) {
            for (int i = j * x; i <= n; ++i) {
                // Choice 1: Don't form a subarray ending at i-1
                dp[j][i] = dp[j][i - 1];

                // Choice 2: Form a subarray ending at i-1 (starts at i-x)
                long long cost = window_cost[i - 1];
                if (dp[j - 1][i - x] != INF) {
                    dp[j][i] = min(dp[j][i], dp[j - 1][i - x] + cost);
                }
            }
        }

        return dp[k][n];
    }
};