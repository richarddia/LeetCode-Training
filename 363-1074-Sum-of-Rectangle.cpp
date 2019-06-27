// 几次遇到这种二维矩阵里求sum的问题，正好总结一些套路
// 第一种套路是先对矩阵在一个方向上求累加和，这里我们选择对每一行从左到右求累加和
// 然后卡住任意两列，再从上到下走一遍，复杂度是O(n*n*m*logm)，如果交换维度，复杂度可以是O(m*m*n*logn)

// 363
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int m = matrix.size();
        int n = matrix[0].size();
        for ( int i = 0; i < m; ++i ) {
            for ( int j = 1; j < n; ++j ) {
                matrix[i][j] += matrix[i][j-1];
            }
        }
        set<int> st;
        int sum;
        int res = INT_MIN;
        for ( int i = 0; i < n; ++i ) {
            for ( int j = i; j < n; ++j ) {
                st.clear();
                st.insert( 0 );
                sum = 0;
                for ( int l = 0; l < m; ++l ) {
                    sum += matrix[l][j] - ( i == 0 ? 0 : matrix[l][i-1] );
                    // 要找出一个x,使得sum - x <= k, x越小越好
                    // x >= sum - k
                    auto it = st.lower_bound( sum - k );
                    if ( it != st.end() ) {
                        res = max( res, sum - *it );
                        if ( res == k ) return k; 
                    }
                    st.insert( sum );
                }
            }
        }
        return res;
    }
};

// 1074 与363的区别就在于用了unordered_map
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(); int n = matrix[0].size();
        for ( int i = 0; i < m; ++i ) {
            for ( int j = 1; j < n; ++j ) {
                matrix[i][j] += matrix[i][j-1];
            }
        }
        int res = 0;
        int sum = 0;
        unordered_map<int, int> mp;
        for ( int i = 0; i < n; ++i ) {
            for ( int j = i; j < n; ++j ) {
                sum = 0;
                mp.clear(); 
                mp[0] = 1;
                for ( int k = 0; k < m; ++k ) {
                    sum += matrix[k][j] - ( i == 0 ? 0 : matrix[k][i-1] );
                    res += mp[sum - target];
                    ++mp[sum];
                }
            }
        }
        return res;
    }
};

//上面这个套路是先求presum然后再上presum矩阵进行操作
//另外一个套路是一遍走一遍求，本质上是一样的，这个套路还适用于LC 85
// 363 再来一遍
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int m = matrix.size();
        int n = matrix[0].size();
        set<int> st;
        int sum;
        int res = INT_MIN;
        int arr[m];
        for ( int j1 = 0; j1 < n; ++j1 ) {
            memset( arr, 0, sizeof( arr ) );
            for ( int j2 = j1; j2 < n; ++j2 ) {
                int sum = 0;
                st.clear();
                st.insert( 0 );
                for ( int l = 0; l < m; ++l ) {
                    arr[l] += matrix[l][j2];
                    sum += arr[l];
                    // sum - x <= k
                    auto it = st.lower_bound( sum - k );
                    if ( it != st.end() ) {
                        res = max( res, sum - *it );
                        if ( res == k ) return res;
                    }
                    st.insert( sum );
                }
            }
        }
        return res;
    }
};

// 1074 再来一遍
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(); int n = matrix[0].size();
        int res = 0;
        int sum = 0;
        unordered_map<int, int> mp;
        int arr[m];
        for ( int i1 = 0; i1 < n; ++i1 ) {
            memset( arr, 0, sizeof( arr ) );
            for ( int i2 = i1; i2 < n; ++i2 ) {
                sum = 0;
                mp.clear(); 
                mp[0] = 1;
                for ( int k = 0; k < m; ++k ) {
                    arr[k] += matrix[k][i2];
                    sum += arr[k];
                    res += mp[sum - target];
                    ++mp[sum];
                }
            }
        }
        return res;
    }
};

// 仔细分析了cuiaoxiang的代码以后，自己尝试加一个cache
const int M = 600000 + 10;
int cache[M];
int timeStamp[M];
int OFFSET = M / 2;

class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(); int n = matrix[0].size();
        int res = 0;
        int sum = 0;
        unordered_map<int, int> mp;
        int arr[m];
        int step = 1;
        memset( timeStamp, 0, sizeof( timeStamp ) );
        for ( int i1 = 0; i1 < n; ++i1 ) {
            memset( arr, 0, sizeof( arr ) );
            for ( int i2 = i1; i2 < n; ++i2 ) {
                sum = 0;
                mp.clear(); 
                cache[0 + OFFSET] = 1;
                timeStamp[0 + OFFSET] = step;
                for ( int k = 0; k < m; ++k ) {
                    arr[k] += matrix[k][i2];
                    sum += arr[k];
                    int key = sum - target + OFFSET;
                    if ( key >= 0 && key < M ) {
                        if ( timeStamp[key] == step ) res += cache[key];
                    } else {
                        res += mp[key];
                    }
                    
                    int key2 = sum + OFFSET;
                    if ( key2 >= 0 && key2 < M ) {
                        if ( timeStamp[key2] == step ) {
                            ++cache[key2];
                        } else {
                            timeStamp[key2] = step;
                            cache[key2] = 1;
                        }
                    } else {
                        ++mp[key2];
                    }
                }
                ++step;
            }
        }
        return res;
    }
};



