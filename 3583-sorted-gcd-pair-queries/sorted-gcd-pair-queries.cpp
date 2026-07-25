class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());
        vector<int> freq(mx + 1, 0);
        for (int x : nums) freq[x]++;
        vector<int> divCnt(mx + 1, 0);
        for (int d = 1; d <= mx; d++) {
            for (int j = d; j <= mx; j += d)
                divCnt[d] += freq[j];
        }
        vector<long long> gcdCnt(mx + 1, 0);
        for (int g = mx; g >= 1; g--) {
            long long c = divCnt[g];
            gcdCnt[g] = c * (c - 1) / 2;
            for (int j = g + g; j <= mx; j += g)
                gcdCnt[g] -= gcdCnt[j];
        }
        vector<long long> prefix(mx + 1, 0);
        for (int g = 1; g <= mx; g++)
            prefix[g] = prefix[g - 1] + gcdCnt[g];
        vector<int> ans;
        for (long long q : queries) {
            int g = lower_bound(prefix.begin() + 1, prefix.end(), q + 1) - prefix.begin();
            ans.push_back(g);
        }
        return ans;
    }
};