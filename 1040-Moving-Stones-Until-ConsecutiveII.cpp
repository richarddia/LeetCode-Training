// 这道题思路上算一个比较难的题，求max用到了贪婪算法，求min又用到了滑动窗口
class Solution {
public:
    vector<int> numMovesStonesII(vector<int>& stones) {
        int n = stones.size();
        sort(stones.begin(), stones.end());
        // X   X        X     X                X
        //     |                               | 这一段中的的空隙
        // |                  |                  或者这一段的空隙
        vector<int> res(2, INT_MAX);
        res[1] = max(stones[n-1] - stones[1] + 1 - ( n - 1 ), 
                     stones[n-2] - stones[0] + 1 - ( n - 1) );
        int pt = 0;
        for ( int i = 0; i < n; ++i ) {
            while ( stones[i] - stones[pt] + 1 > n ) ++pt;
            // 在以stones[i]为结尾并且长度为n的窗口里有cnt个数字
            // 相应就有n - cnt个空缺，这些空缺就需要窗口以外的数字来补上
            int cnt = i - pt + 1;
            if ( cnt == n ) {
                res[0] = 0;
                break;
            } else if ( cnt == n - 1 && stones[i] - stones[pt] + 1 == n - 1 ) {
                // 特殊情况 XXXX           X
                res[0] = min(res[0], 2);
            } else {
                res[0] = min(res[0], n - cnt);
            }
        }
        return res;
    }
};