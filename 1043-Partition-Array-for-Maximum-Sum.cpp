class Solution {
public:
    // 这个题当时在比赛的时候浪费了很多时间在数组index计算上，后面想明白一个地方就行，
    // 循环j的时候加一个限制条件 i - j + 1 <= K
    // 设计dp个数的时候，dp[n]或者dp[n+1]其实都可以
    // 如果设计成dp[n]，那就要在做j循环的时候考虑一下j为0怎么办
    // j 如果是 0，那就不能写dp[j-1]
    // 如果设计成dp[n+1]就不用考虑这个问题，j最小是1，dp[i]的含义略有不同，这时候dp[i]表示前i个数能做出的最大结果
    int maxSumAfterPartitioning(vector<int>& A, int K) {
        int n = A.size();
        int dp[n];
        memset(dp, 0, sizeof(dp));
        for ( int i = 0; i < n; ++i ) {
            int m = 0;
            for ( int j = i; j >= 0 && i - j + 1 <= K; --j ) {
                m = max(m, A[j]);
                dp[i] = max(dp[i], m * (i - j + 1) + (j == 0 ? 0 : dp[j - 1]));
            }
        }
        return dp[n - 1];
    }
    // dp[n + 1]
    int maxSumAfterPartitioning(vector<int>& A, int K) {
        int n = A.size();
        int dp[n + 1];
        memset(dp, 0, sizeof(dp));
        for ( int i = 1; i <= n; ++i ) {
            
            int m = 0;
            for ( int j = i; i - j + 1 <= K && j > 0; --j ) {
                m = max(m, A[j - 1]);
                dp[i] = max(dp[i], dp[j-1] + m * (i - j + 1));
            }
        }
        return dp[n];
    }
};