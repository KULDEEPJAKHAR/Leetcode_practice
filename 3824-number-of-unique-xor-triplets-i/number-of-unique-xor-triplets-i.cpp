class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 1;
        if (n == 2) return 2;

        int k = 0;
        while ((1 << k) <= n) k++;
        return 1 << k;
    }
};