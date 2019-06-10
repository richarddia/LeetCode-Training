class Solution {
public:
    int numSquares(int n) {
        // dp[i]表示数字i最少可以由几个完全平方数构成
        // 时间复杂度O(n^(3/2))
        // 空间复杂度O(n)
        int dp[n+1];
        dp[0] = 0;
        for ( int i = 1; i <= n; ++i ) {
            dp[i] = i;
            for ( int j = 1; j * j <= i; ++j ) {
                dp[i] = min( dp[i], 1 + dp[i - j * j] );
            }
        }
        return dp[n];
    }
};