class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        unordered_set<int> st(nums.begin(), nums.end());
        vector<int> vals(st.begin(), st.end());

        const int MAXX = 2048;

        vector<bool> dp0(MAXX, false), dp1(MAXX, false);
        dp0[0] = true;

        for (int t = 0; t < 3; t++) {
            fill(dp1.begin(), dp1.end(), false);
            for (int x = 0; x < MAXX; x++) {
                if (!dp0[x]) continue;
                for (int v : vals)
                    dp1[x ^ v] = true;
            }
            dp0.swap(dp1);
        }

        int ans = 0;
        for (bool x : dp0) ans += x;
        return ans;
    }
};