class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MIN));
        // dp[i][j][k]表示第一个点走到(k-i,i)以及第二个点走到(k-j,j)时候
        // 能带来的最大收益
        // 本质上相当于dp[k-i][i][k-j][j]
        dp[0][0] = grid[0][0];
        for ( int step = 1; step <= (n - 1) + (n - 1); ++step ) {
            vector<vector<int>> next(n, vector<int>(n, INT_MIN));
            // dp[r1][c1][r2][c2]
            // r1 + c1 = step;
            // c1 >= 0 
            // c1 <= n - 1
            // 解一下不等式 得到 c1 >= max(0, step - (n - 1)) 并且 c1 <= min(step, n - 1)
            // 同理 c2 也是这个范围
            for ( int i = max(0, step - (n - 1)); i <= min(step, n - 1); ++i ) {
                for ( int j =i; j <= min(step, n - 1); ++j ) {
                    if ( grid[step - i][i] == -1 || grid[step - j][j] == -1 ) continue;
                    // next[r1][c1][r2][c2] = dp[r1-1][c1][r2-1][c2];
                    // next[r1][c1][r2][c2] = dp[r1-1][c1][r2][c2-1];
                    // next[r1][c1][r2][c2] = dp[r1][c1-1][r2-1][c2];
                    // next[r1][c1][r2][c2] = dp[r1][c1-1][r2][c2-1];
                    if ( dp[i][j] >= 0 ) next[i][j] = dp[i][j];
                    if ( j - 1 >= 0 && dp[i][j-1] >= 0 ) next[i][j] = max(next[i][j], dp[i][j-1]);
                    if ( i - 1 >= 0 && dp[i-1][j] >= 0 ) next[i][j] = max(next[i][j], dp[i-1][j]);
                    if ( i - 1 >= 0 && j - 1 >= 0 && dp[i-1][j-1] >= 0 ) next[i][j] = max(next[i][j], dp[i-1][j-1]);
                    if ( next[i][j] >= 0 ) next[i][j] += grid[step-i][i] + grid[step-j][j] - ( i == j ? grid[step-i][i] : 0 );
                }
            }
            dp = next;
        }
        return max(0, dp[n-1][n-1]);
    }
};