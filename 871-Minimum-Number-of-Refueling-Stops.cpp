// 这题很难，不太容易想到
// 两种方法都是看过答案后自己写的

// 动态规划o(n2)
class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int n = stations.size();
        long dp[n+1][n+1];
        memset(dp, 0, sizeof(dp));
        // dp[i][j]表示前i个stop里面停j次最多可以走多远
        // dp[i][0] = startFuel;
        // dp[i][j] = dp[i-1][j];
        // dp[i][j] = dp[i-1][j-1] + stations[i-1][1]; if (dp[i-1][j-1] >= stations[i-1][0])
        
        for ( int i = 0; i <= n; ++i ) dp[i][0] = startFuel;
        for ( int i = 1; i <= n; ++i ) {
            for ( int j = 1; j <= i; ++j ) {
                if ( i - 1 >= j ) {
                    dp[i][j] = max(dp[i][j], dp[i-1][j] );
                }
                if ( dp[i-1][j-1] >= stations[i-1][0] ) {
                    dp[i][j] = max(dp[i][j], dp[i-1][j-1] + stations[i-1][1]);
                }
            }
        }
        for ( int j = 0; j <= n; ++j ) {
            if ( dp[n][j] >= target ) return j;
        }
        return -1;
    }
};

class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        // 思路：贪婪算法，先用当前的油量尽量往前走，沿途经过的加油站都是可以选择停留的，但是先不着急选在哪个加油站停
        // 等到走不动的时候，回过头来，在备选的加油站中选择哪个加油量最多的，加好油继续走..沿途再把经过的加油站作为候选
        // 一直这么走下去
        // 如果把沿途所有能停留加油站都加了一遍还是走不到下一个加油站或者走不到target，那就GG
        int n = stations.size();
        priority_queue<int> pq;
        pq.push(0);
        int curDist = startFuel;
        int res = 0;
        int pt = 0;
        while ( !pq.empty() ) {
            if ( curDist >= target ) return res;
            while ( pt < n && curDist >= stations[pt][0] ) pq.push(stations[pt++][1]);
            curDist += pq.top();
            pq.pop();
            ++res;
        }
        return -1;
    }
};
