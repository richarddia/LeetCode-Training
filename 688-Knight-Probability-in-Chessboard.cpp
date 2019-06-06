int dir[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2} };
class Solution {
public:
    double knightProbability(int N, int K, int r, int c) {
        // 打卡题
        // 我发现我居然看不懂我之前提交的java了，感觉当时的想法好诡异
        
        double dp[N][N];
        memset(dp, 0, sizeof(dp));
        double dpNext[N][N];
        dp[r][c] = 1.0;
        
        for ( int k = 0; k < K; ++k ) {
            memset(dpNext, 0, sizeof(dpNext));
            for ( int i = 0; i < N; ++i ) {
                for ( int j = 0; j < N; ++j ) {
                    if (dp[i][j] == 0.0) continue;
                    for ( int l = 0; l < 8; ++l ) {
                        int x = i + dir[l][0]; int y = j + dir[l][1];
                        if ( x >= 0 && x < N && y >= 0 && y < N ) {
                            dpNext[x][y] += dp[i][j]/8.0;
                        }
                    }
                }
            }
            for ( int  i = 0; i < N; ++i ) {
                for ( int j = 0; j < N; ++j ) {
                    dp[i][j] = dpNext[i][j];
                }
            }
        }
        double res = 0.0;
        for ( int  i = 0; i < N; ++i ) {
            for ( int j = 0; j < N; ++j ) {
                res += dp[i][j];
            }
        }
        return res;
    }
};