


        class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<array<long long, 4>> dp(n + 1, {0, 0, 0, 0});
        vector<vector<int>> idx(n);

        for (int i = 0; i < n; ++i) {
            idx[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        }

        sort(idx.begin(), idx.end(), [](const auto& a, const auto& b) {
            return a[0] < b[0];
        });

        vector<int> starts(n);
        for (int i = 0; i < n; ++i) starts[i] = idx[i][0];

        vector<int> nxt(n);
        for (int i = 0; i < n; ++i) {
            nxt[i] = upper_bound(starts.begin(), starts.end(), idx[i][1]) - starts.begin();
        }

        struct State {
            long long sum;
            vector<int> ids;
        };

        vector<vector<State>> f(n + 1, vector<State>(5));
        f[n][0] = {0, {}};

        auto better = [](const State& a, const State& b) {
            if (a.sum != b.sum) return a.sum > b.sum;
            return a.ids < b.ids;
        };

        for (int i = n - 1; i >= 0; --i) {
            for (int k = 0; k <= 4; ++k) {
                f[i][k] = f[i + 1][k];

                if (k < 4) {
                    State cur = f[nxt[i]][k + 1];
                    cur.sum += idx[i][2];
                    cur.ids.push_back(idx[i][3]);
                    sort(cur.ids.begin(), cur.ids.end());

                    if (better(cur, f[i][k]))
                        f[i][k] = cur;
                }
            }
        }

        return f[0][0].ids;
    }
};


