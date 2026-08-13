class Solution {
    struct Node {
        char lc, rc;
        int llen, rlen, best, len;

        Node() : lc(0), rc(0), llen(0), rlen(0), best(0), len(0) {}

        Node(char c) {
            lc = rc = c;
            llen = rlen = best = len = 1;
        }
    };

    vector<Node> tree;

    Node merge(Node a, Node b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;
        res.len = a.len + b.len;
        res.lc = a.lc;
        res.rc = b.rc;

        res.llen = a.llen;
        res.rlen = b.rlen;

        res.best = max(a.best, b.best);

        // Entire left + entire right have the same character
        if (a.rc == b.lc) {
            res.best = max(res.best, a.rlen + b.llen);

            // Prefix extends through the whole left segment
            if (a.llen == a.len)
                res.llen = a.len + b.llen;

            // Suffix extends through the whole right segment
            if (b.rlen == b.len)
                res.rlen = b.len + a.rlen;
        }

        return res;
    }

    void build(int idx, int l, int r, string &s) {
        if (l == r) {
            tree[idx] = Node(s[l]);
            return;
        }

        int mid = (l + r) / 2;

        build(idx * 2, l, mid, s);
        build(idx * 2 + 1, mid + 1, r, s);

        tree[idx] = merge(tree[idx * 2], tree[idx * 2 + 1]);
    }

    void update(int idx, int l, int r, int pos, char c) {
        if (l == r) {
            tree[idx] = Node(c);
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(idx * 2, l, mid, pos, c);
        else
            update(idx * 2 + 1, mid + 1, r, pos, c);

        tree[idx] = merge(tree[idx * 2], tree[idx * 2 + 1]);
    }

public:
    vector<int> longestRepeating(
        string s,
        string queryCharacters,
        vector<int>& queryIndices
    ) {
        int n = s.size();

        tree.resize(4 * n + 5);

        build(1, 0, n - 1, s);

        vector<int> ans;

        for (int i = 0; i < queryCharacters.size(); i++) {
            int pos = queryIndices[i];
            char c = queryCharacters[i];

            update(1, 0, n - 1, pos, c);

            ans.push_back(tree[1].best);
        }

        return ans;
    }
};