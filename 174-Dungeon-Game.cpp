class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        // dp[i][j] 表示保证从i,j走到P需要的最少分数
        int m = dungeon.size();
        int n = dungeon[0].size();
        int dp[m][n];
        memset(dp, 0, sizeof(dp));
        
        dp[m-1][n-1] = max(1, 1 - dungeon[m-1][n-1]);
        // dp[i][j] = dp[i+1][j]  dp[i][j+1]
        for ( int i = m-1; i >= 0; --i ) {
            for ( int j = n-1; j >= 0; --j ) {
                if( i == m-1 && j == n-1 ) continue;
                dp[i][j] = INT_MAX/2;
                if ( i+1 < m ) dp[i][j] = min(dp[i][j], max(1, dp[i+1][j]-dungeon[i][j]));
                if ( j+1 < n ) dp[i][j] = min(dp[i][j], max(1, dp[i][j+1]-dungeon[i][j]));
            }
        }
        return dp[0][0];
    }
};