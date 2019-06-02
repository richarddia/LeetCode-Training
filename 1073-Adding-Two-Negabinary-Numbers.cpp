class Solution {
public:
    vector<int> addNegabinary(vector<int>& arr1, vector<int>& arr2) {
        // 比赛的时候做这道题也是磕磕绊绊，思维一度非常混乱，主要的问题是如果出现-1要怎么处理
        // 因为以前做过类似的题，知道大致思路是 出现了-1，要从上一位借一个 2把当前位变成1,这样上一位就
        // 当前为 -(-2)，上一位就要 + 1
        // 参考了lee215的代码后自己写一遍
        // 不是很理解lee答案中的处理进位的部分，按照自己的理解写出来的
        int pt1 = arr1.size() - 1; 
        int pt2 = arr2.size() - 1;
        int c = 0;
        int base = -2;
        vector<int> res;
        while ( pt1 >= 0 || pt2 >= 0 || c != 0 ) {
            if ( pt1 >= 0 ) c += arr1[pt1--];
            if ( pt2 >= 0 ) c += arr2[pt2--];
            int a = c % base; // 
            c /= base;
            if ( a < 0 ) {
                a -= base;
                c += 1;
            }
            res.push_back(a);            
        }
        while ( res.size() > 1 && res.back() == 0 ) res.pop_back();
        reverse(res.begin(), res.end());
        return res;
    }
};