#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Solution {
    int timer = 0;
    vector<int> tin, tout;
    vector<vector<int>> up;
    vector<int> depth;
    int LOG;

    struct BIT {
        int n;
        vector<int> tree;
        BIT(int n) : n(n), tree(n + 1, 0) {}

        void update(int idx, int val) {
            for (; idx <= n; idx += idx & -idx) {
                tree[idx] ^= val;
            }
        }

        int query(int idx) {
            int sum = 0;
            for (; idx > 0; idx -= idx & -idx) {
                sum ^= tree[idx];
            }
            return sum;
        }
    };

    void dfs(int u, int p, int d, const vector<vector<int>>& adj) {
        tin[u] = ++timer;
        depth[u] = d;
        up[u][0] = p;

        for (int i = 1; i < LOG; ++i) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }

        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, d + 1, adj);
            }
        }
        tout[u] = timer;
    }

    int getLCA(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);

        for (int i = LOG - 1; i >= 0; --i) {
            if (depth[u] - (1 << i) >= depth[v]) {
                u = up[u][i];
            }
        }

        if (u == v) return u;

        for (int i = LOG - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }

        return up[u][0];
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        vector<vector<int>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        tin.resize(n);
        tout.resize(n);
        depth.resize(n);
        up.assign(n, vector<int>(LOG, 0));

        dfs(0, 0, 0, adj);

        BIT bit(n);
        vector<int> curr_mask(n);
        for (int i = 0; i < n; ++i) {
            curr_mask[i] = 1 << (s[i] - 'a');
            bit.update(tin[i], curr_mask[i]);
            bit.update(tout[i] + 1, curr_mask[i]);
        }

        vector<bool> result;

        for (const string& q : queries) {
            stringstream ss(q);
            string type;
            ss >> type;

            if (type == "update") {
                int u;
                char c;
                ss >> u >> c;

                int old_mask = curr_mask[u];
                int new_mask = 1 << (c - 'a');
                int diff = old_mask ^ new_mask;

                if (diff != 0) {
                    curr_mask[u] = new_mask;
                    bit.update(tin[u], diff);
                    bit.update(tout[u] + 1, diff);
                }
            } else if (type == "query") {
                int u, v;
                ss >> u >> v;

                int lca = getLCA(u, v);

                int mask_u = bit.query(tin[u]);
                int mask_v = bit.query(tin[v]);
                int mask_lca = bit.query(tin[lca]);

                int path_mask = mask_u ^ mask_v ^ curr_mask[lca];

                bool is_palindrome = (path_mask & (path_mask - 1)) == 0;
                result.push_back(is_palindrome);
            }
        }

        return result;
    }
};