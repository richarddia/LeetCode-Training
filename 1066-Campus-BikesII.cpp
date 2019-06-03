class Solution {
public:
    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        int m = workers.size();
        int n = bikes.size();
        // dp[i][j]表示前i个worker挑选j里面bit 1的出现的位置上的那些bike时能得到的最好曼哈顿距离
        // j里面1的个数必须大于等于i否则没有意义
        // 比赛中这个题束手无策，看到workers.length <= 10 ，抱着侥幸心理写了一个暴力搜索，不出意外TLE
        // 也有想过要用动态规划，想不出来用什么来表示状态，更别说状态转移方程了
        // 想到了要用bitmap来表示状态，但是输入有两个数组，bitmap哪一个呢，又陷入被动
        // 当做一个套路学习一下吧，
        int dp[m+1][1<<n];
        memset(dp[0], 0, sizeof(dp[0]));
        for ( int i = 1; i <= m; ++i ) {
            for ( int j = 0; j < (1 << n); ++j ) {
                if ( countBit(j) < i ) continue; // 第一次run的时候这里写成了 coutBit(j) != i,其实只要大于等于i都可以
                dp[i][j] = INT_MAX;
                for ( int b = 0; b < n; ++b ) {
                    if ( ( (1 << b) & j ) != 0 ) {
                        dp[i][j] = min(dp[i][j], dp[i-1][j - (1 << b)] + 
                                abs(workers[i-1][0] - bikes[b][0]) + abs(workers[i-1][1] - bikes[b][1]));                            
                    }
                }
                
            }
        }
        return dp[m][(1<<n)-1];
    }
    
    int countBit(int n) {
        int ret = 0;
        while ( n != 0 ) {
            ret ++;
            n = n & ( n - 1 );
        }
        return ret;
    }
};