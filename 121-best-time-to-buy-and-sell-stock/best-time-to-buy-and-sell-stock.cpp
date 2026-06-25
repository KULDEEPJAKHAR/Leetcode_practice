class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxprofit = 0;
        int buy = 0;
        for(int j = 1;j<prices.size();j++){
            int profit = 0;
            if(prices[buy]>prices[j]){
                buy = j;
            }
            profit = prices[j]-prices[buy];
            maxprofit = max(profit,maxprofit);
        }
        return maxprofit;
;        
    }
};