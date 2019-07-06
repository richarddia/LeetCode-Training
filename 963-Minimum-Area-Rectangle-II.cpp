const int c = 40001;
class Solution {
public:
    double minAreaFreeRect(vector<vector<int>>& points) {
        // 这个题看到以后首先思路不是很清晰
        // 假设用n^3来做，就是固定住三个点，计算剩下一个
        // 写起来特别恶心
        // 如果用n^4抓出4个点来还要判断是不是长方形
        // 
        int n = points.size();
        unordered_set<int> st;
        long res = LONG_MAX;
        for ( int i = 0; i < n; ++i ) st.insert(points[i][0] * c + points[i][1]);
        
        for ( int i = 0; i < n - 2; ++i ) {
            // 循环时候不用考虑三个点的出现位置，
            // 假设 a b c d可以围成一个长方形，a先出现，bcd中有两个点是a的相邻点
            // 假设b和d是a的相邻点，那么abd/adb一定有一个会被循环到
            int a0 = points[i][0];
            int a1 = points[i][1];
            for ( int j = i + 1; j < n - 1; ++j ) {
                int b0 = points[j][0];
                int b1 = points[j][1];
                for ( int k = j + 1; k < n; ++k ) {
                    int c0 = points[k][0];
                    int c1 = points[k][1];
                    //ab = (b0 - a0, b1 - a1);
                    //ac = (c0 - a0, c1 - a1);
                    if ((b0 - a0) * (c0 - a0) + (b1 - a1) * (c1 - a1) == 0 ) {
                        // 在满足向量ab和ac的内积为0的条件下
                        // ab ac垂直, 
                        // 假设d是最后一个点
                        // d要满足条件 向量bd和ac相等
                        // bd = (d0 - b0, d1 - b1);
                        // ac = (c0 - a0, c1 - a1);
                        int d0 = c0 - a0 + b0;
                        int d1 = c1 - a1 + b1;
                        long len_ab_sq = (b0 - a0) * (b0 - a0) + (b1 - a1) * (b1 - a1);
                        long len_ac_sq = (c0 - a0) * (c0 - a0) + (c1 - a1) * (c1 - a1);
                        long candidate = len_ab_sq * len_ac_sq;
                        // 然后我们再来看d在不在hash set内
                        if ( candidate < res && st.find(d0 * c + d1) != st.end() ) {
                            res = candidate;
                        }
                    }
                }
            }
        }
        
        if ( res == LONG_MAX ) return 0.0;
        else return sqrt(res);
    }
};