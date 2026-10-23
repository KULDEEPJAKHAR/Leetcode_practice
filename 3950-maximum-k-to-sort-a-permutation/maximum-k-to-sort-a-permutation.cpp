#include <vector>
#include <algorithm>

class Solution {
public:
    int sortPermutation(std::vector<int>& nums) {
        int ans = -1;
        for (int i = 0; i < nums.size(); ++i) {
            if (i != nums[i]) {
                ans &= nums[i];
            }
        }
        return std::max(ans, 0);
    }
};