class Solution {
public:
    int checkRecord(int n) {
        // 动态规划
        // 符合条件的序列有4种情况 有没有A，结尾是不是L
        // dp[i][k]表示长i天的record符合情况k的有多少
        // k = 0  无A,结尾也不是L
        // k = 1  无A,结尾1个L
        // k = 2  无A,结尾2个L
        // k = 3  有A,结尾不是L
        // k = 4  有A,结尾1个L
        // k = 5  有A,结尾2个L
        // dp[i][x]之和dp[i-1][x]有关，所以可以压缩状态为dp[4]
        int mod = 1e9 + 7;
        // vector<int> dp{1, 1, 0, 1, 0, 0};
        int dp[] = {1, 1, 0, 1, 0, 0};
        int cur[6];
        for ( int i = 2; i <= n; ++i ) {
            memset(cur, 0, sizeof(cur));
            // case0 + L -> case1
            cur[1] = ( cur[1] + dp[0] ) % mod;
            // case0 + A -> case3
            cur[3] = ( cur[3] + dp[0] ) % mod;
            // case0 + P -> case0
            cur[0] = ( cur[0] + dp[0] ) % mod;
            
            // case1 + L -> case2
            cur[2] = ( cur[2] + dp[1] ) % mod;
            // case1 + P -> case0
            cur[0] = ( cur[0] + dp[1] ) % mod;
            // case1 + A -> case3
            cur[3] = ( cur[3] + dp[1] ) % mod;
            
            // case2 + L -> not possible
            // case2 + P -> case0
            cur[0] = ( cur[0] + dp[2] ) % mod;
            // case2 + A -> case3
            cur[3] = ( cur[3] + dp[2] ) % mod;
            
            // case3 + L -> case4
            cur[4] = ( cur[4] + dp[3] ) % mod;
            // case3 + P -> case3
            cur[3] = ( cur[3] + dp[3] ) % mod;
            // case3 + A -> not possible
            
            // case4 + L -> case5
            cur[5] = ( cur[5] + dp[4] ) % mod;
            // case4 + P -> case3
            cur[3] = ( cur[3] + dp[4] ) % mod;
            // case4 + A -> not possible
            
            // case5 + L -> not possible
            // case5 + P -> case3
            cur[3] = ( cur[3] + dp[5] ) % mod;
            // case5 + A -> not possible
            for ( int j = 0; j < 6; ++j ) dp[j] = cur[j];
        }
        int res = 0;
        for ( int i = 0; i < 6; ++i ) {
            res += dp[i];
            res %= mod;
        }
        return res;
    }
};