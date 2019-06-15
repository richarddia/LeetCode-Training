//这个题目两种解法，比较直观的解法是用map，滑动窗口更新map里面的内容，然后输出map中最大的Key即可
//第二种是使用deque，原理类似单调栈，从滑动窗口左侧移出的点可以从deque左侧移出。

//map
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
		map<int, int> mp;
		for ( int i = 0; i < nums.size(); ++i ) {
			int x = nums[i];
			++mp[x];
			if ( i >= k ) {
				if ( --mp[nums[i-k]] == 0 ) mp.erase( nums[i-k] );
			}
			if ( i >= k - 1 ) res.push_back( mp.rbegin() -> first );
		}
		return res;
    }
};

//deque
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
		deque<int> dq;		
		for ( int i = 0; i < nums.size(); ++i ) {
			while ( !dq.empty() && nums[i] > dq.back() ) dq.pop_back();
			dq.push_back( nums[i] );
			if ( i >= k && nums[i-k] == dq.front() ) dq.pop_front();
			if ( i >= k - 1 ) res.push_back( dq.front() );
		}
		return res;
    }
};

// 补充一个解法，感谢haitao7提供idea

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        // 膜 haitao7
        // 思路:k个数字为一个区间，对每一个区间求premax和postmax
        // [1,3,-1,-3,5,3,6,7]
        //    <-  |->
        //    post|pre
        
        int n = nums.size();
        vector<int> res;
        if ( n == 0 ) return res;
        vector<int> premax( n, 0 );
        vector<int> postmax( n, 0 );
        for ( int i = 0; i < n; ++i ) {
            if ( i % k == 0 ) premax[i] = nums[i];
            else premax[i] = max( premax[i-1], nums[i] );
        }
        postmax[n-1] = nums[n-1];
        for ( int i = n - 2; i >= 0; --i ) {
            if ( i % k == k - 1 ) postmax[i] = nums[i];
            else postmax[i] = max( postmax[i+1], nums[i] );
        }
        int pt1 = 0; int pt2 = k - 1;
        
        while ( pt2 < n ) {
            res.push_back( max( postmax[pt1], premax[pt2] ) );
            ++pt1;
            ++pt2;
        }
        return res;
    }
};
