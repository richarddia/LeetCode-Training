// 6月24和25两天都是练习滑动窗口求Median
// 295和480本质上是一道题，480稍微更难一些。
// 295可以使用pq,map,multiset来做,480可以用map或者multiset,
// 对480而言pq不是很理想的选择因为删除非队头的元素复杂度是o(n)
// 通过这两道题，学习c++里面multiset怎么用
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> res;
        int n = nums.size();
        multiset<int> set;
        for ( int i = 0; i < k; ++i ) set.insert( nums[i] );
        auto it = next(set.begin(), ( k - 1 ) / 2);
        res.push_back( ( (double)*it + (double)*next(it, k%2 == 0 ) ) / 2.0  );
        int m;
        for ( int i = k; i < n; ++i ) {
            // insert默认插入到最后一个满足条件的位置
            set.insert(nums[i]);
            // 这个地方太牛逼了，巧妙用相对位置避开了it自己被删除的尴尬局面
            if (nums[i]<*it) it--;
            if (nums[i-k]<=*it)it++;
            set.erase(set.lower_bound(nums[i-k]));
            res.push_back( ( (double)*it + (double)*next(it, k%2 == 0 ) ) / 2.0  );
        }
        return res;
    }
};
// 原来是偶数个，插入在左边
// XXXXXX
//   P
// OXXXXXX
//   P
// 这种情况
// XXXXX
//   p
// OXXXXX
//   p

// 295 multiset
class MedianFinder {
    multiset<int> set;
    multiset<int>::iterator it;
public:
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if ( set.size() == 0 ) {
            set.insert( num );
            it = set.begin();
        } else {
            int n = set.size();
            set.insert( num );
            // 偶数个右插入,it右移一位
            if ( n % 2 == 0 && num >= *it ) {
                it = next( it, 1 );
            }            
            // 奇数个左插入,it左移一位
            if ( n % 2 == 1 && num < *it ) {
                it = prev( it, 1 );
            }
        }
    }
    
    double findMedian() {
        int n = set.size();
        if ( n % 2 == 1 ) {
            return (double) *it;
        } else {
            return ( (double) *it + (double) *next(it, 1) ) / 2.0;
        }
    }
};

// 295还可以用pq来做，这道题数字是只进不出，所以不存在pq删除某个元素的情况
class MedianFinder {
    priority_queue<int> lo;
    priority_queue<int, vector<int>, greater<int>> hi;
    int n;
public:
    /** initialize your data structure here. */
    MedianFinder() {
        n = 0;
    }
    
    void addNum(int num) {
        // 先过一遍lo，再过一遍hi，最后平衡lo和hi的个数
        lo.push( num );
        hi.push( lo.top() );
        lo.pop();
        if ( lo.size() < hi.size() ) {
            lo.push( hi.top() );
            hi.pop();
        }
        ++n;
    }
    
    double findMedian() {
        if ( n & 0x01 ) return (double) lo.top();
        else return ( hi.top() - lo.top() ) / 2.0 + lo.top();
    }
};

