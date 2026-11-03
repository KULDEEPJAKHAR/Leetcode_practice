class Solution {
public:
    int minMoves(std::vector<int>& nums) {
        int max_val = *std::max_element(nums.begin(), nums.end());
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        return max_val * nums.size() - sum;
    }
};