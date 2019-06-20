// 这道题两种思路，一种是把每个数字和行号捆绑起来，排序，然后就变成一个滑动窗口找包含所有种类的行并且范围最小的区间
// 第二种思路是multiple pointers，每次把值最小的那个pointer向前走一个，直到走不动了位置
class Solution {
    struct myComp {
        bool operator () (pair<int, int>& a, pair<int, int>& b) {
            return a.first > b.first;
        }
    };
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int n{nums.size()};
        priority_queue<pair<int, int>, vector<pair<int, int>>, myComp> pq;
        int l{nums[0][0]};
        int r{nums[0][0]};
        vector<int> pointers(n, 0);
        for(int i=0; i<n; ++i){
            pq.push(make_pair(nums[i][0], i));
            l = min(l, nums[i][0]);
            r = max(r, nums[i][0]);
        }
        int curMax{r};
        while(!pq.empty()){
            pair<int, int> cur = pq.top();
            // cout<<cur.first<<" "<<cur.second<<endl;
            pq.pop();
            if(pointers[cur.second]==nums[cur.second].size()-1) break;
            
            curMax = max(curMax, nums[cur.second][++pointers[cur.second]]);
            pq.push(make_pair(nums[cur.second][pointers[cur.second]], cur.second));
            // cout<<"curMax:"<<curMax<<endl;
            // cout<<"pqTop:"<<pq.top().first<<endl;
            if(curMax-pq.top().first<r-l){
                r = curMax;
                l = pq.top().first;
            }
        }
        return vector<int>{l, r};
    }
};