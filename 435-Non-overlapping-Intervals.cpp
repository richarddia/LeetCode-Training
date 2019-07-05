class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        // 这个题上来就没什么思路，感觉一团乱，如果按照start排序，也不确定要删除哪个要留下哪个
        // 又觉得像是个动态规划
        // 还是想想贪心
        // 按照end从小到大排序
        // [1,2] [1,3] [2,3] [3,4]
        // 如果两个interval有重叠了，只能留一个，那么肯定留下end小的那一个，这样对后续
        // 其他元素的影响会降低
        int n = intervals.size();
        if ( n <= 1 ) return 0;
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b){
            return a[1] < b[1];
        });
        int res = 0;
        int last = intervals[0][1];
        for ( int i = 1; i < n; ++i ) {
            if ( intervals[i][0] < last ) {
                ++res;
            } else {
                last = intervals[i][1];
            }
        }
        return res;
    }
};