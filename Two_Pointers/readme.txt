列举一些见过的two pointers的类型和套路

LintCode 1797
给两个排序的数组。 从两个数组中各取取一个数，这两个数之和需要小于或等于k， 需要找到两数之和最大的索引组合。返回一对包含两个列表的索引。如果有多个两数之和相等的索引答案，你应该选择第一个数组索引最小的索引对。
1）两数的总和<= k
2）总和是最大的
3）两个数组索引都尽量最小

class Solution {
public:
    /**
     * @param A: a integer sorted array
     * @param B: a integer sorted array
     * @param K: a integer
     * @return: return a pair of index
     */
    vector<int> optimalUtilization(vector<int> &A, vector<int> &B, int K) {
        // write your code here
        int m = A.size();
        int n = B.size();
        int pt = n - 1;
        int val = INT_MIN;
        if ( m == 0 || n == 0 || A[0] + B[0] > K ) return vector<int>();
        vector<int> res{-1, -1};
        for ( int i = 0; i < m; ++i ) {
            while ( pt >= 0 && A[i] + B[pt] > K ) --pt;
            if ( pt >= 0 && A[i] + B[pt] > val ) {
                res[0] = i;
                res[1] = pt;
                val = A[i] + B[pt];
            }
        }
        return res;
    }
};
套路: 第一个指针从前往后，第一个指针固定的时候，第二个指针从后往前，Pt2不回头