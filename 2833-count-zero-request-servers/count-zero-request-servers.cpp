class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        int m = logs.size();
        int q = queries.size();

        sort(logs.begin(), logs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        vector<pair<int, int>> sorted_queries(q);
        for (int i = 0; i < q; ++i) {
            sorted_queries[i] = {queries[i], i};
        }
        sort(sorted_queries.begin(), sorted_queries.end());

        vector<int> result(q);
        unordered_map<int, int> server_count;
        int left = 0, right = 0;

        for (const auto& [time, original_idx] : sorted_queries) {
            int win_start = time - x;
            int win_end = time;

            while (right < m && logs[right][1] <= win_end) {
                server_count[logs[right][0]]++;
                right++;
            }

            while (left < m && logs[left][1] < win_start) {
                int server_id = logs[left][0];
                if (--server_count[server_id] == 0) {
                    server_count.erase(server_id);
                }
                left++;
            }

            result[original_idx] = n - server_count.size();
        }

        return result;
    }
};