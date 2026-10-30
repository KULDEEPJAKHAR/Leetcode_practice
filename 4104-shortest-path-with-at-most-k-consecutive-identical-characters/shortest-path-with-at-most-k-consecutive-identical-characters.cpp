class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int, int>>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
        }

        const int INF = 1e9;
        vector<vector<int>> dist(n, vector<int>(k + 1, INF));
        priority_queue<tuple<int, int, int>,
                       vector<tuple<int, int, int>>,
                       greater<tuple<int, int, int>>> pq;

        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [d, u, cnt] = pq.top();
            pq.pop();

            if (d != dist[u][cnt]) continue;

            for (auto& [v, w] : adj[u]) {
                int nextCnt = (labels[u] == labels[v]) ? cnt + 1 : 1;

                if (nextCnt > k) continue;

                int nd = d + w;

                if (nd < dist[v][nextCnt]) {
                    dist[v][nextCnt] = nd;
                    pq.push({nd, v, nextCnt});
                }
            }
        }

        int ans = INF;
        for (int cnt = 1; cnt <= k; cnt++) {
            ans = min(ans, dist[n - 1][cnt]);
        }

        return ans == INF ? -1 : ans;
    }
};