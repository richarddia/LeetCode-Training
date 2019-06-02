class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        // 比赛的时候把这个题想难了，用了union find，杀鸡用了宰牛刀
        // 如果两行数字能通过翻动列元素变成一行全0或者全1，那么这两行要么一样，要么互补
        // 而互补的通过行翻转可以变成一模一样的，如果两行A，B互补(A[i] + B[i] = 1)，那么A行翻转一定是B
        // 用Hash就足够了，不需要Union Find
        
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> root(m, 0);
        unordered_map<string, int> mp;
        int res = 0;
        for ( auto& row : matrix ) {
            string s = convertRow( row );
            res = max( res, ++mp[s] );
        }
        return res;
    }
    
    string convertRow( vector<int>& row ) {
        string ret;
        bool flag = row[0];
        for ( auto& x : row ) {
            ret.push_back( '0' + ( flag ? 1 - x : x ) );
        }
        return ret;
    }
};

