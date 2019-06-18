//O(m+n)算法，精妙，没见过这个套路不容易想到
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if ( m == 0 ) return false;
        int n = matrix[0].size();
        if ( n == 0 ) return false;
        int r = 0, c = n - 1;
        while ( r < m && c >= 0 ) {
            if ( matrix[r][c] < target ) ++r;
            else if ( matrix[r][c] > target ) --c;
            else return true;
        }
        return false;
    }
};

//前一天做了LC378，有一个方法是用O(m+n)来找出小于等于某个k的数有多少个
// 这个题就可以借用这个方法，比如我要找有没有5，那我先找一下小于等于5的数有几个
// 再找一下小于等于4的有几个，如果两个数不一样，那说明5存在
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if ( matrix.empty() || matrix[0].empty() ) return false;
        return leq( matrix, target ) != leq( matrix, target - 1 );
    }
    
    int leq( vector<vector<int>>& matrix, int val ) {
        int res = 0;
        int m = matrix.size();
        int n = matrix[0].size();
        int row = 0, col = n - 1;
        while ( row < m && col >= 0 ) {
            if ( matrix[row][col] <= val ) {
                res += col + 1;
                ++row;
            } else {
                --col;
            }
        }
        return res;        
    }
};

