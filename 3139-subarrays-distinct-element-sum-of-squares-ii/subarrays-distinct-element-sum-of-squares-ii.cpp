#include <vector>

class Solution {
    int MOD = 1e9 + 7;
    std::vector<long long> tree_sum;
    std::vector<long long> tree_sq;
    std::vector<long long> lazy;

    void push(int node, int l, int r) {
        if (lazy[node] != 0) {
            int mid = (l + r) / 2;
            long long v = lazy[node];

            tree_sq[2 * node] = (tree_sq[2 * node] + 2 * v * tree_sum[2 * node] + v * v % MOD * (mid - l + 1)) % MOD;
            tree_sum[2 * node] = (tree_sum[2 * node] + v * (mid - l + 1)) % MOD;
            lazy[2 * node] = (lazy[2 * node] + v) % MOD;

            tree_sq[2 * node + 1] = (tree_sq[2 * node + 1] + 2 * v * tree_sum[2 * node + 1] + v * v % MOD * (r - mid)) % MOD;
            tree_sum[2 * node + 1] = (tree_sum[2 * node + 1] + v * (r - mid)) % MOD;
            lazy[2 * node + 1] = (lazy[2 * node + 1] + v) % MOD;

            lazy[node] = 0;
        }
    }

    void update(int node, int l, int r, int ql, int qr, long long v) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            tree_sq[node] = (tree_sq[node] + 2 * v * tree_sum[node] + v * v % MOD * (r - l + 1)) % MOD;
            tree_sum[node] = (tree_sum[node] + v * (r - l + 1)) % MOD;
            lazy[node] = (lazy[node] + v) % MOD;
            return;
        }
        push(node, l, r);
        int mid = (l + r) / 2;
        update(2 * node, l, mid, ql, qr, v);
        update(2 * node + 1, mid + 1, r, ql, qr, v);
        tree_sum[node] = (tree_sum[2 * node] + tree_sum[2 * node + 1]) % MOD;
        tree_sq[node] = (tree_sq[2 * node] + tree_sq[2 * node + 1]) % MOD;
    }

public:
    int sumCounts(std::vector<int>& nums) {
        int n = nums.size();
        tree_sum.assign(4 * n, 0);
        tree_sq.assign(4 * n, 0);
        lazy.assign(4 * n, 0);

        std::vector<int> last(100005, -1);
        long long total_sum_squares = 0;
        long long current_total = 0;

        for (int j = 0; j < n; ++j) {
            int l = last[nums[j]] + 1;
            int r = j;
            
            update(1, 0, n - 1, l, r, 1);
            
            current_total = tree_sq[1];
            total_sum_squares = (total_sum_squares + current_total) % MOD;
            
            last[nums[j]] = j;
        }

        return total_sum_squares;
    }
};