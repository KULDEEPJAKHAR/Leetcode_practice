class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();
        vector<int> ans(m);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> available;
        priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<tuple<long long, int, int>>> unavailable;

        for (int i = 0; i < n; ++i) {
            available.push({servers[i], i});
        }

        long long curr_time = 0;

        for (int j = 0; j < m; ++j) {
            curr_time = max(curr_time, (long long)j);

            if (available.empty() && !unavailable.empty()) {
                curr_time = max(curr_time, get<0>(unavailable.top()));
            }

            while (!unavailable.empty() && get<0>(unavailable.top()) <= curr_time) {
                auto [free_time, weight, index] = unavailable.top();
                unavailable.pop();
                available.push({weight, index});
            }

            auto [weight, index] = available.top();
            available.pop();

            ans[j] = index;
            unavailable.push({curr_time + tasks[j], weight, index});
        }

        return ans;
    }
};