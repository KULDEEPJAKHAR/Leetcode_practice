class Solution {
public:
    int minOperations(string s, int k) {
        int n = s.length();
        int initial_zeros = 0;
        for (char c : s) if (c == '0') initial_zeros++;

        if (initial_zeros == 0) return 0;

       
        set<int> unvisited[2];
        for (int i = 0; i <= n; ++i) {
            unvisited[i % 2].insert(i);
        }

        queue<pair<int, int>> q;
        q.push({initial_zeros, 0});
        unvisited[initial_zeros % 2].erase(initial_zeros);

        while (!q.empty()) {
            auto [curr_z, steps] = q.front();
            q.pop();

           
            int min_x = max(0, k - (n - curr_z));
            int max_x = min(curr_z, k);
           
            int low = curr_z + k - 2 * max_x;
            int high = curr_z + k - 2 * min_x;
            int p = low % 2;

            auto it = unvisited[p].lower_bound(low);
            while (it != unvisited[p].end() && *it <= high) {
                if (*it == 0) return steps + 1;
                q.push({*it, steps + 1});
                it = unvisited[p].erase(it); 
            }
        }

        return -1;
    }
};