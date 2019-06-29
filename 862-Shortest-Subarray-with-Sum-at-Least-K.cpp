class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
        // 这个题上一次做的时候就没做出来，之前就应该是抄答案的
        // 一开始试着用了一个简单的滑动窗口，自己也知道多半是错的，还是硬着头皮试了一下
        // 结果当然是不出意外地出错了，原因是负数的存在影响到了presum的单调性
        // 这个题对原数组求了presum之后就变成了在presum数组中求出满足这个条件presum[i] - presum[j] >= k 的j，并且要让
        // i - j尽量小，输出最小的那个i-j的值
        
        // 我一开始尝试使用一个map来做，但是出了一个问题，我可以找到满足 x <= presum[i] - k，但是这样的x不止一个
        // 我还要在所有满足条件的x构成的集合{x}里面找出其中某个x让它的位置距离i最近，通过把比当前sum大的数字都弹出去
        // 那下一次如果有要搜索比当前sum大的数字，也会搜索到当前的sum
        
        // 考虑一下用stack或者deque来做
        // 我们希望当前的sum尽量小，这样可以为后面的数字创造更多机会，如果前面有个数字比当前sum还大，那我们肯定不要
        // 这个数字，当前数完全可以取代前一个数的功能，(假如某个x-presum[i-1] >= K, 那么x-presum[i] 一定也>= K)
        // 而且i还更靠后，得到的长度更短，因此我们可以直接把那些前面出现的比i大的数字踢出去，这样就形成了单调递增栈
        // 
        
        
        int n = A.size();
        int res = n + 1;
        map<int, int> mp; // mp[i]存的是 小于等于i的这些数字中的最大index
        mp[0] = -1;
        int sum = 0;
        for ( int i = 0; i < n; ++i ) {
            sum += A[i];
            auto it = mp.upper_bound( sum - K );
            if ( it != mp.begin() ) {
                --it;
                res = min( res, i - it -> second );
            }
            
            it = mp.lower_bound( sum );
            while( it != mp.end() ) {
                mp.erase( it );
                it = mp.upper_bound( sum );
            }
            mp[sum] = i;            
        }
        return res == n + 1 ? -1 : res;
    }
};

// 单调栈方法后面会单独列一个专题
class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
        int n = A.size();
        int res = n + 1;
        deque<int> Q;
        Q.push_back( 0 );
        int presum[n+1];
        presum[0] = 0;
        for ( int i = 0; i < n; ++i ) presum[i+1] = presum[i] + A[i];
        for ( int i = 1; i <= n; ++i ) {
            int sum = presum[i]; // A数组中前i个数的和
            while ( !Q.empty() && sum - presum[Q.front()] >= K ) {
                res = min( res, i - Q.front() );
                Q.pop_front();
            }
            while ( !Q.empty() && presum[Q.back()] >= sum ) {
                Q.pop_back();
            }
            Q.push_back( i );
        }
        return res == n + 1 ? -1 : res;
    }
};