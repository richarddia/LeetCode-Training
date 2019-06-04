class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        int res = 0;
        // 状态转移不难，反而是这个大k的单独处理会提升很多速度
        if ( k >= n/2 ) {
            for ( int i = 1; i < n; ++i ) {
                res += max(0, prices[i]-prices[i-1]);
            }
            return res;
        }
        // dp[k][0] 表示第k次交易买入状态
        // dp[k][0] 表示第k次交易卖出状态
        vector<vector<int>> dp(k+1, vector<int>(2, INT_MIN/2));
        dp[0][0] = 0; dp[0][1] = 0;        
        for ( int i = 0; i < n; ++i ) {
            for ( int j = k; j >= 1; --j ) {
                dp[j][1] = max(dp[j][1], dp[j][0] + prices[i]);
                dp[j][0] = max(dp[j][0], dp[j-1][1] - prices[i]);    
            }
        }
        for ( int i = 0; i <= k; ++i ) {
            res = max(res, dp[i][0]);
            res = max(res, dp[i][1]);
        }
        return res;
    }
};