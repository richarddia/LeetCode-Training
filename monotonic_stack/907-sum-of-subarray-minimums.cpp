// 这道题容易想到用单调栈
// 难点在于怎么处理数字相等的问题，扣边界烦死人
// 比如 2 2 2 2 2 2 怎么能保证不漏算，重算
// 解决的方法是左开右闭，或者左闭右开
// 比如 1 2 2 3 2 ，以第二个数字为例， 左边找到比2严格小的第一个数字，就是1所在的位置0，右边找到第一个小于等于2的数字，就是最后一个2
class Solution {
public:
    int sumSubarrayMins(vector<int>& A) {
        A.push_back(0);
        int n = A.size();
        stack<int> stk;
        int res = 0;
        const int mod = 1e9 + 7;
        for ( int i = 0; i < n; ++i ) {
            while ( !stk.empty() && A[i] <= A[stk.top()] ) { //这里 用 <=  或者< 都可以
                int j = stk.top();
                stk.pop();
                int l = stk.empty() ? -1 : stk.top();
                res += A[j] * ( j - l ) * ( i - j ) % mod;
                res %= mod;
            }
            stk.push(i);
        }
        A.pop_back();
        return res;
    }
};