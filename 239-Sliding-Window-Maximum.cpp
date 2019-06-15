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