// map方法
class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();
        if ( n < 3 ) return false;
        map<int, int> mp;
        for ( int i = 1; i < n; ++i ) {
            ++mp[nums[i]];
        }
        int minVal = nums[0];
        for ( int i = 1; i < n - 1; ++i ) {
            if ( --mp[nums[i]] == 0 ) {
                mp.erase( nums[i] );
            }
            auto itup = mp.upper_bound ( minVal );
            if ( nums[i] > minVal && itup != mp.end() &&  itup -> first < nums[i] ) return true;
            minVal = min( minVal, nums[i] );
        }
        return false;
    }
};


// 单调栈
// 核心思路: 从后往前遍历，当前的数字作为1，如果当前数字小于third，那几说明找到了
// 出栈过程: nums[i]只弹出小于自己的数字，因为栈里面的元素会呈单调不减(从栈底到栈顶)，所以弹出的数字会越来
// 越大，至少不会降低，所以从全局来看third的值只增不减，如果third降了，那说明pattern找到了
class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();
        if ( n < 3 ) return false;
        stack<int> st;
        // third表示第三个数
        int third = INT_MIN;
        
        for ( int i = n - 1; i >= 0; --i ) {
            if ( nums[i] < third ) return true;
            while ( !st.empty() && nums[i] > st.top() ) {
                third = st.top();
                st.pop();
            }
            st.push( nums[i] );
        }
        return false;
    }
};