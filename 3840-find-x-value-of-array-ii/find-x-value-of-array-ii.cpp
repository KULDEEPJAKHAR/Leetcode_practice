


        


class Solution {
    struct Node {
        int prod;
        int cnt[5];

        Node() {
            prod = 1;
            memset(cnt, 0, sizeof(cnt));
        }
    };

    int k;
    vector<Node> tree;

    Node merge(Node a, Node b) {
        Node res;
        res.prod = (a.prod * b.prod) % k;

        for (int i = 0; i < k; i++)
            res.cnt[i] = a.cnt[i];

        for (int i = 0; i < k; i++)
            res.cnt[(a.prod * i) % k] += b.cnt[i];

        return res;
    }

    void build(int p, int l, int r, vector<int>& nums) {
        if (l == r) {
            int x = nums[l] % k;
            tree[p].prod = x;
            tree[p].cnt[x] = 1;
            return;
        }

        int m = (l + r) / 2;

        build(p * 2, l, m, nums);
        build(p * 2 + 1, m + 1, r, nums);

        tree[p] = merge(tree[p * 2], tree[p * 2 + 1]);
    }

    void update(int p, int l, int r, int idx, int val) {
        if (l == r) {
            tree[p] = Node();
            val %= k;
            tree[p].prod = val;
            tree[p].cnt[val] = 1;
            return;
        }

        int m = (l + r) / 2;

        if (idx <= m)
            update(p * 2, l, m, idx, val);
        else
            update(p * 2 + 1, m + 1, r, idx, val);

        tree[p] = merge(tree[p * 2], tree[p * 2 + 1]);
    }

    Node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tree[p];

        int m = (l + r) / 2;

        if (qr <= m)
            return query(p * 2, l, m, ql, qr);

        if (ql > m)
            return query(p * 2 + 1, m + 1, r, ql, qr);

        return merge(
            query(p * 2, l, m, ql, qr),
            query(p * 2 + 1, m + 1, r, ql, qr)
        );
    }

public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        this->k = k;

        int n = nums.size();
        tree.resize(4 * n);

        build(1, 0, n - 1, nums);

        vector<int> ans;

        for (auto& q : queries) {
            update(1, 0, n - 1, q[0], q[1]);

            Node res = query(1, 0, n - 1, q[2], n - 1);

            ans.push_back(res.cnt[q[3]]);
        }

        return ans;
    }
};




    
