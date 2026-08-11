class Solution {
public:
    int missingInteger(vector<int>& nums) {
        unordered_set<int> st(nums.begin(), nums.end());

        int sum = nums[0];

        // Find the longest sequential prefix
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1] + 1)
                sum += nums[i];
            else
                break;
        }

        // Find the smallest missing integer >= sum
        while (st.count(sum)) {
            sum++;
        }

        return sum;
    }
};