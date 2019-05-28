class Solution {
public:
    int knightDialer(int N) {
        // 其实这个题挺无聊的，状态转移方程本质上是手动构造的。
        // 了解一下思路就可以了
        vector<vector<int>> list{{4, 6}, {6, 8}, {7, 9}, {4, 8}, {0, 3, 9}, {}, {0, 1, 7}, {2, 6}, {1, 3}, {2, 4}};
        int mod = 1e9 + 7;
        vector<int> dp(10, 1);
        vector<int> next(10, 0);
        for ( int i = 1; i < N; ++i ) {
            for ( int j = 0; j < 10; ++j ) {
                next[j] = 0;
                for ( auto& x : list[j] ) {
                    next[j] += dp[x];
                    next[j] %= mod;
                }
            }
            dp = next;
        }
        int res = 0;
        for ( auto& x : dp ) {
            res += x;
            res %= mod;
        }
        return res;
    }
};