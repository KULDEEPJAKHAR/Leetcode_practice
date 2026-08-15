class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size();

        int xr = 0;
        bool hasNonZero = false;

        for (int x : nums) {
            xr ^= x;
            if (x != 0) hasNonZero = true;
        }

      
        if (xr != 0)
            return n;

        // Total XOR is zero.
        // Remove one non-zero element to make the XOR non-zero.
        if (hasNonZero)
            return n - 1;

        // All elements are zero, so no non-empty subsequence works.
        return 0;
    }
};