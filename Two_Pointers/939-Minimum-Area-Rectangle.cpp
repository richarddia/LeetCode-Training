// 这道题虽然不难但是还有一些值得学习的点
// 首先是思路上 面对点来组成长方形，要抓对角线上两个点 diagnal scan 
// 其次是代码实现上
// 1. x,y都是0到40000内的数字，通过x*400001 + y可以映射成一个int，而我的第一版代码中用的是x*1e5 + y
// 2. 相对于数值计算而言，st.find更费时一些，所以我们可以提前算一下candidate的值，如果比res大就不进行
//    set内的find操作了，可以节约一些时间

// 第一版代码
class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        int n = points.size();
        unordered_set<long> st;
        const long c = 1e5;
        for ( auto& x : points ) {
            st.insert(x[0] * c + x[1]);
        }
        int res = INT_MAX;
        for ( int i = 0; i < n; ++i ) {
            for ( int j = i + 1; j < n; ++j ) {
                if ( points[i][0] == points[j][0] || points[i][1] == points[j][1] ) continue;
                if ( st.find(points[i][0]*c + points[j][1]) != st.end() && 
                     st.find(points[j][0]*c + points[i][1]) != st.end() ) {
                    res = min(res, abs(points[i][0] - points[j][0]) * abs(points[i][1] - points[j][1]));
                }
            }
        }
        if ( res == INT_MAX ) return 0;
        else return res;
    }
};

// 第二版代码

class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        int n = points.size();
        unordered_set<int> st;
        const int c = 40001;
        for ( auto& x : points ) {
            st.insert(x[0] * c + x[1]);
        }
        int res = INT_MAX;
        for ( int i = 0; i < n; ++i ) {
            for ( int j = i + 1; j < n; ++j ) {
                int candidate = abs((points[i][0] - points[j][0]) * (points[i][1] - points[j][1]));
                if ( candidate == 0 || candidate >= res ) continue;
                if ( st.find(points[i][0]*c + points[j][1]) != st.end() && 
                     st.find(points[j][0]*c + points[i][1]) != st.end() ) {
                    res = candidate;
                }
            }
        }
        if ( res == INT_MAX ) return 0;
        else return res;
    }
};