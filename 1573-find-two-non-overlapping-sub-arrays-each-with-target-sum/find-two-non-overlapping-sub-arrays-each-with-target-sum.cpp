class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        

int n = arr.size();
        const int INF = 1e9;
        vector<int> best(n, INF);

        int l = 0, sum = 0, ans = INF;
        int minLen = INF;

        for (int r = 0; r < n; r++) {
            sum += arr[r];

            while (sum > target) {
                sum -= arr[l++];
            }

            if (sum == target) {
                int len = r - l + 1;

                if (l > 0 && best[l - 1] != INF)
                    ans = min(ans, len + best[l - 1]);

                minLen = min(minLen, len);
            }

            best[r] = minLen;
        }

        return ans == INF ? -1 : ans;
   







    }
};