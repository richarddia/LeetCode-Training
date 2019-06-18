// 一开始想着能不能用2*log(n)从矩阵里找出小于等于某个val的值有多少个
// 试了很长时间发现不行
// [1,2]
// [1,3]


// n*log(n)*log( max - min )
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int l = matrix[0][0], r = matrix[n-1][n-1];
        while ( l + 1 < r ) {
            int mid = ( r - l ) / 2 + l;
            int num = leq( matrix, mid );
            if ( num >= k ) {
                r = mid;
            } else {
                l = mid;
            }
        }
        if ( leq( matrix, l ) < k ) return r;
        else return l;
    }
    
    int leq( vector<vector<int>>& matrix, int val ) {
        int res = 0;
        int n = matrix.size();
        int idx = 0;
        while ( idx < n ) {
            if ( matrix[idx][0] > val ) break;
            if ( matrix[idx].back() <= val ) res += n;
            else {
                int l = 0, r = n - 1;
                while ( l + 1 < r ) {
                    int mid = ( r - l ) / 2 + l;
                    if ( matrix[idx][mid] > val ) r = mid;
                    else l = mid;
                }
                if ( matrix[idx][r] <= val ) {
                    res += r + 1;
                } else if ( matrix[idx][l] <= val ) {
                    res += l + 1;
                }
            }
            ++idx;
        }
        return res;        
    }
};


//看了高票答案，进行改进
//自己还是没有把握住给的矩阵的行列单调性
//改进过后时间复杂度 2*n*log( max - min )

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int l = matrix[0][0], r = matrix[n-1][n-1];
        while ( l + 1 < r ) {
            int mid = ( r - l ) / 2 + l;
            int num = leq( matrix, mid );
            if ( num >= k ) {
                r = mid;
            } else {
                l = mid;
            }
        }
        if ( leq( matrix, l ) < k ) return r;
        else return l;
    }
    
    int leq( vector<vector<int>>& matrix, int val ) {
        int res = 0;
        int n = matrix.size();
        int row = 0, col = n - 1;
        while ( row < n && col >= 0 ) {
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


// 6/17 这道题也可以用priority_queue来做，练习一下pq的使用方法
class Solution {
    struct Tuple {
        int x, y, sum;
        Tuple ( int x, int y, int sum ) : x{x}, y{y}, sum{sum} {};
    };
    
    struct myComp {
        bool operator () ( const Tuple& lhs, const Tuple& rhs ) {
            return lhs.sum > rhs.sum;
        }
    };   
    
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<bool>> visited( m, vector<bool>( n, false) );
        priority_queue<Tuple, vector<Tuple>, myComp> pq;
        pq.push( Tuple( 0, 0, matrix[0][0] ) );
        
        for ( int i = 0; i < k - 1; ++i ) {
            Tuple cur = pq.top();
            pq.pop();
            if ( cur.x + 1 < m && visited[cur.x+1][cur.y] == false ) {
                pq.push( Tuple( cur.x + 1, cur.y, matrix[cur.x+1][cur.y] ) );
                visited[cur.x+1][cur.y] = true;
            } 
            if ( cur.y + 1 < n && visited[cur.x][cur.y+1] == false ) {
                pq.push( Tuple( cur.x, cur.y + 1, matrix[cur.x][cur.y+1] ) );
                visited[cur.x][cur.y+1] = true;
            } 
        }
        return pq.top().sum;
    }
};