class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        int first = -1, last = -1;

        // First occurrence
        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] >= target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }

            if (nums[mid] == target) {
                first = mid;
            }
        }

        // Last occurrence
        left = 0, right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] <= target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }

            if (nums[mid] == target) {
                last = mid;
            }
        }

        return {first, last};
    }
};
