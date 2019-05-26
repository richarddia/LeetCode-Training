// 打比赛中做这道题的时候思维有点混乱，没有理清楚总顾客数，总的unsatisfy customer数，
// 还有滑动窗口得到的最大和之间的关系. 这些数字怎么能够算出来最终我们要return的结果
// res = 永远不会受grumpy影响的顾客数 + 滑动窗口求出的最大和(不满意转换成满意的顾客数量)
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int X) {
        int n = grumpy.size();
        // free表示从来就不会被影响到的customer的数量
        int free = 0;
        for ( int i = 0; i < n; ++i ) {
            free += (1 - grumpy[i]) * customers[i];
        }
        // unblock表示在滑动窗口移动过程中，能够被解除影响的顾客数量
        int unblock = 0;
        for ( int i = 0; i < X; ++i ) unblock += grumpy[i] * customers[i];
        int maxUnblock = unblock;
        for ( int i = X; i < grumpy.size(); ++i ) {
            unblock += grumpy[i] * customers[i];
            unblock -= grumpy[i-X] * customers[i-X];
            maxUnblock = max(maxUnblock, unblock);
        }
        return free + maxUnblock;
    }
};